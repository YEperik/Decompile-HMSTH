// @category PS2Workbench
import ghidra.app.util.headless.HeadlessScript;
import ghidra.app.decompiler.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.pcode.*;
import java.nio.file.*;
import java.util.*;
import com.google.gson.GsonBuilder;

public class ExportR5900Program extends HeadlessScript {
    public void run() throws Exception {
        if (!currentProgram.getLanguageID().toString().equals("r5900:LE:32:default")) throw new IllegalStateException("R5900 required");
        if (analysisTimeoutOccurred()) throw new IllegalStateException("Analysis timeout");
        Path out=Paths.get(getScriptArgs()[0]); Files.createDirectories(out.resolve("functions"));
        DecompInterface decompiler=new DecompInterface();
        if (!decompiler.openProgram(currentProgram)) throw new IllegalStateException("Cannot open decompiler");
        List<Map<String,Object>> rows=new ArrayList<>(); int success=0,failed=0;
        try {
            FunctionIterator functions=currentProgram.getFunctionManager().getFunctions(true);
            while(functions.hasNext()) {
                monitor.checkCancelled(); Function f=functions.next(); if(f.isExternal())continue;
                Map<String,Object> row=new LinkedHashMap<>(); String addr=f.getEntryPoint().toString();
                row.put("address",addr);row.put("name",f.getName());row.put("body_bytes",f.getBody().getNumAddresses());
                Map<String,Integer> userops=new TreeMap<>();
                InstructionIterator instructions=currentProgram.getListing().getInstructions(f.getBody(),true);
                int count=0;
                while(instructions.hasNext()) { Instruction ins=instructions.next(); count++;
                    for(PcodeOp op:ins.getPcode())if(op.getOpcode()==PcodeOp.CALLOTHER) {
                        String name=currentProgram.getLanguage().getUserDefinedOpName((int)op.getInput(0).getOffset());
                        userops.put(name,userops.getOrDefault(name,0)+1);
                    }
                }
                row.put("instructions",count);row.put("pcode_userops",userops);
                DecompileResults result=decompiler.decompileFunction(f,30,monitor);
                if(result.decompileCompleted() && result.getDecompiledFunction()!=null) {
                    String file="functions/"+addr+".c";String code=result.getDecompiledFunction().getC();Files.writeString(out.resolve(file),code);
                    List<String> warnings=new ArrayList<>();for(String line:code.split("\\R"))if(line.contains("WARNING:"))warnings.add(line.trim());
                    row.put("warnings",warnings);
                    row.put("status","DECOMPILED_UNVERIFIED");row.put("file",file);success++;
                } else {row.put("status","FAILED");failed++;}
                row.put("message",result.getErrorMessage());rows.add(row);
            }
        } finally {decompiler.dispose();}
        Map<String,Object> report=new LinkedHashMap<>();report.put("language",currentProgram.getLanguageID().toString());
        report.put("status",failed==0?"DECOMPILED_UNVERIFIED":"PARTIAL_DECOMPILATION");
        report.put("discovered_functions",rows.size());report.put("decompiled",success);report.put("failed",failed);
        report.put("functions",rows);report.put("analysis_completed",true);report.put("semantics_verified",false);
        report.put("whole_game_reconstructed",false);report.put("game_executed",false);
        Files.writeString(out.resolve("result.json"),new GsonBuilder().setPrettyPrinting().create().toJson(report));
        println("PS2_WORKBENCH_PROGRAM_EXPORTED "+success+" / "+rows.size());
    }
}
