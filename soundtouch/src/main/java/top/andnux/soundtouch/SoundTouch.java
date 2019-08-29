package top.andnux.libsoundtouch;

public class SoundTouch {

    //
    // Available setting IDs for the 'setSetting' & 'get_setting' functions:

    /// Enable/disable anti-alias filter in pitch transposer (0 = disable)
    public static final int SETTING_USE_AA_FILTER = 0;

    /// Pitch transposer anti-alias filter length (8 .. 128 taps, default = 32)
    public static final int SETTING_AA_FILTER_LENGTH = 1;

    /// Enable/disable quick seeking algorithm in tempo changer routine
/// (enabling quick seeking lowers CPU utilization but causes a minor sound
///  quality compromising)
    public static final int SETTING_USE_QUICKSEEK = 2;

    /// Time-stretch algorithm single processing sequence length in milliseconds. This determines
/// to how long sequences the original sound is chopped in the time-stretch algorithm.
/// See "STTypes.h" or README for more information.
    public static final int SETTING_SEQUENCE_MS = 3;

    /// Time-stretch algorithm seeking window length in milliseconds for algorithm that finds the
/// best possible overlapping location. This determines from how wide window the algorithm
/// may look for an optimal joining location when mixing the sound sequences back together.
/// See "STTypes.h" or README for more information.
    public static final int SETTING_SEEKWINDOW_MS = 4;

    /// Time-stretch algorithm overlap length in milliseconds. When the chopped sound sequences
/// are mixed back together, to form a continuous sound stream, this parameter defines over
/// how long period the two consecutive sequences are let to overlap each other.
/// See "STTypes.h" or README for more information.
    public static final int SETTING_OVERLAP_MS = 5;


    /// Call "getSetting" with this ID to query processing sequence size in samples.
/// This value gives approximate value of how many input samples you'll need to
/// feed into SoundTouch after initial buffering to get out a new batch of
/// output samples.
///
/// This value does not include initial buffering at beginning of a new processing
/// stream, use SETTING_INITIAL_LATENCY to get the initial buffering size.
///
/// Notices:
/// - This is read-only parameter, i.e. setSetting ignores this parameter
/// - This parameter value is not constant but change depending on
///   tempo/pitch/rate/samplerate settings.
    public static final int SETTING_NOMINAL_INPUT_SEQUENCE = 6;


    /// Call "getSetting" with this ID to query nominal average processing output
/// size in samples. This value tells approcimate value how many output samples
/// SoundTouch outputs once it does DSP processing run for a batch of input samples.
///
/// Notices:
/// - This is read-only parameter, i.e. setSetting ignores this parameter
/// - This parameter value is not constant but change depending on
///   tempo/pitch/rate/samplerate settings.
    public static final int SETTING_NOMINAL_OUTPUT_SEQUENCE = 7;


    /// Call "getSetting" with this ID to query initial processing latency, i.e.
/// approx. how many samples you'll need to enter to SoundTouch pipeline before
/// you can expect to get first batch of ready output samples out.
///
/// After the first output batch, you can then expect to get approx.
/// SETTING_NOMINAL_OUTPUT_SEQUENCE ready samples out for every
/// SETTING_NOMINAL_INPUT_SEQUENCE samples that you enter into SoundTouch.
///
/// Example:
///     processing with parameter -tempo=5
///     => initial latency = 5509 samples
///        input sequence  = 4167 samples
///        output sequence = 3969 samples
///
/// Accordingly, you can expect to feed in approx. 5509 samples at beginning of
/// the stream, and then you'll get out the first 3969 samples. After that, for
/// every approx. 4167 samples that you'll put in, you'll receive again approx.
/// 3969 samples out.
///
/// This also means that average latency during stream processing is
/// INITIAL_LATENCY-OUTPUT_SEQUENCE/2, in the above example case 5509-3969/2
/// = 3524 samples
///
/// Notices:
/// - This is read-only parameter, i.e. setSetting ignores this parameter
/// - This parameter value is not constant but change depending on
///   tempo/pitch/rate/samplerate settings.
    public static final int SETTING_INITIAL_LATENCY = 8;

    static {
        System.loadLibrary("soundtouch");
    }

    public SoundTouch() {
        newInstance();
    }

    //在NDK层创建一个实例
    public native void newInstance();

    // 不使用后一定要调用此方法，防止内存泄露
    public native void deleteInstance();

    /// Get SoundTouch library version Id
    public native String getVersionString();

    /// Sets new rate control value. Normal rate = 1.0, smaller values
    /// represent slower rate, larger faster rates.
    public native void setRate(double newRate);

    /// Sets new tempo control value. Normal tempo = 1.0, smaller values
    /// represent slower tempo, larger faster tempo.
    public native void setTempo(double newTempo);

    /// Sets new rate control value as a difference in percents compared
    /// to the original rate (-50 .. +100 %)
    public native void setRateChange(double newRate);

    /// Sets new tempo control value as a difference in percents compared
    /// to the original tempo (-50 .. +100 %)
    public native void setTempoChange(double newTempo);

    /// Sets new pitch control value. Original pitch = 1.0, smaller values
    /// represent lower pitches, larger values higher pitch.
    public native void setPitch(double newPitch);

    /// Sets pitch change in octaves compared to the original pitch
    /// (-1.00 .. +1.00)
    public native void setPitchOctaves(double newPitch);

    /// Sets pitch change in semi-tones compared to the original pitch
    /// (-12 .. +12)
    public native void setPitchSemiTones(double newPitch);

    /// Sets the number of channels, 1 = mono, 2 = stereo
    public native void setChannels(int numChannels);

    /// Sets sample rate.
    public native void setSampleRate(int srate);

    /// Get ratio between input and output audio durations, useful for calculating
    /// processed output duration: if you'll process a stream of N samples, then
    /// you can expect to get out N * getInputOutputSampleRatio() samples.
    ///
    /// This ratio will give accurate target duration ratio for a full audio track,
    /// given that the the whole track is processed with same processing parameters.
    ///
    /// If this ratio is applied to calculate intermediate offsets inside a processing
    /// stream, then this ratio is approximate and can deviate +- some tens of milliseconds
    /// from ideal offset, yet by end of the audio stream the duration ratio will become
    /// exact.
    ///
    /// Example: if processing with parameters "-tempo=15 -pitch=-3", the function
    /// will return value 0.8695652... Now, if processing an audio stream whose duration
    /// is exactly one million audio samples, then you can expect the processed
    /// output duration  be 0.869565 * 1000000 = 869565 samples.
    public native double getInputOutputSampleRatio();

    /// Flushes the last samples from the processing pipeline to the output.
    /// Clears also the internal processing buffers.
    //
    /// Note: This function is meant for extracting the last samples of a sound
    /// stream. This function may introduce additional blank samples in the end
    /// of the sound stream, and thus it's not recommended to call this function
    /// in the middle of a sound stream.
    public native void flush();

    /// Adds 'numSamples' pcs of samples from the 'samples' memory position into
    /// the input of the object. Notice that sample rate _has_to_ be set before
    /// calling this function, otherwise throws a runtime_error exception.
    public native void putSamples(
            float[] samples,  ///< Pointer to sample buffer.
            int numSamples                         ///< Number of samples in buffer. Notice
            ///< that in case of stereo-sound a single sample
            ///< contains data for both channels.
    );

    /// Output samples from beginning of the sample buffer. Copies requested samples to
    /// output buffer and removes them from the sample buffer. If there are less than
    /// 'numsample' samples in the buffer, returns all that available.
    ///
    /// \return Number of samples returned.
    public native int receiveSamples(float[] outBuffer, ///< Buffer where to copy output samples.
                                     int maxSamples                 ///< How many samples to receive at max.
    );

    /// Clears all the samples in the object's output and internal processing
    /// buffers.
    public native void clear();

    /// Changes a setting controlling the processing system behaviour. See the
    /// 'SETTING_...' defines for available setting ID's.
    ///
    /// \return 'true' if the setting was successfully changed
    public native boolean setSetting(int settingId,   ///< Setting ID number. see SETTING_... defines.
                                     int value        ///< New setting value.
    );

    /// Reads a setting controlling the processing system behaviour. See the
    /// 'SETTING_...' defines for available setting ID's.
    ///
    /// \return the setting value.
    public native int getSetting(int settingId    ///< Setting ID number, see SETTING_... defines.
    );

    /// Returns number of samples currently unprocessed.
    public native int numUnprocessedSamples();

    /// Return number of channels
    public native int numChannels();
}
