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
    enum stream_index
    {
        STREAM_0,
        STREAM_1
    };
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
    static int audioBufferStream0( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                                   double streamTime, RtAudioStreamStatus status, void *data );
    void processData( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                      double streamTime, RtAudioStreamStatus status, void *data );

    static QVector<audioSource *>    m_stream_list;
    std::mutex foo, boo;
    bool log_buff;
    bool save_buff_log;
    bool m_stat_time;
    static volatile bool lock_fill;
    #if defined(SAMPLE_FORMAT_FLOAT64)
        QVector<QPointF>    m_qpoint_signal;
    #else
        #error Error: define sample fotmat in parameters.h.
    #endif
    std::vector<std::vector<double>> audio_log;
    void statTime();
    void logDataInBuff( void * vv );

    RtAudio         m_audio_device;
    RtAudio::StreamParameters   m_aud_dev_in_params;
    RtAudio::StreamParameters   m_aud_dev_out_params;
    RtAudio::StreamOptions      m_options;
    unsigned int    m_audio_buffer_frames;      // number of elements of size e.g. double
    unsigned int    m_sampling_freq;
    std::string     m_stream_name;
};

#endif // AUDIOSOURCE_H
