// Qt includes
#include <QApplication>

// App includes
#include "audiosource.h"
#include "mainwindow.h"

int main( int argc, char *argv[] )
{
    //audioSource audioInput;

    QApplication a( argc, argv );
    MainWindow w;
    w.startTimer( 20 );
    w.show();

    return a.exec();
}
