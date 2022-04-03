/***********************************************************************************
 * 文件名 : SerialPort.h
 * 负责人 :
 * 创建日期 :
 * 文件描述 : 串口类
 * 版权说明 :
 * 其它说明 :
 * 修改日志 :
***********************************************************************************/
#ifndef _SERIALPORT_H_
#define _SERIALPORT_H_

#include <QWidget>
#include "win_qextserialport.h"
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

class SerialPort : public QWidget
{
    Q_OBJECT

    /*串口相关*/
    Win_QextSerialPort* SerialPortDev;/*串口设备*/
    QLabel* SerialPort_Number_Label;/*串口号标签*/
    QLabel* SerialPort_BaudRate_Label;/*波特率标签*/
    QLabel* SerialPort_DataBits_Label;/*数据位标签*/
    QLabel* SerialPort_Parity_Label;/*奇偶校验位标签*/
    QLabel* SerialPort_StopBits_Label;/*停止位标签*/
    QComboBox* SerialPort_Number_Box;/*串口号下拉框*/
    QComboBox* SerialPort_BaudRate_Box;/*波特率下拉框*/
    QComboBox* SerialPort_DataBits_Box;/*数据位下拉框*/
    QComboBox* SerialPort_Parity_Box;/*奇偶校验位下拉框*/
    QComboBox* SerialPort_StopBits_Box;/*停止位下拉框*/
    QPushButton* SerialPort_clear;
    QPushButton* SerialPort_open;
    QPushButton* SerialPort_close;
    QPushButton* SerialPort_write;
    QLabel* SerialPort_Status;
    QLineEdit* SerialPort_SendLine;

signals:
    void clearSignal();
    void openSignal();
    void closeSignal();

public:
    explicit SerialPort(QWidget* parent = 0);
    Win_QextSerialPort* getSerialPortDev();
    
protected slots:
    void clickSerialOpenButton();
    void clickSerialCloseButton();
    void clickSerialSendButton();
    void clickSerialClearButton();
};

#endif //_SERIALPORT_H_
