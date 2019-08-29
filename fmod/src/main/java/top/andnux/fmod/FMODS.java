package top.andnux.fmod;

import android.content.Context;

import org.fmod.FMOD;

public class FMODS {

    //音效的类型
    public static final int MODE_NORMAL = 0;//正常
    public static final int MODE_LUOLI = 1;//萝莉
    public static final int MODE_DASHU = 2;//大叔
    public static final int MODE_JINGSONG = 3;//惊悚
    public static final int MODE_GAOGUAI = 4;//搞怪
    public static final int MODE_KONGLING = 5;//空灵

    static {
        try {
            System.loadLibrary("fmodL");
            System.loadLibrary("fmod");
            System.loadLibrary("fmods");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static native void fix(String path, int type);

    public static void init(Context context) {
        FMOD.init(context);
    }

    public static void close() {
        FMOD.close();
    }
}
