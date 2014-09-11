#-------------------------------------------------
#
# Project created by QtCreator 2014-07-01T14:29:31
#
#-------------------------------------------------

QT       += core gui widgets

TARGET   = qt_examp_000_rtaudio
TEMPLATE = app

#------------------------------------------------------------
# RtAudio library settings
RTAUDIO_PATH        = /home/franto/builds/libs/rtaudio/rtaudio-4.1.1
RTAUDIO_PATH_INC    = $${RTAUDIO_PATH}
RTAUDIO_PATH_INC2   = $${RTAUDIO_PATH}/include

DEFINES     += __LINUX_PULSE__
INCLUDEPATH += $${STK_PATH_INC}
LIBS        += -lpulse-simple -lpulse

#DEFINES     += __UNIX_JACK__
#INCLUDEPATH += $${STK_PATH_INC}
#LIBS        += -lasound -ljack

#DEFINES     += __LINUX_ALSA__
#INCLUDEPATH += $${STK_PATH_INC}
#LIBS        += -lasound

#------------------------------------------------------------
# STK library settings
STK_PATH        = /home/franto/builds/libs/stk/stk-4.5.0
STK_PATH_INC    = $${STK_PATH}/include
STK_PATH_SRC    = $${STK_PATH}/src
STK_PATH_SRC_INC = $${STK_PATH}/src/include
STK_PATH_LIB    = $${STK_PATH}/src

#------------------------------------------------------------
# Qwt library settings
QWT_PATH        = /home/franto/builds/libs/qwt/qwt_620_trunk140414
QWT_PATH_INC    = $${QWT_PATH}/src
QWT_PATH_LIB    = $${QWT_PATH}/lib

win32:CONFIG(release, debug|release):    LIBS += -L$$PWD/../../builds/libs/qwt/qwt_620_trunk140414/lib/release/ -lqwt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../builds/libs/qwt/qwt_620_trunk140414/lib/debug/ -lqwt
else:unix: LIBS += -L$${QWT_PATH_LIB} -lqwt

INCLUDEPATH += $${QWT_PATH_INC}
DEPENDPATH  += $${QWT_PATH_INC}

#------------------------------------------------------------
# Compiler settings

QMAKE_CXXFLAGS += -std=c++11

#------------------------------------------------------------
# Source files
SOURCES += main.cpp         \
        mainwindow.cpp      \
        audiosource.cpp     \
    threadstoredata.cpp \
    $${RTAUDIO_PATH}/RtAudio.cpp

HEADERS  += mainwindow.h    \
        audiosource.h       \
        audiosource.h \
    parameters.h \
    threadstoredata.h \
    timer.h

#------------------------------------------------------------
# Other files
OTHER_FILES += \
    README.md
