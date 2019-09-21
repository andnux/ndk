#include <jni.h>
#include <string>
#include <cstdio>
#include <android/log.h>

#include "client/linux/handler/exception_handler.h"
#include "client/linux/handler/minidump_descriptor.h"

#define LOG_TAG "breakpad"

#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define ALOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define ALOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define ALOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

bool DumpCallback(const google_breakpad::MinidumpDescriptor &descriptor,
                  void *context,
                  bool succeeded) {
    ALOGD("===============crrrrash================");
    ALOGD("Dump path: %s\n", descriptor.path());
    return succeeded;
}

/** java 代码中调用*/
extern "C"
JNIEXPORT void JNICALL
Java_top_andnux_breakpad_BreakPad_init(JNIEnv *env, jclass type,
                                                           jstring path_) {
    const char *path = env->GetStringUTFChars(path_, nullptr);
    google_breakpad::MinidumpDescriptor descriptor(path);
    static google_breakpad::ExceptionHandler eh(descriptor, nullptr, DumpCallback, NULL, true, -1);
    env->ReleaseStringUTFChars(path_, path);
}

JNIEXPORT jint
JNICALL JNI_OnLoad(JavaVM
                   *vm,
                   void *reserved
) {
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    return JNI_VERSION_1_6;
}
