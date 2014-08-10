#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Qt includes
#include <QMainWindow>
#include <QVector>
#include <QPointF>

// Qwt includes
#include <qwt_plot.h>
#include <qwt_plot_curve.h>

// App includes
#include "audiosource.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void actionButtonOption1();
    void actionButtonOption2();
    void actionButtonOption3();
    void actionButtonOption4();
    void actionButtonOption5();
    void actionButtonOption6();
    void actionButtonOption7();

private:
    void timerEvent(QTimerEvent * timerId );    // override of QObject 'virtual protected'
    audioSource     * m_signalSource;
    QwtPlot         * m_main_plot;
    QwtPlotCurve    * m_main_curve;
    QVector<QPointF>    m_qpoint_signal;
};

#endif // MAINWINDOW_H
