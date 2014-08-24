// C++ Standard includes
#include <iostream>

// Qt includes
#include <qlayout.h>
#include <QPushButton>
#include <QMenuBar>
#include <QLabel>

// Qwt includes
#include <qwt_plot_grid.h>

// App includes
#include "mainwindow.h"
#include "audiosource.h"
#include "parameters.h"

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow( parent ), m_infoWindow( nullptr )
{
    for(int i = 0; i < 1024; i++)
    {
        m_qpoint_signal.push_back( QPointF( i, 0) );
    }

    m_signalSource = new audioSource;

    setCentralWidget( new QWidget( this ) );
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing( 5 );
    layout->setMargin( 15 );

    createActions();
    createMenus();

    //------------buttons----------------------------
    QHBoxLayout * hLoutOptionButtons = new QHBoxLayout( );
    QPushButton * buttonOption1 = new QPushButton( "Option_1" );
    QPushButton * buttonOption2 = new QPushButton( "Option_2" );
    QPushButton * buttonOption3 = new QPushButton( "Option_3" );
    QPushButton * buttonOption4 = new QPushButton( "Option_4" );
    QPushButton * buttonOption5 = new QPushButton( "Option_5" );
    QPushButton * buttonOption6 = new QPushButton( "Option_6" );
    QPushButton * buttonOption7 = new QPushButton( "Option_7" );
    hLoutOptionButtons->addWidget( buttonOption1 );
    hLoutOptionButtons->addWidget( buttonOption2 );
    hLoutOptionButtons->addWidget( buttonOption3 );
    hLoutOptionButtons->addWidget( buttonOption4 );
    hLoutOptionButtons->addWidget( buttonOption5 );
    hLoutOptionButtons->addWidget( buttonOption6 );
    hLoutOptionButtons->addWidget( buttonOption7 );

    layout->addLayout( hLoutOptionButtons );

    connect( buttonOption1, SIGNAL( clicked() ), SLOT( actionButtonOption1() ) );
    connect( buttonOption2, SIGNAL( clicked() ), SLOT( actionButtonOption2() ) );
    connect( buttonOption3, SIGNAL( clicked() ), SLOT( actionButtonOption3() ) );
    connect( buttonOption4, SIGNAL( clicked() ), SLOT( actionButtonOption4() ) );
    connect( buttonOption5, SIGNAL( clicked() ), SLOT( actionButtonOption5() ) );
    connect( buttonOption6, SIGNAL( clicked() ), SLOT( actionButtonOption6() ) );
    connect( buttonOption7, SIGNAL( clicked() ), SLOT( actionButtonOption7() ) );

    //------------qwt plot start---------------------
    QString label;
    QwtText text( label );
    m_main_plot = new QwtPlot( text, parent );
    m_main_plot->setCanvasBackground( QColor( Qt::black ) );
    m_main_plot->setAxisScale( QwtPlot::xBottom, 0, ( AUDIO_DEV_BUFFER_FRAMES_NBR - 1 ) );

    const double sampleTime = 1000.0 / AUDIO_DEV_SAMPLING_FREQ;
    QString s = "samples [ 1 smpl/" + QString::number( sampleTime ) + " us]";
    m_main_plot->setAxisTitle( QwtPlot::xBottom, s );
    m_main_plot->setAxisScale( QwtPlot::yLeft, -0.7, 0.7 );
    m_main_plot->setAxisTitle( QwtPlot::yLeft, "signal magnitude [-]" );
    m_main_plot->enableAxis( QwtPlot::yRight, true );
    m_main_plot->setAxisScale( QwtPlot::yRight, -0.7, 0.7 );
    m_main_plot->enableAxis( QwtPlot::xTop, true );
    m_main_plot->setAxisScale( QwtPlot::xTop, 0, ( AUDIO_DEV_BUFFER_FRAMES_NBR - 1 ) );

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setPen( QPen( Qt::green, 0.0, Qt::DotLine ) );
    grid->enableX( true );
    grid->enableXMin( true );
    grid->enableY( true );
    grid->enableYMin( false );
    grid->attach( m_main_plot );

    layout->addWidget( m_main_plot );
    centralWidget()->setLayout( layout );

    // add curve
    m_main_curve = new QwtPlotCurve( "Main curve" );
    m_main_curve->setSamples( m_qpoint_signal );
    m_main_curve->setPen( QPen( Qt::green, qreal(1.5) ) );
    m_main_curve->attach( m_main_plot );

    // finally, refresh the plot
    m_main_plot->replot();
}

void MainWindow::closeEvent( QCloseEvent * event )
{
    if( m_infoWindow != nullptr )
    {
        m_infoWindow->close();
        delete m_infoWindow;
    }
}

MainWindow::~MainWindow()
{
    delete m_signalSource;
}

void MainWindow::timerEvent( QTimerEvent * timerId )
{
    m_signalSource->fillSignal( m_qpoint_signal );
    //replot_curve();
    m_main_curve->setSamples( m_qpoint_signal );
    m_main_plot->replot();
    m_main_plot->setCanvasBackground( QColor( Qt::black ) );
}

/*
 * Use the button with label 'Option_1' to start collecting the samples. Use
 * button 'Option_2' to store the collected samples into file in the working
 * directory.
 */
void MainWindow::actionButtonOption1()
{
    if( m_signalSource->getLogBuff() == true )
    {
        std::cout << "Logging already started..." << std::endl;
    }
    else
    {
        std::cout << "Started samples logging ..." << std::endl;
        m_signalSource->setLogBuff();
    }

}

/*
 * Use button 'Option_2' to store the collected samples into file in the working
 * directory.
 */
void MainWindow::actionButtonOption2()
{
    if( m_signalSource->getLogBuff() == true )
    {
        std::cout << "Still logging..." << std::endl;
    }
    else
    {
        std::cout << "Started storing data ..." << std::endl;
        m_signalSource->setSaveBuffLog();
        m_signalSource->storeDataToFile();
    }
}

void MainWindow::actionButtonOption3()
{
    m_signalSource->fillSignal( m_qpoint_signal );
}

#include "timer.h"

void MainWindow::actionButtonOption4()
{

}

void MainWindow::actionButtonOption5()
{

}

void MainWindow::actionButtonOption6()
{

}

void MainWindow::actionButtonOption7()
{

}

void MainWindow::releaseResources()
{
    m_infoWindow = nullptr;
}

void MainWindow::createActions()
{
    m_newAction = new QAction( tr( "&Info" ), this);
    connect( m_newAction, SIGNAL( triggered() ), this, SLOT( showAppInfo() ) );
}

void MainWindow::createMenus()
{
    m_MenuBar = new QMenuBar(this);
    m_fileMenu = new QMenu("&Info");
    m_fileMenu->addAction(m_newAction);
    m_MenuBar->addMenu(m_fileMenu);
    setMenuBar(m_MenuBar);
}

void MainWindow::showAppInfo()
{
    if( m_infoWindow == nullptr )
    {
        const double microsecond = 1000; // display time in us
        const double sampleTime = microsecond / AUDIO_DEV_SAMPLING_FREQ;
        QString s = "sampling frequency :      " + QString::number( AUDIO_DEV_SAMPLING_FREQ ) + " Hz\n";
        s +=        "                          " + QString::number( sampleTime ) + " us per sample\n";
        s +=        "audio buffer filled in :  " + QString::number( sampleTime * AUDIO_DEV_BUFFER_FRAMES_NBR ) + " us\n";
        s +=        "                          " + QString::number( microsecond/(sampleTime * AUDIO_DEV_BUFFER_FRAMES_NBR) ) + " Hz\n";
        s +=        "audio server :            " + QString( AUDIO_SERVER ) + "\n";
        s +=        "library used :            " + QString( LIBS_USED ) + "\n";

        QLabel * lbl = new QLabel;
        lbl->setFont( QFont( "Monospace", 12 ) );
        lbl->setText( s );

        QVBoxLayout * vbl = new QVBoxLayout();
        vbl->addWidget( lbl );

        m_infoWindow = new QWidget();
        m_infoWindow->setLayout( vbl );
        m_infoWindow->resize( 320, 240 );
        m_infoWindow->setAttribute( Qt::WA_DeleteOnClose );
        connect ( m_infoWindow, SIGNAL( destroyed() ), this, SLOT( releaseResources() ) );
        m_infoWindow->show();
    }
}
