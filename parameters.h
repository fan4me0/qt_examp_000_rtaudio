#ifndef QT_GLOBAL_PARAM_H
#define QT_GLOBAL_PARAM_H

//----------------------------------------------------------------------------------------------
// Global parameters
//----------------------------------------------------------------------------------------------
#define SAMPLE_FORMAT           RTAUDIO_FLOAT64
#define SAMPLE_FORMAT_TYPE      double
#define SAMPLE_FORMAT_FLOAT64


// !!! by default the data sampled in the OS buffer from signal input (e.g. microphone)
// are interleaved that is for channels = 2 samples that are fed into fft has to be
// selected either odd or even
const int AUDIO_DEV_CHANNEL_NBR               = 1;
const int AUDIO_DEV_IN_FISRT_CHANNEL_OFFSET   = 0;
const int AUDIO_DEV_OUT_FISRT_CHANNEL_OFFSET  = 0;
const int AUDIO_DEV_BUFFER_FRAMES_NBR         = 2048;
const int AUDIO_DEV_SAMPLING_FREQ             = 44100;

/* number of the vector of vectors i.e :
nbr_samples_to_store = AUDIO_DEV_BUFFER_FRAMES_NBR * row_nbr
*/
const int ROW_NBR = 200;


#if defined(__LINUX_PULSE__)
const char AUDIO_SERVER[] = "__LINUX_PULSE__";
const char LIBS_USED[] = "-lpulse-simple -lpulse";
#else
    #if defined(__UNIX_JACK__)
    const char AUDIO_SERVER[] = "__UNIX_JACK__";
    const char LIBS_USED[] = "-lasound -ljack";
    #else
        #if defined(__LINUX_ALSA__)
        const char AUDIO_SERVER[] = "__LINUX_ALSA__";
        const char LIBS_USED[] = "-lasound";
        #else
            #error Define audio interface in makefile via one of the __LINUX_PULSE__, __UNIX_JACK__ or __LINUX_ALSA__ macro.
        #endif  // defined(__LINUX_ALSA__)
    #endif  // defined(__UNIX_JACK__)
#endif  // defined(__LINUX_PULSE__)

#endif // QT_GLOBAL_PARAM_H
