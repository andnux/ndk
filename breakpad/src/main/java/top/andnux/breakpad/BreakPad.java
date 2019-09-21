package top.andnux.breakpad;

public class BreakPad {
    static {
        System.loadLibrary("breakpad");
    }

    public native static void init(String path);

}
