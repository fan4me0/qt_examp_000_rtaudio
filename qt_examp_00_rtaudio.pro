#-------------------------------------------------
#
# Project created by QtCreator 2014-07-01T14:29:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_examp_00_rtaudio
TEMPLATE = app


SOURCES += main.cpp         \
        mainwindow.cpp      \
        audiosource.cpp     \
        ../../../../../builds/libs/stk/stk-4.5.0/src/RtAudio.cpp \
    threadstoredata.cpp

HEADERS  += mainwindow.h    \
        audiosource.h       \
        audiosource.h \
    parameters.h \
    threadstoredata.h

#------------------------------------------------------------
# Compiler settings

QMAKE_CXXFLAGS += -std=c++11

#------------------------------------------------------------
# Qwt library settings

unix:!macx: LIBS += -L$$PWD/../../../../../builds/libs/qwt/qwt_620_trunk140414/lib/ -lqwt

INCLUDEPATH += $$PWD/../../../../../builds/libs/qwt/qwt_620_trunk140414/src
DEPENDPATH += $$PWD/../../../../../builds/libs/qwt/qwt_620_trunk140414/src

#------------------------------------------------------------
# STK library settings

DEFINES     += __LINUX_PULSE__
INCLUDEPATH += /home/franto/builds/libs/stk/stk-4.5.0/include
LIBS += -lpulse-simple -lpulse

#DEFINES     += __UNIX_JACK__
#INCLUDEPATH += /home/franto/builds/libs/stk/stk-4.5.0/include
#LIBS += -lasound -ljack

#DEFINES     += __LINUX_ALSA__
#INCLUDEPATH += /home/franto/builds/libs/stk/stk-4.5.0/include
#LIBS += -lasound

OTHER_FILES += \
    README.md
