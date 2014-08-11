#ifndef QT_GLOBAL_PARAM_H
#define QT_GLOBAL_PARAM_H

//----------------------------------------------------------------------------------------------
// Parameters for audioSource.cpp
//----------------------------------------------------------------------------------------------

typedef double  MY_TYPE;
#define FORMAT RTAUDIO_FLOAT64

// !!! by default the data sampled in the OS buffer from signal input (e.g. microphone)
// are interleaved that is for channels = 2 samples that are fed into fft has to be
// selected either odd or even
#define AUDIO_DEV_CHANNEL_NBR               1UL

#define AUDIO_DEV_IN_FISRT_CHANNEL_OFFSET   0UL

#define AUDIO_DEV_OUT_FISRT_CHANNEL_OFFSET  0UL

#define AUDIO_DEV_BUFFER_FRAMES_NBR         512UL     // i.e. 'AUDIO_DEV_BUFFER_FRAMES_NBR' number of sample type

#define AUDIO_DEV_SAMPLING_FREQ             44100UL

#if defined(__LINUX_PULSE__)
#define AUDIO_SERVER    "__LINUX_PULSE__"
#define LIBS_USED       "-lpulse-simple -lpulse"
#else
#if defined(__UNIX_JACK__)
#define AUDIO_SERVER    __UNIX_JACK__
#define LIBS_USED  =  "-lasound -ljack";
#else
#if defined(__LINUX_ALSA__)
#define AUDIO_SERVER    __LINUX_ALSA__
#define LIBS_USED =   "-lasound";
#endif  // defined(__LINUX_ALSA__)
#endif  // defined(__UNIX_JACK__)
#endif  // defined(__LINUX_PULSE__)

#endif // QT_GLOBAL_PARAM_H
