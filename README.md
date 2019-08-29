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
    implementation 'com.github.andnux:ndk:1.1.0'
    or
    implementation 'com.github.andnux.ndk:lame:1.1.0'
    implementation 'com.github.andnux.ndk:fmod:1.1.0'
    implementation 'com.github.andnux.ndk:jpeg:1.1.0'
    implementation 'com.github.andnux.ndk:soundtouch:1.1.0'
    implementation 'com.github.andnux.ndk:ffmpeg:1.1.0'
    implementation 'com.github.andnux.ndk:bspatch:1.1.0'
    implementation 'com.github.andnux.ndk:glide:1.1.0'
    implementation 'com.github.andnux.ndk:yuv:1.1.0'
    implementation 'com.github.andnux.ndk:rtmp:1.1.0'
}
```
