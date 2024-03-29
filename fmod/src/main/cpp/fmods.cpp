//
// Created by 张春林 on 2019/3/26.
//
#include <jni.h>
#include <android/log.h>
#include "fmod.hpp"

#include <string.h>
#include <unistd.h>

using namespace FMOD;

#define MODE_NORMAL 0
#define MODE_LUOLI 1
#define MODE_DASHU 2
#define MODE_JINGSONG 3
#define MODE_GAOGUAI 4
#define MODE_KONGLING 5

#include <android/log.h>

#define LOGI(FORMAT, ...) __android_log_print(ANDROID_LOG_INFO,"fmod",FORMAT,##__VA_ARGS__);
#define LOGE(FORMAT, ...) __android_log_print(ANDROID_LOG_ERROR,"fmod",FORMAT,##__VA_ARGS__);

extern "C"
JNIEXPORT void JNICALL
Java_top_andnux_fmod_FMODS_fix(JNIEnv *env, jclass type_, jstring path_, jint type) {
    const char *path = env->GetStringUTFChars(path_, 0);

    System *system;
    Sound *sound;
    Channel *channel = NULL;
    DSP *dsp;
    bool playing = true;
    float frequency = 1;

    //初始化
    System_Create(&system);
    system->init(32, FMOD_INIT_NORMAL, NULL);
    //创建声音
    system->createSound(path, FMOD_DEFAULT, 0, &sound);
    try {
        //根据类型改变声音
        switch (type) {
            case MODE_NORMAL:
                //正常声音
                system->playSound(sound, 0, false, &channel);
                break;
            case MODE_LUOLI:
                //萝莉
                //DSP digital signal process
                //dsp -> 音效 创建fmod中预定义好的音效
                //FMOD_DSP_TYPE_PITCHSHIFT dsp，提升或者降低音调用的一种音效
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                //提高音效
                dsp->setParameterFloat(FMOD_DSP_TYPE_PITCHSHIFT, 2.5);
                //播放声音
                system->playSound(sound, 0, false, &channel);
                //将channel添加到dsp
                channel->addDSP(0, dsp);
                break;
            case MODE_DASHU:
                //大叔
                system->createDSPByType(FMOD_DSP_TYPE_PITCHSHIFT, &dsp);
                //降低声音
                dsp->setParameterFloat(FMOD_DSP_PITCHSHIFT_PITCH, 0.8);
                //播放声音
                system->playSound(sound, 0, false, &channel);
                //将channel添加到dsp
                channel->addDSP(0, dsp);
                break;
            case MODE_JINGSONG:
                //惊悚
                system->createDSPByType(FMOD_DSP_TYPE_TREMOLO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_TREMOLO_SKEW, 0.5);
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                break;
            case MODE_GAOGUAI:
                //搞怪
                //提高说话的速度
                system->playSound(sound, 0, false, &channel);
                //frequency  原来的声音速度
                channel->getFrequency(&frequency);
                frequency = static_cast<float>(frequency * 1.6);
                channel->setFrequency(frequency);
                LOGI("%s", "fix gaoguai");
                break;
            case MODE_KONGLING:
                //空灵
                system->createDSPByType(FMOD_DSP_TYPE_ECHO, &dsp);
                dsp->setParameterFloat(FMOD_DSP_ECHO_DELAY, 300);
                dsp->setParameterFloat(FMOD_DSP_ECHO_FEEDBACK, 20);
                system->playSound(sound, 0, false, &channel);
                channel->addDSP(0, dsp);
                LOGI("%s", "fix kongling");
                break;
            default:
                break;
        }
    }
    catch (...) {
        //捕捉异常
        LOGE("%s", "发生异常");
    }
    system->update();
    //释放资源
    //单位是微秒
    //每秒钟判断下是否在播放
    while (playing) {
        channel->isPlaying(&playing);
        usleep(1000 * 1000);
    }

    //释放
    sound->release();
    system->close();
    system->release();
    env->ReleaseStringUTFChars(path_, path);
}
