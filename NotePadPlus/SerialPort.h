/***********************************************************************************
 * �ļ��� : SerialPort.h
 * ������ :
 * �������� :
 * �ļ����� : ������
 * ��Ȩ˵�� :
 * ����˵�� :
 * �޸���־ :
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

    /*�������*/
    Win_QextSerialPort* SerialPortDev;/*�����豸*/
    QLabel* SerialPort_Number_Label;/*���ںű�ǩ*/
    QLabel* SerialPort_BaudRate_Label;/*�����ʱ�ǩ*/
    QLabel* SerialPort_DataBits_Label;/*����λ��ǩ*/
    QLabel* SerialPort_Parity_Label;/*��żУ��λ��ǩ*/
    QLabel* SerialPort_StopBits_Label;/*ֹͣλ��ǩ*/
    QComboBox* SerialPort_Number_Box;/*���ں�������*/
    QComboBox* SerialPort_BaudRate_Box;/*������������*/
    QComboBox* SerialPort_DataBits_Box;/*����λ������*/
    QComboBox* SerialPort_Parity_Box;/*��żУ��λ������*/
    QComboBox* SerialPort_StopBits_Box;/*ֹͣλ������*/
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
