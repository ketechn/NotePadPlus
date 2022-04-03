/***********************************************************************************
 * 文件名 : SerialPort.cpp
 * 负责人 :
 * 创建日期 :
 * 文件描述 : 串口类
 * 版权说明 :
 * 其它说明 :
 * 修改日志 :
***********************************************************************************/
#include "SerialPort.h"
#include <QDebug>

/*****************************************************************
** 函数名: SerialPort(QWidget *parent)
** 输　入: QWidget *parent
** 输　出: 无
** 返回值: 无
** 功能描述:串口类界面，连接信号与槽
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
SerialPort::SerialPort(QWidget* parent) : QWidget(parent)
{
    /*串口设置第一行：端口号*/
    SerialPort_Number_Label = new QLabel(this);
    SerialPort_Number_Label->move(10, 10);
    SerialPort_Number_Label->resize(60, 25);
    SerialPort_Number_Label->setText("端口号");

    SerialPort_Number_Box = new QComboBox(this);
    SerialPort_Number_Box->move(90, 10);
    SerialPort_Number_Box->resize(70, 20);
    SerialPort_Number_Box->addItem("COM1");
    SerialPort_Number_Box->addItem("COM2");
    SerialPort_Number_Box->addItem("COM3");
    SerialPort_Number_Box->addItem("COM4");
    SerialPort_Number_Box->addItem("COM5");
    SerialPort_Number_Box->addItem("COM6");
    SerialPort_Number_Box->addItem("COM7");
    SerialPort_Number_Box->addItem("COM8");
    SerialPort_Number_Box->addItem("COM9");
    SerialPort_Number_Box->addItem("COM10");
    SerialPort_Number_Box->addItem("COM11");
    SerialPort_Number_Box->addItem("COM12");
    SerialPort_Number_Box->addItem("COM13");
    SerialPort_Number_Box->addItem("COM14");
    SerialPort_Number_Box->addItem("COM15");
    SerialPort_Number_Box->addItem("COM16");
    SerialPort_Number_Box->addItem("COM17");
    SerialPort_Number_Box->addItem("COM18");
    SerialPort_Number_Box->addItem("COM19");
    SerialPort_Number_Box->addItem("COM20");
    SerialPort_Number_Box->addItem("COM21");
    SerialPort_Number_Box->addItem("COM22");
    SerialPort_Number_Box->addItem("COM23");
    SerialPort_Number_Box->addItem("COM24");
    SerialPort_Number_Box->addItem("COM25");
    SerialPort_Number_Box->addItem("COM26");
    SerialPort_Number_Box->addItem("COM27");
    SerialPort_Number_Box->addItem("COM28");
    SerialPort_Number_Box->addItem("COM29");

    /*串口设置第二行：波特率*/
    SerialPort_BaudRate_Label = new QLabel(this);
    SerialPort_BaudRate_Label->move(10, 40);
    SerialPort_BaudRate_Label->resize(60, 25);
    SerialPort_BaudRate_Label->setText("波特率");

    SerialPort_BaudRate_Box = new QComboBox(this);
    SerialPort_BaudRate_Box->move(90, 40);
    SerialPort_BaudRate_Box->resize(70, 20);
    SerialPort_BaudRate_Box->addItem("110");
    SerialPort_BaudRate_Box->addItem("300");
    SerialPort_BaudRate_Box->addItem("600");
    SerialPort_BaudRate_Box->addItem("1200");
    SerialPort_BaudRate_Box->addItem("2400");
    SerialPort_BaudRate_Box->addItem("4800");
    SerialPort_BaudRate_Box->addItem("9600");
    SerialPort_BaudRate_Box->addItem("14400");
    SerialPort_BaudRate_Box->addItem("19200");
    SerialPort_BaudRate_Box->addItem("38400");
    SerialPort_BaudRate_Box->addItem("56000");
    SerialPort_BaudRate_Box->addItem("57600");
    SerialPort_BaudRate_Box->addItem("115200");
    SerialPort_BaudRate_Box->addItem("128000");
    SerialPort_BaudRate_Box->addItem("256000");

    /*串口设置第三行：奇偶校验*/
    SerialPort_Parity_Label = new QLabel(this);
    SerialPort_Parity_Label->move(10, 70);
    SerialPort_Parity_Label->resize(60, 25);
    SerialPort_Parity_Label->setText("奇偶校验");

    SerialPort_Parity_Box = new QComboBox(this);
    SerialPort_Parity_Box->move(90, 70);
    SerialPort_Parity_Box->resize(70, 20);
    SerialPort_Parity_Box->addItem("无");
    SerialPort_Parity_Box->addItem("奇校验");
    SerialPort_Parity_Box->addItem("偶校验");
    SerialPort_Parity_Box->addItem("标记");
    SerialPort_Parity_Box->addItem("空格");

    /*串口设置第四行：数据位*/
    SerialPort_DataBits_Label = new QLabel(this);
    SerialPort_DataBits_Label->move(10, 100);
    SerialPort_DataBits_Label->resize(60, 25);
    SerialPort_DataBits_Label->setText("数据位");

    SerialPort_DataBits_Box = new QComboBox(this);
    SerialPort_DataBits_Box->move(90, 100);
    SerialPort_DataBits_Box->resize(70, 20);
    SerialPort_DataBits_Box->addItem("8");
    SerialPort_DataBits_Box->addItem("7");
    SerialPort_DataBits_Box->addItem("6");
    SerialPort_DataBits_Box->addItem("5");

    /*串口设置第五行：停止位*/
    SerialPort_StopBits_Label = new QLabel(this);
    SerialPort_StopBits_Label->move(10, 130);
    SerialPort_StopBits_Label->resize(60, 25);
    SerialPort_StopBits_Label->setText("停止位");

    SerialPort_StopBits_Box = new QComboBox(this);
    SerialPort_StopBits_Box->move(90, 130);
    SerialPort_StopBits_Box->resize(70, 20);
    SerialPort_StopBits_Box->addItem("1");
    SerialPort_StopBits_Box->addItem("1.5");
    SerialPort_StopBits_Box->addItem("2");

    SerialPort_open = new QPushButton(this);
    SerialPort_open->move(180, 10);
    SerialPort_open->resize(50, 25);
    SerialPort_open->setText("打开");

    SerialPort_close = new QPushButton(this);
    SerialPort_close->move(250, 10);
    SerialPort_close->resize(50, 25);
    SerialPort_close->setText("关闭");

    SerialPort_clear = new QPushButton(this);
    SerialPort_clear->move(320, 10);
    SerialPort_clear->resize(50, 25);
    SerialPort_clear->setText("清空");

    SerialPort_Status = new QLabel(this);
    SerialPort_Status->move(180, 40);
    SerialPort_Status->resize(125, 25);
    SerialPort_Status->setText("端口关闭");

    SerialPort_SendLine = new QLineEdit(this);
    SerialPort_SendLine->move(10, 160);
    SerialPort_SendLine->resize(350, 30);

    SerialPort_write = new QPushButton(this);
    SerialPort_write->move(10, 200);
    SerialPort_write->resize(50, 25);
    SerialPort_write->setText("发送");

    setFixedSize(400, 600);

    /*串口设备*/
    SerialPortDev = NULL;
    connect(SerialPort_open, SIGNAL(clicked()), this, SLOT(clickSerialOpenButton()));
    connect(SerialPort_close, SIGNAL(clicked()), this, SLOT(clickSerialCloseButton()));
    connect(SerialPort_write, SIGNAL(clicked()), this, SLOT(clickSerialSendButton()));
    connect(SerialPort_clear, SIGNAL(clicked()), this, SLOT(clickSerialClearButton()));
}

/*****************************************************************
** 函数名: clickSerialOpenButton()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:串口打开槽函数，创建串口硬件类
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void SerialPort::clickSerialOpenButton()
{
    /*如果串口设备指针不为空，即原来打开过串口设备，则先关闭原来的串口并释放对应的内存空间*/
    if(SerialPortDev != NULL)
    {
        SerialPortDev->close();
        delete SerialPortDev;
        SerialPortDev = NULL;
    }

    SerialPortDev = new Win_QextSerialPort(SerialPort_Number_Box->currentText(), QextSerialBase::EventDriven);

    if(SerialPortDev != NULL)
    {
        switch(SerialPort_BaudRate_Box->currentText().toInt(NULL, 10))
        {
            case 110: SerialPortDev->setBaudRate(BAUD110);break;
            case 300: SerialPortDev->setBaudRate(BAUD300);break;
            case 600: SerialPortDev->setBaudRate(BAUD600);break;
            case 1200: SerialPortDev->setBaudRate(BAUD1200);break;
            case 2400: SerialPortDev->setBaudRate(BAUD2400);break;
            case 4800: SerialPortDev->setBaudRate(BAUD4800);break;
            case 9600: SerialPortDev->setBaudRate(BAUD9600);break;
            case 14400: SerialPortDev->setBaudRate(BAUD14400);break;
            case 19200: SerialPortDev->setBaudRate(BAUD19200);break;
            case 38400: SerialPortDev->setBaudRate(BAUD38400);break;
            case 56000: SerialPortDev->setBaudRate(BAUD56000);break;
            case 115200: SerialPortDev->setBaudRate(BAUD115200);break;
            case 128000: SerialPortDev->setBaudRate(BAUD128000);break;
            case 256000: SerialPortDev->setBaudRate(BAUD256000);break;
            default:break;
        }

        switch(SerialPort_DataBits_Box->currentText().toInt(NULL, 10))
        {
            case 5: SerialPortDev->setDataBits(DATA_5);break;
            case 6: SerialPortDev->setDataBits(DATA_6);break;
            case 7: SerialPortDev->setDataBits(DATA_7);break;
            case 8: SerialPortDev->setDataBits(DATA_8);break;
            default:break;
        }

        if(SerialPort_Parity_Box->currentText() == "NONE")
        {
            SerialPortDev->setParity(PAR_NONE);
        }
        else if(SerialPort_Parity_Box->currentText() == "ODD")
        {
            SerialPortDev->setParity(PAR_ODD);
        }
        else if(SerialPort_Parity_Box->currentText() == "EVEN")
        {
            SerialPortDev->setParity(PAR_EVEN);
        }
        else if(SerialPort_Parity_Box->currentText() == "MARK")
        {
            SerialPortDev->setParity(PAR_MARK);
        }
        else if(SerialPort_Parity_Box->currentText() == "SPACE")
        {
            SerialPortDev->setParity(PAR_SPACE);
        }

        if(SerialPort_StopBits_Box->currentText() == "1")
        {
            SerialPortDev->setStopBits(STOP_1);
        }
        else if(SerialPort_StopBits_Box->currentText() == "1.5")
        {
            SerialPortDev->setStopBits(STOP_1_5);
        }
        else if(SerialPort_StopBits_Box->currentText() == "2")
        {
            SerialPortDev->setStopBits(STOP_2);
        }

        SerialPortDev->setFlowControl(FLOW_OFF);      //控制流

        SerialPortDev->setTimeout(-1);              //设置时间间隔

        if(SerialPortDev->open(QIODevice::ReadWrite))
        {
            SerialPort_Status->setText(QString(SerialPort_Number_Box->currentText()) + QString("打开成功!"));
            emit openSignal(); //发送串口打开信号
        }
        else
        {
            SerialPort_Status->setText(QString(SerialPort_Number_Box->currentText()) + QString("打开失败!"));

            SerialPortDev->close();

            delete SerialPortDev;

            SerialPortDev = NULL;
        }
    }
    else
    {
        SerialPort_Status->setText(QString(SerialPort_Number_Box->currentText()) + QString("打开失败!"));
    }
}

/*****************************************************************
** 函数名: clickSerialCloseButton()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:串口关闭槽函数，释放串口硬件类，发送串口关闭信号
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void SerialPort::clickSerialCloseButton()
{
    if(SerialPortDev != NULL)
    {
        emit closeSignal();

        SerialPortDev->close();

        delete SerialPortDev;

        SerialPortDev = NULL;
    }

    SerialPort_Status->setText("串口关闭");
}

/*****************************************************************
** 函数名: clickSerialSendButton()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:向串口发送数据
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void SerialPort::clickSerialSendButton()
{
    QString qs = SerialPort_SendLine->text();

    if(SerialPortDev != NULL && SerialPortDev->isOpen())
    {
        SerialPortDev->write(SerialPort_SendLine->text().toLatin1().data());
    }
}

/*****************************************************************
** 函数名: clickSerialClearButton()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:向中央组件发送清空文本框信号
** 作　者:
** 日　期:
** 说　明:信号的定义形式跟函数接口相同，但没有函数接口的实现
******************************************************************/
void SerialPort::clickSerialClearButton()
{
    emit clearSignal();
}

/*****************************************************************
** 函数名: getSerialPortDev()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:返回串口硬件类
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
Win_QextSerialPort* SerialPort::getSerialPortDev()
{
    return SerialPortDev;
}
