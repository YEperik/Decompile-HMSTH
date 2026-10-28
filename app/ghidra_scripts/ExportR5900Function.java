// Export one bounded R5900 function. Input ELF is never executed.
// @category PS2Workbench
import ghidra.app.util.headless.HeadlessScript;
import ghidra.framework.options.Options;
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.pcode.*;
import ghidra.program.model.data.DataOrganization;
import ghidra.program.model.lang.Register;
import java.nio.file.*;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.util.*;
import com.google.gson.GsonBuilder;

public class ExportR5900Function extends HeadlessScript {
    private Map<String,Object> operand(Varnode node) {
        Map<String,Object> value = new LinkedHashMap<>();
        value.put("space", node.getAddress().getAddressSpace().getName());
        value.put("offset", Long.toUnsignedString(node.getOffset(), 16));
        value.put("size", node.getSize());
        Register register = currentProgram.getLanguage().getRegister(node.getAddress(), node.getSize());
        if (register != null) value.put("register", register.getName());
        return value;
    }

    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 5) throw new IllegalArgumentException("start size output_dir expected_sha256 analysis_profile");
        String language = currentProgram.getLanguageID().toString();
        if (!language.equals("r5900:LE:32:default")) throw new IllegalStateException("Wrong processor: " + language);
        String profile = args[4];
        if (!profile.equals("bounded") && !profile.equals("recommended")) throw new IllegalArgumentException("Unknown profile");
        if (profile.equals("recommended") && analysisTimeoutOccurred()) throw new IllegalStateException("Auto-analysis timed out");
        Map<String,Object> analysis = new LinkedHashMap<>();
        analysis.put("profile", profile);
        analysis.put("auto_analysis_completed", profile.equals("recommended"));
        Map<String,Boolean> settings = new LinkedHashMap<>();
        if (profile.equals("recommended")) {
            Options options = currentProgram.getOptions(Program.ANALYSIS_PROPERTIES);
            String[] names = {"Decompiler Parameter ID", "Demangler GNU", "Demangler GNU.Use Deprecated Demangler"};
            boolean[] expected = {false, true, true};
            for (int i = 0; i < names.length; i++) {
                if (!options.contains(names[i]) || options.getBoolean(names[i], !expected[i]) != expected[i])
                    throw new IllegalStateException("Analyzer setting mismatch: " + names[i]);
                settings.put(names[i], expected[i]);
            }
        }
        analysis.put("settings", settings);
        Address start = toAddr(Long.decode(args[0]));
        int size = Integer.parseInt(args[1]);
        if (size <= 0 || size > 16384 || size % 4 != 0) throw new IllegalArgumentException("Size must be aligned and <=16 KiB");
        AddressSet body = new AddressSet(start, start.add(size - 1));
        byte[] raw = new byte[size];
        if (currentProgram.getMemory().getBytes(start, raw) != size) throw new IllegalStateException("Short mapped bytes");
        String digest = HexFormat.of().formatHex(MessageDigest.getInstance("SHA-256").digest(raw));
        if (!digest.equals(args[3])) throw new IllegalStateException("Loader bytes differ from source range");
        DisassembleCommand command = new DisassembleCommand(start, body, true);
        if (!command.applyTo(currentProgram, monitor)) throw new IllegalStateException("Disassembly failed: " + command.getStatusMsg());
        List<Map<String,Object>> instructions = new ArrayList<>();
        Map<String,Integer> useropCounts = new TreeMap<>();
        int covered = 0;
        while (covered < size) {
            monitor.checkCancelled();
            Instruction instruction = currentProgram.getListing().getInstructionAt(start.add(covered));
            if (instruction == null || instruction.getLength() != 4) throw new IllegalStateException("Undecoded instruction at " + start.add(covered));
            Map<String,Object> row = new LinkedHashMap<>();
            row.put("address", instruction.getAddress().toString());
            row.put("bytes", HexFormat.of().formatHex(instruction.getBytes()));
            row.put("assembly", instruction.toString());
            row.put("pcode_ops", instruction.getPcode().length);
            List<Map<String,Object>> userops = new ArrayList<>();
            for (PcodeOp op : instruction.getPcode()) {
                if (op.getOpcode() != PcodeOp.CALLOTHER) continue;
                String name = currentProgram.getLanguage().getUserDefinedOpName((int)op.getInput(0).getOffset());
                if (name == null || name.isEmpty()) throw new IllegalStateException("Unknown p-code userop");
                Map<String,Object> item = new LinkedHashMap<>();
                item.put("name", name);
                List<Map<String,Object>> inputs = new ArrayList<>();
                for (int i = 1; i < op.getNumInputs(); i++) inputs.add(operand(op.getInput(i)));
                item.put("inputs", inputs);
                if (op.getOutput() != null) item.put("output", operand(op.getOutput()));
                userops.add(item);
                useropCounts.merge(name, 1, Integer::sum);
            }
            row.put("userops", userops);
            instructions.add(row); covered += 4;
        }
        Function function = currentProgram.getFunctionManager().getFunctionAt(start);
        if (function == null) function = currentProgram.getFunctionManager().createFunction("target_" + start, start, body, SourceType.USER_DEFINED);
        else function.setBody(body);
        if (function == null) throw new IllegalStateException("Function creation failed");
        DecompInterface decompiler = new DecompInterface();
        String code;
        String warning;
        try {
            if (!decompiler.openProgram(currentProgram)) throw new IllegalStateException(decompiler.getLastMessage());
            DecompileResults result = decompiler.decompileFunction(function, 60, monitor);
            if (!result.decompileCompleted() || result.getDecompiledFunction() == null) throw new IllegalStateException("Decompile failed: " + result.getErrorMessage());
            if (result.getHighFunction() == null) throw new IllegalStateException("No high function");
            java.util.Iterator<ghidra.program.model.pcode.PcodeOpAST> operations = result.getHighFunction().getPcodeOps();
            while (operations.hasNext()) {
                Address origin = operations.next().getSeqnum().getTarget();
                if (!body.contains(origin)) throw new IllegalStateException("Decompiler expanded beyond selected range: " + origin);
            }
            code = result.getDecompiledFunction().getC();
            warning = result.getErrorMessage();
        } finally { decompiler.dispose(); }
        Path output = Path.of(args[2]);
        Files.createDirectories(output);
        Files.writeString(output.resolve("decompiled.c"), code, StandardCharsets.UTF_8, StandardOpenOption.CREATE_NEW);
        Map<String,Object> result = new LinkedHashMap<>();
        result.put("status", "DECOMPILED_UNVERIFIED");
        result.put("language", language);
        result.put("export_schema", 2);
        DataOrganization organization = currentProgram.getDataTypeManager().getDataOrganization();
        Map<String,Integer> sizes = new LinkedHashMap<>();
        sizes.put("char", organization.getCharSize());
        sizes.put("short", organization.getShortSize());
        sizes.put("int", organization.getIntegerSize());
        sizes.put("long", organization.getLongSize());
        sizes.put("long_long", organization.getLongLongSize());
        sizes.put("pointer", organization.getPointerSize());
        result.put("scalar_sizes", sizes);
        result.put("pcode_userop_counts", useropCounts);
        result.put("analysis", analysis);
        result.put("analyzer_options", getCurrentAnalysisOptionsAndValues(currentProgram));
        List<Map<String,Object>> blocks = new ArrayList<>();
        for (ghidra.program.model.mem.MemoryBlock block : currentProgram.getMemory().getBlocks()) {
            Map<String,Object> item = new LinkedHashMap<>();
            item.put("name", block.getName()); item.put("start", block.getStart().toString());
            item.put("size", block.getSize()); item.put("initialized", block.isInitialized());
            item.put("read", block.isRead()); item.put("write", block.isWrite()); item.put("execute", block.isExecute());
            blocks.add(item);
        }
        result.put("memory_blocks", blocks);
        result.put("ghidra_version", ghidra.framework.Application.getApplicationVersion());
        result.put("java_version", System.getProperty("java.version"));
        result.put("compiler_spec", currentProgram.getCompilerSpec().getCompilerSpecID().toString());
        result.put("decompiler_warning", warning);
        result.put("function_name", function.getName());
        result.put("start", start.toString());
        result.put("size", size);
        result.put("mapped_bytes_sha256", digest);
        result.put("instructions", instructions);
        result.put("pcode_origins_within_selected_range", true);
        result.put("recompiled", false);
        result.put("semantics_verified", false);
        Files.writeString(output.resolve("result.json"), new GsonBuilder().setPrettyPrinting().create().toJson(result), StandardCharsets.UTF_8, StandardOpenOption.CREATE_NEW);
        println("PS2_WORKBENCH_EXPORT_OK " + output);
    }
}
