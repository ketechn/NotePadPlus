/***********************************************************************************
 * 文件名 : CenterWidget.h
 * 负责人 :
 * 创建日期 :
 * 文件描述 : MainWindow中心组建类
 * 版权说明 :
 * 其它说明 :
 * 修改日志 :
***********************************************************************************/
#ifndef _CENTERWIDGET_H_
#define _CENTERWIDGET_H_

#include <QWidget>
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include "Calculator.h"
#include "CenterWidget.h"
#include "Common.h"
#include "DrawingBoard.h"
#include "SerialPort.h"

class CenterWidget : public QWidget
{
    Q_OBJECT

    QHBoxLayout* mainLayout;
    QPlainTextEdit* mainEditor;
    Calculator* mainCalculator;
    DrawingBoard* mainDrawingBoard;
    SerialPort* mainSerialPort;

    explicit CenterWidget(QWidget* parent = 0);
    bool construct();

    void addCalculator();
    void removeCalculator();
    void addDrawingBoard();
    void removeDrawingBoard();
    void addSerialPort();
    void removeSerialPort();

public:
    static CenterWidget* NewInstance();
    QPlainTextEdit* getMainEditor();
    void transMode(Mode mode);

private:
    Mode currentMode;
    
signals:
    
public slots:
    void CalculatorProcessSlot(QQueue<QString>);
    void SerialPortOpenSlot();
    void SerialPortCloseSlot();
    void SerialPortClearSlot();
    void SerialPortReadSlot();
    void SerialPortAutoEndSlot();
};

#endif //_CENTERWIDGET_H_
