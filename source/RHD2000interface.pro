QMAKE_CXXFLAGS += -std=c++11
TEMPLATE      = app

QT            += widgets
greaterThan(4, QT_MAJOR_VERSION): QT += multimedia
CONFIG        += static

HEADERS       = \
    okFrontPanelDLL.h \
    rhd2000evalboard.h \
    rhd2000registers.h \
    rhd2000datablock.h \
    waveplot.h \
    mainwindow.h \
    signalprocessor.h \
    bandwidthdialog.h \
    renamechanneldialog.h \
    signalchannel.h \
    signalgroup.h \
    signalsources.h \
    spikescopedialog.h \
    spikeplot.h \
    keyboardshortcutdialog.h \
    randomnumber.h \
    impedancefreqdialog.h \
    globalconstants.h \
    triggerrecorddialog.h \
    setsaveformatdialog.h \
    helpdialoghighpassfilter.h \
    helpdialognotchfilter.h \
    helpdialogdacs.h \
    helpdialogcomparators.h \
    helpdialogchipfilters.h \
    qtincludes.h \
    auxdigoutconfigdialog.h \
    cabledelaydialog.h \
    helpdialogfastsettle.h \
    impedancefreqListdialog.h

SOURCES       = main.cpp \
    okFrontPanelDLL.cpp \
    rhd2000evalboard.cpp \
    rhd2000registers.cpp \
    rhd2000datablock.cpp \
    waveplot.cpp \
    mainwindow.cpp \
    signalprocessor.cpp \
    bandwidthdialog.cpp \
    renamechanneldialog.cpp \
    signalchannel.cpp \
    signalgroup.cpp \
    signalsources.cpp \
    spikescopedialog.cpp \
    spikeplot.cpp \
    keyboardshortcutdialog.cpp \
    randomnumber.cpp \
    impedancefreqdialog.cpp \
    triggerrecorddialog.cpp \
    setsaveformatdialog.cpp \
    helpdialoghighpassfilter.cpp \
    helpdialognotchfilter.cpp \
    helpdialogdacs.cpp \
    helpdialogcomparators.cpp \
    helpdialogchipfilters.cpp \
    auxdigoutconfigdialog.cpp \
    cabledelaydialog.cpp \
    helpdialogfastsettle.cpp \
    impedancefreqListdialog.cpp
    
RESOURCES     = RHD2000interface.qrc
LIBS+=-lm
LIBS+=-ldl

#the make file will be put in shadow folder root
CONFIG(debug, debug|release) {
    DESTDIR = debug/bin
    OBJECTS_DIR = debug/.obj
    MOC_DIR = debug/.moc
    RCC_DIR = debug/.rcc
    UI_DIR = debug/.ui
    #QMAKE_MAKEFILE = debug/Makefile #the qtcreator cannot work with QMAKE_MAKEFILE

} else {
    DESTDIR = release/bin
    OBJECTS_DIR = release/.obj
    MOC_DIR = release/.moc
    RCC_DIR = release/.rcc
    UI_DIR = release/.ui
    #QMAKE_MAKEFILE = release/Makefile #the qtcreator cannot work with QMAKE_MAKEFILE
    DEFINES += QT_NO_DEBUG_OUTPUT
}
QMAKE_CFLAGS_RELEASE -= -O2
QMAKE_CFLAGS_RELEASE += -O3
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
