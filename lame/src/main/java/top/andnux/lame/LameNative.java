package top.andnux.lame;

public class LameNative {

    static {
        System.loadLibrary("lame");
    }

    /**
     * pcm to mp3
     *
     * @param input
     * @param output
     */
    public static native void convert(String input, String output);


    /**
     * 初始化
     *
     * @param samplerate 音频的采样率
     * @param channels   编码器的声道
     * @param brate      压缩比。Default is compression ratio of 11.
     *                   quality=0..9.  0=best (very slow).  9=worst.
     *                   3     near-best quality, not too slow
     *                   5     good quality, fast
     *                   7     ok quality, really fast
     * @param quality
     */
    public static native void init(int samplerate, int channels,
                                   int brate, int quality);

    /**
     * 销毁编码器
     */
    public static native void destroy();

    /**
     * 编码
     *
     * @param lbuffer
     * @param rbuffer
     * @param len
     * @return
     */
    public static native byte[] encode(short[] lbuffer, short[] rbuffer,
                                       int len);

    /**
     * 获取版本
     *
     * @return
     */
    public static native String getVersion();
}
