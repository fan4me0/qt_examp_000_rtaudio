// C++ Standard includes
#include <iterator>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <mutex>
#include <unistd.h>  // getpid()
#include <chrono>

#if defined(__UNIX_JACK__)
    #include <jack/jack.h>
#endif

// Qt includes
#include <QThreadPool>

// RtAudio includes
#include "RtAudio.h"

// App includes
#include "audiosource.h"
#include "parameters.h"
#include "threadstoredata.h"


bool audioSource::log_buff;
bool audioSource::save_buff_log;
std::mutex foo, boo;
bool audioSource::m_stat_time = false;

static int signal_iter = 0;
#if defined(SAMPLE_FORMAT_FLOAT64)
    static QVector<QPointF>    m_qpoint_signal( AUDIO_DEV_BUFFER_FRAMES_NBR );
#else
    #error Error: define sample fotmat in parameters.h.
#endif

int audioSource::audio_buffer_full( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                                double streamTime, RtAudioStreamStatus status, void *data )
{
    statTime();  // start to print callback stats to stdout via button 'Start/stop stat'

    // via '*data' parameter possible to recognize audio stream-callback relation
    //std::cout << static_cast<RtAudio::StreamOptions*>(data)->streamName << std::endl;

    // Since the number of input and output channels is equal, we can do
    // a simple buffer copy operation here.
    logDataInBuff( inputBuffer );

    if ( status ) std::cout << "Stream over/underflow detected." << std::endl;

    std::lock (foo, boo);
    for(; signal_iter < AUDIO_DEV_BUFFER_FRAMES_NBR; signal_iter++)
    {
        ::m_qpoint_signal[signal_iter] = QPointF( signal_iter, ((SAMPLE_FORMAT_TYPE*)inputBuffer)[signal_iter] );
        //((SAMPLE_FORMAT_TYPE*)outputBuffer)[signal_iter] = ((SAMPLE_FORMAT_TYPE*)inputBuffer)[signal_iter];
    }
    foo.unlock();
    boo.unlock();

    return 0;
}

void audioSource::statTime()
{
    namespace ns_chr = std::chrono;
    static ns_chr::high_resolution_clock::time_point t1;
    static ns_chr::high_resolution_clock::time_point t2;
    static int nbr_call = 0;
    static ns_chr::duration<double> time_span_sum{0};

    t2 = ns_chr::high_resolution_clock::now();

    if( m_stat_time == true )
    {
        nbr_call++;
        ns_chr::duration<double> time_span = t2 - t1;
        time_span_sum += time_span;
        std::cout << "Average callback period is : " << time_span_sum.count()/nbr_call<< " s" << std::endl;
        //std::cout << nbr_call << " : " << duration<double,std::milli>(time_span).count() << " ms" << std::endl;
        std::cout << nbr_call << " : " << time_span.count() << " s" << std::endl;
    }
    else
    {
        nbr_call = 0;
        time_span_sum = ns_chr::high_resolution_clock::duration::zero();
    }

    t1 = t2;
}

void audioSource::statTimeToogle()
{
    if( m_stat_time == true )
        m_stat_time = false;
    else
        m_stat_time = true;
}

audioSource::audioSource( unsigned int sampl_freq ) : m_sampling_freq( sampl_freq )
{
    log_buff = false;
    save_buff_log = false;
    if ( m_audio_device.getDeviceCount() < 1 )
    {
        std::cout << "\nNo audio devices found!\n";
        exit( 0 );
    }

    m_aud_dev_in_params.nChannels = AUDIO_DEV_CHANNEL_NBR;
    m_audio_buffer_frames = AUDIO_DEV_BUFFER_FRAMES_NBR;

    // iDevice = 0;  -> Device Name = Default Device - duplex mode
    // iDevice = 5;  -> Device Name = Mic in at rear panel (Pink) (Realtek High Definition Audio)
    //                  !!! This majk has to be than set as default in the system 'control panel->sound->recording'
    // iDevice = 8;  -> Device Name = Microphone (3- USB Audio CODEC ) - external 'Alesis' mixpult
    unsigned int iDevice = 0, oDevice = 0;
    if ( iDevice == 0 )
        m_aud_dev_in_params.deviceId = m_audio_device.getDefaultInputDevice();
    else
        m_aud_dev_in_params.deviceId = iDevice - 1;

    m_aud_dev_in_params.firstChannel = AUDIO_DEV_IN_FISRT_CHANNEL_OFFSET;

    if ( oDevice == 0 )
        m_aud_dev_out_params.deviceId = m_audio_device.getDefaultOutputDevice();
    else
        m_aud_dev_out_params.deviceId = oDevice - 1;

    m_aud_dev_out_params.nChannels = AUDIO_DEV_CHANNEL_NBR;
    m_aud_dev_out_params.firstChannel = AUDIO_DEV_OUT_FISRT_CHANNEL_OFFSET;

    // set unique name to recognize multiple instances
    m_options.streamName = "pid_" + std::to_string( getpid() ) + "_stream_0";

    try {
        // !!! if want to use input and output and one of them is aquired from duplex device, second one has to be as well
        // first variant for input only mode
        m_audio_device.openStream( nullptr,                // RtAudio::StreamParameters for out
                                   &m_aud_dev_in_params,   // RtAudio::StreamParameters for in
                                   SAMPLE_FORMAT,          // RtAudioFormat
                                   m_sampling_freq,        // unsigned int sampleRate
                                   &m_audio_buffer_frames, // unsigned int *bufferFrames
                                   &audio_buffer_full,     // RtAudioCallback
                                   &m_options,             // void *userData = NULL
                                   &m_options  );          // RtAudio::StreamOptions *options = NULL

        // second variant is a must for duplex mode
//        m_audio_device.openStream( &m_aud_dev_out_params,  // RtAudio::StreamParameters for out
//                                   &m_aud_dev_in_params,   // RtAudio::StreamParameters for in
//                                   SAMPLE_FORMAT,          // RtAudioFormat
//                                   m_sampling_freq,        // unsigned int sampleRate
//                                   &m_audio_buffer_frames, // unsigned int *bufferFrames
//                                   &audio_buffer_full,     // RtAudioCallback
//                                   &m_options,             // void *userData = NULL
//                                   &m_options );           // RtAudio::StreamOptions *options = NULL
    }
    catch ( RtAudioError& e ) {
        std::cout << '\n' << e.getMessage() << '\n' << std::endl;
        exit( 1 );
    }

    // start audio stream
    try {
        m_audio_device.startStream();
    }
    catch ( RtAudioError& e ) {
        std::cout << '\n' << e.getMessage() << '\n' << std::endl;
    }

#if defined(__UNIX_JACK__)
    std::cout << "Number of frames/period in JACK is: "
              << jack_get_buffer_size( (jack_client_t*) & (m_options.streamName) )
              << std::endl;
#endif
}

audioSource::~audioSource()
{
    if ( m_audio_device.isStreamRunning() )
    {
        m_audio_device.stopStream();
    }
}


const int row_elements = AUDIO_DEV_BUFFER_FRAMES_NBR;

void audioSource::setLogBuff()
{
    log_buff = true;
}

bool audioSource::getLogBuff()
{
    return log_buff;
}

void audioSource::setSaveBuffLog()
{
    save_buff_log = true;
}

static std::vector<std::vector<double>> audio_log( ROW_NBR );

void audioSource::logDataInBuff( void *inputBuffer )
{
    static int log_iter = 0;

    if( log_buff == true )
    {
        int iter = 0;
        for( ; iter < row_elements; iter++)
        {
            ::audio_log[ log_iter ].push_back(((double*)inputBuffer)[iter]);
        }

        log_iter++;
        if( log_iter == ROW_NBR )
        {
            log_iter = 0;
            log_buff = false;
            std::cout << "Finished sample logging ..." << std::endl;
        }
    }
}

void audioSource::fillSignal( QVector<QPointF> & vector )
{
    std::lock ( foo, boo );
    vector = ::m_qpoint_signal;
    foo.unlock();
    boo.unlock();
    signal_iter = 0;
}

void audioSource::storeDataToFile()
{
    threadStoreData *threadd = new threadStoreData();
    threadd->setPointer( ::audio_log );
    // QThreadPool takes ownership and deletes 'threadd' automatically
    QThreadPool::globalInstance()->start( threadd );
}
