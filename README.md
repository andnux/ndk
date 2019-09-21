### 快速集成：
- **Step 1.** Add the JitPack repository to your build file
```groovy
allprojects {
    repositories {
        maven { url 'https://jitpack.io' }
    }
}
```
- Step 2. Add the dependency
```groovy
dependencies {
    implementation 'com.github.andnux:ndk:0.0.1'
    or
    implementation 'com.github.andnux.ndk:rtmp:0.0.2'
    implementation 'com.github.andnux.ndk:bspatch:0.0.2'
    implementation 'com.github.andnux.ndk:lame:0.0.2'
    implementation 'com.github.andnux.ndk:aac:0.0.2'
    implementation 'com.github.andnux.ndk:breakpad:0.0.2'
    implementation 'com.github.andnux.ndk:soundtouch:0.0.2'
    implementation 'com.github.andnux.ndk:x264:0.0.2'
    implementation 'com.github.andnux.ndk:ffmpeg:0.0.2'
    implementation 'com.github.andnux.ndk:fmod:0.0.2'
    implementation 'com.github.andnux.ndk:zbar:0.0.2'
    implementation 'com.github.andnux.ndk:jpeg:0.0.2'
    implementation 'com.github.andnux.ndk:glide:0.0.2'
    implementation 'com.github.andnux.ndk:yuv:0.0.2'
}
```
