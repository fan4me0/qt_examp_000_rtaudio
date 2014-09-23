#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

// C++ Standard includes
#include <vector>
#include <mutex>

// Qt includes
#include <QVector>
#include <QPointF>

// RtAudio includes
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
    void setLogBuff();
    bool getLogBuff();
    void setStoreBuff();
    void setSaveBuffLog();
    void statTimeToogle();

private :
    static bool log_buff;
    static bool save_buff_log;
    static bool m_stat_time;
    static volatile bool lock_fill;
    static QVector<QPointF>    m_qpoint_signal;
    static std::vector<std::vector<double>> audio_log;
    static int audio_buffer_full( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                                    double streamTime, RtAudioStreamStatus status, void *data );
    static void statTime();
    static void logDataInBuff( void * vv );

    RtAudio         m_audio_device;
    RtAudio::StreamParameters   m_aud_dev_in_params;
    RtAudio::StreamParameters   m_aud_dev_out_params;
    RtAudio::StreamOptions      m_options;
    unsigned int    m_audio_buffer_frames;      // number of elements of size e.g. double
    unsigned int    m_sampling_freq;
};

#endif // AUDIOSOURCE_H
