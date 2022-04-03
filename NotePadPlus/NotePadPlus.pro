#-------------------------------------------------
#
# Project created by QtCreator 2019-03-02T14:53:05
#
#-------------------------------------------------

QT       += core gui

TARGET = NotePadCalc
TEMPLATE = app


SOURCES += main.cpp \
    MainWindowUI.cpp \
    MainWindowSlots.cpp \
    FindDialog.cpp \
    ReplaceDialog.cpp \
    AboutDialog.cpp \
    AppConfig.cpp \
    CalCulatorUI.cpp \
    CalCulatorDec.cpp \
    Calculator.cpp \
    CenterWidget.cpp \
    DrawingBoard.cpp \
    win_qextserialport.cpp \
    qextserialbase.cpp \
    SerialPort.cpp

HEADERS  += MainWindow.h \
    FindDialog.h \
    ReplaceDialog.h \
    AboutDialog.h \
    AppConfig.h \
    ICalculator.h \
    CalCulatorUI.h \
    CalCulatorDec.h \
    Calculator.h \
    CenterWidget.h \
    Common.h \
    DrawingBoard.h \
    win_qextserialport.h \
    qextserialbase.h \
    SerialPort.h

RESOURCES += \
    Res.qrc
