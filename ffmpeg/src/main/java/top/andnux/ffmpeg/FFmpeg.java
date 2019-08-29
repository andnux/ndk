package top.andnux.libffmpeg;

public class FFmpeg {

    public static void loadLibrary() {
        System.loadLibrary("avutil-56");
        System.loadLibrary("swresample-3");
        System.loadLibrary("swscale-5");
        System.loadLibrary("avcodec-58");
        System.loadLibrary("avformat-58");
        System.loadLibrary("postproc-55");
        System.loadLibrary("avfilter-7");
        System.loadLibrary("avdevice-58");
        System.loadLibrary("ffmpeg");
    }

    static {
        loadLibrary();
    }

    public interface ProgressListener {
        void onChange(int current, int target);
    }


    public static int run(String[] argc) {
        return run(argc, (current, target) -> {

        });
    }

    public static native int run(String[] argc, ProgressListener listener);
}
