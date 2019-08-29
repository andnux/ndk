//
// Created by 张春林 on 2019/3/26.
//
#include <jni.h>
#include "android/log.h"
#include "ffmpeg.h"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , "ffmpeg.c", __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , "ffmpeg.c", __VA_ARGS__)

static jobject listener;
static JNIEnv *senv;

void onChange(int current, int target) {
    if (listener != NULL) {
        jclass jclass = (*senv)->GetObjectClass(senv, listener);
        jmethodID jmethodID = (*senv)->GetMethodID(senv, jclass, "onChange", "(II)V");
        (*senv)->CallVoidMethod(senv, listener, jmethodID, current, target);
    }
}

JNIEXPORT jint JNICALL
Java_top_andnux_ffmpeg_FFmpeg_run(JNIEnv *env, jclass clazz,
                                     jobjectArray jargv, jobject jlistener) {
    senv = env;
    int argc = (*env)->GetArrayLength(env, jargv);
    listener = (*env)->NewGlobalRef(env, jlistener);
    char *argv[argc];
    jstring buf[argc];
    LOGD("length=%d", argc);
    for (int i = 0; i < argc; ++i) {
        buf[i] = ((*env)->GetObjectArrayElement(env, jargv, i));
        char *string = (char *) ((*env)->GetStringUTFChars(env, buf[i], JNI_FALSE));
        argv[i] = string;
    }
    int ret = ffmpeg_exec(argc, argv, onChange);
    for (int i = 0; i < argc; ++i) {
        free(argv[i]);
    }
    free(argv);
    (*env)->DeleteGlobalRef(env, listener);
    return ret;
}

