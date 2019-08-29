////////////////////////////////////////////////////////////////////////////////
///
/// Example Interface class for SoundTouch native compilation
///
/// Author        : Copyright (c) Olli Parviainen
/// Author e-mail : oparviai 'at' iki.fi
/// WWW           : http://www.surina.net
///
////////////////////////////////////////////////////////////////////////////////

#include <jni.h>
#include <android/log.h>
#include <stdexcept>
#include <string>

using namespace std;

#include "SoundTouch.h"

#define LOGV(...)   __android_log_print((int)ANDROID_LOG_INFO, "SOUNDTOUCH", __VA_ARGS__)
//#define LOGV(...)

static string _errMsg = "";


#define DLL_PUBLIC __attribute__ ((visibility ("default")))
#define BUFF_SIZE 4096


using namespace soundtouch;


// Set error message to return
static void _setErrmsg(const char *msg) {
    _errMsg = msg;
}


#ifdef _OPENMP

#include <pthread.h>
extern pthread_key_t gomp_tls_key;
static void * _p_gomp_tls = NULL;

static int _init_threading(bool warn)
{
    void *ptr = pthread_getspecific(gomp_tls_key);
    LOGV("JNI thread-specific TLS storage %ld", (long)ptr);
    if (ptr == NULL)
    {
        LOGV("JNI set missing TLS storage to %ld", (long)_p_gomp_tls);
        pthread_setspecific(gomp_tls_key, _p_gomp_tls);
    }
    else
    {
        LOGV("JNI store this TLS storage");
        _p_gomp_tls = ptr;
    }
    // Where critical, show warning if storage still not properly initialized
    if ((warn) && (_p_gomp_tls == NULL))
    {
        _setErrmsg("Error - OpenMP threading not properly initialized: Call SoundTouch.getVersionString() from the App main thread!");
        return -1;
    }
    return 0;
}

#else

static int _init_threading(bool warn) {
    // do nothing if not OpenMP build
    return 0;
}

#endif

extern "C" JNICALL jstring
Java_top_andnux_soundtouch_SoundTouch_getVersionString(JNIEnv *env, jobject instance) {
    const char *verStr;
    LOGV("JNI call SoundTouch.getVersionString");
    // Call example SoundTouch routine
    verStr = SoundTouch::getVersionString();

    /// gomp_tls storage bug workaround - see comments in _init_threading() function!
    _init_threading(false);

    int threads = 0;
#pragma omp parallel
    {
#pragma omp atomic
        threads++;
    }
    LOGV("JNI thread count %d", threads);
    // return version as string
    return env->NewStringUTF(verStr);
}


static SoundTouch *soundTouch;

void check() {
    if (soundTouch == nullptr) {
        soundTouch = new SoundTouch();
    }
}

extern "C" JNICALL void
Java_top_andnux_soundtouch_SoundTouch_newInstance(JNIEnv *env, jobject instance) {
    soundTouch = new SoundTouch();
}

extern "C" JNICALL void
Java_top_andnux_soundtouch_SoundTouch_deleteInstance(JNIEnv *env, jobject instance) {
    delete soundTouch;
}

extern "C" JNICALL void
Java_top_andnux_soundtouch_SoundTouch_setRate(JNIEnv *env, jobject instance, jdouble newRate) {
    check();
    soundTouch->setRate(newRate);
}

extern "C" JNICALL void
Java_top_andnux_soundtouch_SoundTouch_setTempo(JNIEnv *env, jobject instance, jdouble newTempo) {
    check();
    soundTouch->setTempo(newTempo);
}

extern "C" JNICALL void
Java_top_andnux_soundtouch_SoundTouch_setRateChange(JNIEnv *env, jobject instance,
                                                       jdouble newRate) {
    check();
    soundTouch->setRateChange(newRate);
}

extern "C" JNICALL void
Java_top_andnux_soundtouch_SoundTouch_setTempoChange(JNIEnv *env, jobject instance,
                                                        jdouble newTempo) {
    check();
    soundTouch->setTempoChange(newTempo);
}

extern "C" JNICALL void
Java_top_andnux_soundtouch_SoundTouch_setPitch(JNIEnv *env, jobject instance,
                                                  jdouble newPitch) {
    check();
    soundTouch->setPitch(newPitch);
}
extern "C" JNICALL void
Java_top_andnux_soundtouch_SoundTouch_setPitchOctaves(JNIEnv *env, jobject instance,
                                                         jdouble newPitch) {
    check();
    soundTouch->setPitchOctaves(newPitch);
}

extern "C" JNICALL void
Java_top_andnux_soundtouch_SoundTouch_setPitchSemiTones(JNIEnv *env, jobject instance,
                                                           jdouble newPitch) {
    check();
    soundTouch->setPitchSemiTones(newPitch);
}

extern "C" JNICALL void
Java_top_andnux_soundtouch_SoundTouch_setChannels(JNIEnv *env, jobject instance,
                                                     jint numChannels) {
    check();
    soundTouch->setChannels(numChannels);
}

extern "C" JNICALL void
Java_top_andnux_soundtouch_SoundTouch_setSampleRate(JNIEnv *env, jobject instance,
                                                       jint srate) {
    check();
    soundTouch->setSampleRate(srate);
}

extern "C" JNICALL jdouble
Java_top_andnux_soundtouch_SoundTouch_getInputOutputSampleRatio(JNIEnv *env, jobject instance) {
    check();
    return soundTouch->getInputOutputSampleRatio();
}

extern "C" JNICALL void
Java_top_andnux_soundtouch_SoundTouch_flush(JNIEnv *env, jobject instance) {
    check();
    soundTouch->flush();
}

extern "C" JNICALL void
Java_top_andnux_soundtouch_SoundTouch_putSamples(JNIEnv *env, jobject instance,
                                                    jfloatArray samples_,
                                                    jint numSamples) {
    check();
    jfloat *samples = env->GetFloatArrayElements(samples_, nullptr);
    soundTouch->putSamples(samples, static_cast<uint>(numSamples));
}

extern "C" JNICALL jint
Java_top_andnux_soundtouch_SoundTouch_receiveSamples(JNIEnv *env, jobject instance,
                                                        jfloatArray samples_,
                                                        jint maxSamples) {
    check();
    jfloat *samples = env->GetFloatArrayElements(samples_, nullptr);
    return soundTouch->receiveSamples(samples, static_cast<uint>(maxSamples));
}

extern "C" JNICALL void
Java_top_andnux_soundtouch_SoundTouch_clear(JNIEnv *env, jobject instance) {
    check();
    soundTouch->clear();
}

extern "C" JNICALL jboolean
Java_top_andnux_soundtouch_SoundTouch_setSetting(JNIEnv *env, jobject instance, jint settingId,
                                                    jint value) {
    check();
    return static_cast<jboolean>(soundTouch->setSetting(settingId, value));
}

extern "C" JNICALL jint
Java_top_andnux_soundtouch_SoundTouch_getSetting(JNIEnv *env, jobject instance, jint settingId) {
    check();
    return soundTouch->getSetting(settingId);
}

extern "C" JNICALL jint
Java_top_andnux_soundtouch_SoundTouch_numUnprocessedSamples(JNIEnv *env, jobject instance) {
    check();
    return soundTouch->numUnprocessedSamples();
}


extern "C" JNICALL jint
Java_top_andnux_soundtouch_SoundTouch_numChannels(JNIEnv *env, jobject instance) {
    check();
    return soundTouch->numChannels();
}