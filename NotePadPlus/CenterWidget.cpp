/***********************************************************************************
 * 文件名 : CenterWidget.cpp
 * 负责人 :
 * 创建日期 :
 * 文件描述 : MainWindow中心组建类
 * 版权说明 :
 * 其它说明 :
 * 修改日志 :
***********************************************************************************/
#include "CenterWidget.h"

/*****************************************************************
** 函数名: CenterWidget
** 输　入: QWidget* parent
** 输　出: 无
** 返回值: 无
** 功能描述:中央组件类构造函数
** 作　者:
** 日　期:
** 说　明: 初始默认为只有文本组件模式
******************************************************************/
CenterWidget::CenterWidget(QWidget* parent) : QWidget(parent)
{
    currentMode = TextEditOnlyMode;
}

/*****************************************************************
** 函数名: construct()
** 输　入: 无
** 输　出: 无
** 返回值: bool
** 功能描述:中央组件类二阶构造
** 作　者:
** 日　期:
** 说　明:创建各种类以及有可能返回错误的操作
******************************************************************/
bool CenterWidget::construct()
{
    bool ret = true;

    mainLayout = new QHBoxLayout(this);
    mainEditor = new QPlainTextEdit(this);
    mainDrawingBoard = new DrawingBoard(this);
    mainSerialPort = new SerialPort(this);
    mainCalculator = Calculator::NewInstance();
    mainCalculator->setParent(this);

    if(mainLayout && mainEditor && mainCalculator && mainDrawingBoard && mainSerialPort)
    {
        mainLayout->addWidget(mainEditor);
        mainDrawingBoard->hide();
        mainSerialPort->hide();
        currentMode = TextEditOnlyMode;

        connect(mainCalculator->getUi(), SIGNAL(sendProcess(QQueue<QString>)), this, SLOT(CalculatorProcessSlot(QQueue<QString>)));
        connect(mainSerialPort, SIGNAL(openSignal()), this, SLOT(SerialPortOpenSlot()));
        connect(mainSerialPort, SIGNAL(closeSignal()), this, SLOT(SerialPortCloseSlot()));
        connect(mainSerialPort, SIGNAL(clearSignal()), this, SLOT(SerialPortClearSlot())); 
    }
    else
    {
        ret = false;
    }

    return ret;
}

/*****************************************************************
** 函数名: NewInstance()
** 输　入: 无
** 输　出: 无
** 返回值: CenterWidget*
** 功能描述:中央组件类静态二阶构造
** 作　者:
** 日　期:
** 说　明:返回中央组件类
******************************************************************/
CenterWidget* CenterWidget::NewInstance()
{
    CenterWidget* ret = new CenterWidget();

    if( !(ret && ret->construct()) )
    {
        delete ret;
        ret = NULL;
    }

    return ret;
}

/*****************************************************************
** 函数名: getMainEditor()
** 输　入: 无
** 输　出: 无
** 返回值: QPlainTextEdit*
** 功能描述:返回中央组件类
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
QPlainTextEdit* CenterWidget::getMainEditor()
{
    return mainEditor;
}

/*****************************************************************
** 函数名: addCalculator()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:显示计算器
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void CenterWidget::addCalculator()
{
    mainLayout->addWidget(mainCalculator->getUi());
    mainCalculator->show();
    currentMode = CalculatorMode;
}

/*****************************************************************
** 函数名: removeCalculator()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:不显示计算器
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void CenterWidget::removeCalculator()
{
    mainLayout->removeWidget(mainCalculator->getUi());
    mainCalculator->hide();
}

/*****************************************************************
** 函数名: addDrawingBoard()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:显示画图板
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void CenterWidget::addDrawingBoard()
{
    mainLayout->addWidget(mainDrawingBoard);
    mainDrawingBoard->show();
    currentMode = DrawingBoardMode;
}

/*****************************************************************
** 函数名: removeDrawingBoard()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:不显示画图板
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void CenterWidget::removeDrawingBoard()
{
    mainLayout->removeWidget(mainDrawingBoard);
    mainDrawingBoard->hide();
}

/*****************************************************************
** 函数名: addSerialPort()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:显示串口控制器
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void CenterWidget::addSerialPort()
{
    mainLayout->addWidget(mainSerialPort);
    mainSerialPort->show();
    currentMode = SerialPortMode;
    connect(mainEditor, SIGNAL(cursorPositionChanged()), this, SLOT(SerialPortAutoEndSlot()));
}

/*****************************************************************
** 函数名: removeSerialPort()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:不显示串口控制器
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void CenterWidget::removeSerialPort()
{
    mainLayout->removeWidget(mainSerialPort);
    mainSerialPort->hide();
    disconnect(mainEditor, SIGNAL(cursorPositionChanged()), this, SLOT(SerialPortAutoEndSlot()));
}

/*****************************************************************
** 函数名: transMode(Mode mode)
** 输　入: Mode mode:
            TextEditOnlyMode 仅文本组件
            CalculatorMode   文本组件 + 计算器
            DrawingBoardMode 文本组件 + 画图板
            SerialPortMode   文本组件 + 串口通信
** 输　出: 无
** 返回值: 无
** 功能描述:切换多功能显示
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void CenterWidget::transMode(Mode mode)
{
    if(currentMode == TextEditOnlyMode)
    {
        if(mode == CalculatorMode)/*仅文本组件 ==> 文本组件 + 计算器*/
        {
            addCalculator();
        }
        else if(mode == DrawingBoardMode)/*仅文本组件 ==> 文本组件 + 画图板*/
        {
            addDrawingBoard();
        }
        else if(mode == SerialPortMode)/*仅文本组件 ==> 文本组件 + 串口*/
        {
            addSerialPort();
        }
    }
    else if(currentMode == CalculatorMode)
    {
        removeCalculator();

        if(mode == TextEditOnlyMode)/*文本组件 + 计算器 ==> 仅文本组件*/
        {
            currentMode = TextEditOnlyMode;
        }
        else if(mode == DrawingBoardMode)/*文本组件 + 计算器 ==> 文本组件 + 画图板*/
        {
            addDrawingBoard();
        }
        else if(mode == SerialPortMode)/*文本组件 + 计算器 ==> 文本组件 + 串口*/
        {
            addSerialPort();
        }
    }
    else if(currentMode == DrawingBoardMode)
    {
        removeDrawingBoard();

        if(mode == TextEditOnlyMode)/*文本组件 + 画图板 ==> 仅文本组件*/
        {
            currentMode = TextEditOnlyMode;
        }
        else if(mode == CalculatorMode)/*文本组件 + 画图板 ==> 文本组件 + 计算器*/
        {
            addCalculator();
        }
        else if(mode == SerialPortMode)/*文本组件 + 画图板 ==> 文本组件 + 串口*/
        {
            addSerialPort();
        }
    }
    else if(currentMode == SerialPortMode)
    {
        removeSerialPort();

        if(mode == TextEditOnlyMode)/*文本组件 + 串口 ==> 仅文本组件*/
        {
            currentMode = TextEditOnlyMode;
        }
        else if(mode == CalculatorMode)/*文本组件 + 串口 ==> 文本组件 + 计算器*/
        {
            addCalculator();
        }
        else if(mode == DrawingBoardMode)/*文本组件 + 串口 ==> 文本组件 + 画图板*/
        {
            addDrawingBoard();
        }
    }
}

/*****************************************************************
** 函数名: SerialPortOpenSlot()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:串口打开槽函数
** 作　者:
** 日　期:
** 说　明:只有在串口设备指针不为空时才可以连接槽函数
******************************************************************/
void CenterWidget::SerialPortOpenSlot()
{
    connect(mainSerialPort->getSerialPortDev(), SIGNAL(readyRead()), this, SLOT(SerialPortReadSlot()));
}

/*****************************************************************
** 函数名: SerialPortCloseSlot()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:串口关闭槽函数
** 作　者:
** 日　期:
** 说　明:断开槽函数连接
******************************************************************/
void CenterWidget::SerialPortCloseSlot()
{
    disconnect(mainSerialPort->getSerialPortDev(), SIGNAL(readyRead()), this, SLOT(SerialPortReadSlot()));
}

/*****************************************************************
** 函数名: SerialPortClearSlot()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:串口控制文本框清除槽函数
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void CenterWidget::SerialPortClearSlot()
{
    mainEditor->clear();
}

/*****************************************************************
** 函数名: SerialPortReadSlot()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:文本框写入串口数据槽函数
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void CenterWidget::SerialPortReadSlot()
{
    mainEditor->insertPlainText(QString(mainSerialPort->getSerialPortDev()->readAll()));
}

/*****************************************************************
** 函数名: SerialPortAutoEndSlot()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:文本框（串口）自动下拉
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void CenterWidget::SerialPortAutoEndSlot()
{
    QTextCursor cursor = mainEditor->textCursor();

    cursor.movePosition(QTextCursor::End);

    mainEditor->setTextCursor(cursor);
}

/*****************************************************************
** 函数名: CalculatorProcessSlot
** 输　入: QQueue<QString> obj : 计算过程
** 输　出: 无
** 返回值: 无
** 功能描述:文本框显示计算过程
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void CenterWidget::CalculatorProcessSlot(QQueue<QString> obj)
{
    for(int i = 0; i < obj.length(); i++)
    {
        mainEditor->insertPlainText(obj[i]);
    }
}
