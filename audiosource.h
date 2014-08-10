#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

// C++ Standard includes
#include <vector>

// Qt includes
#include <QVector>
#include <QPointF>

// Stk includes
#include "RtAudio.h"

// App includes
#include "parameters.h"

class audioSource
{
public:
    audioSource(unsigned int sampl_freq = AUDIO_DEV_SAMPLING_FREQ);
    virtual ~audioSource();
    void fillSignal( QVector<QPointF> & buffer );
    void storeDataToFile();

private :
    static volatile bool lock_fill;
    static QVector<QPointF>    m_qpoint_signal;
    static std::vector<std::vector<double>> audio_log;
    static int audio_buffer_full( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                                    double streamTime, RtAudioStreamStatus status, void *data );
    static void storeData( void * vv );

    RtAudio         m_audio_device;
    RtAudio::StreamParameters   m_aud_dev_in_params;
    RtAudio::StreamParameters   m_aud_dev_out_params;
    RtAudio::StreamOptions      m_options;
    unsigned int    m_audio_buffer_frames;      // number of elements of size e.g. double
    unsigned int    m_audio_buffer_bytes;       // number of bytes in buffer i.e. 'm_audio_buffer_frames * sizeof(double)'
    unsigned int    m_sampling_freq;
};

#endif // AUDIOSOURCE_H
