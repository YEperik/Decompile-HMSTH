// Upstream compatibility settings, applied before auto-analysis.
// @category PS2Workbench
import ghidra.app.util.headless.HeadlessScript;
import ghidra.framework.options.Options;
import ghidra.program.model.listing.Program;

public class ConfigureR5900 extends HeadlessScript {
    public void run() throws Exception {
        setHeadlessContinuationOption(HeadlessContinuationOption.ABORT_AND_DELETE);
        if (!currentProgram.getLanguageID().toString().equals("r5900:LE:32:default"))
            throw new IllegalStateException("R5900 required");
        Options options = currentProgram.getOptions(Program.ANALYSIS_PROPERTIES);
        String[] names = {"Decompiler Parameter ID", "Demangler GNU", "Demangler GNU.Use Deprecated Demangler"};
        boolean[] values = {false, true, true};
        for (int i = 0; i < names.length; i++) {
            if (!options.contains(names[i])) throw new IllegalStateException("Missing analyzer option: " + names[i]);
            options.setBoolean(names[i], values[i]);
            if (options.getBoolean(names[i], !values[i]) != values[i]) throw new IllegalStateException("Setting rejected: " + names[i]);
        }
        setHeadlessContinuationOption(HeadlessContinuationOption.CONTINUE);
        println("PS2_WORKBENCH_PROFILE_CONFIGURED");
    }
}
