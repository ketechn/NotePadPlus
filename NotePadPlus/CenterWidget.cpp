/***********************************************************************************
 * �ļ��� : CenterWidget.cpp
 * ������ :
 * �������� :
 * �ļ����� : MainWindow�����齨��
 * ��Ȩ˵�� :
 * ����˵�� :
 * �޸���־ :
***********************************************************************************/
#include "CenterWidget.h"

/*****************************************************************
** ������: CenterWidget
** �䡡��: QWidget* parent
** �䡡��: ��
** ����ֵ: ��
** ��������:��������๹�캯��
** ������:
** �ա���:
** ˵����: ��ʼĬ��Ϊֻ���ı����ģʽ
******************************************************************/
CenterWidget::CenterWidget(QWidget* parent) : QWidget(parent)
{
    currentMode = TextEditOnlyMode;
}

/*****************************************************************
** ������: construct()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: bool
** ��������:�����������׹���
** ������:
** �ա���:
** ˵����:�����������Լ��п��ܷ��ش���Ĳ���
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
** ������: NewInstance()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: CenterWidget*
** ��������:��������ྲ̬���׹���
** ������:
** �ա���:
** ˵����:�������������
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
** ������: getMainEditor()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: QPlainTextEdit*
** ��������:�������������
** ������:
** �ա���:
** ˵����:
******************************************************************/
QPlainTextEdit* CenterWidget::getMainEditor()
{
    return mainEditor;
}

/*****************************************************************
** ������: addCalculator()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:��ʾ������
** ������:
** �ա���:
** ˵����:
******************************************************************/
void CenterWidget::addCalculator()
{
    mainLayout->addWidget(mainCalculator->getUi());
    mainCalculator->show();
    currentMode = CalculatorMode;
}

/*****************************************************************
** ������: removeCalculator()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:����ʾ������
** ������:
** �ա���:
** ˵����:
******************************************************************/
void CenterWidget::removeCalculator()
{
    mainLayout->removeWidget(mainCalculator->getUi());
    mainCalculator->hide();
}

/*****************************************************************
** ������: addDrawingBoard()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:��ʾ��ͼ��
** ������:
** �ա���:
** ˵����:
******************************************************************/
void CenterWidget::addDrawingBoard()
{
    mainLayout->addWidget(mainDrawingBoard);
    mainDrawingBoard->show();
    currentMode = DrawingBoardMode;
}

/*****************************************************************
** ������: removeDrawingBoard()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:����ʾ��ͼ��
** ������:
** �ա���:
** ˵����:
******************************************************************/
void CenterWidget::removeDrawingBoard()
{
    mainLayout->removeWidget(mainDrawingBoard);
    mainDrawingBoard->hide();
}

/*****************************************************************
** ������: addSerialPort()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:��ʾ���ڿ�����
** ������:
** �ա���:
** ˵����:
******************************************************************/
void CenterWidget::addSerialPort()
{
    mainLayout->addWidget(mainSerialPort);
    mainSerialPort->show();
    currentMode = SerialPortMode;
    connect(mainEditor, SIGNAL(cursorPositionChanged()), this, SLOT(SerialPortAutoEndSlot()));
}

/*****************************************************************
** ������: removeSerialPort()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:����ʾ���ڿ�����
** ������:
** �ա���:
** ˵����:
******************************************************************/
void CenterWidget::removeSerialPort()
{
    mainLayout->removeWidget(mainSerialPort);
    mainSerialPort->hide();
    disconnect(mainEditor, SIGNAL(cursorPositionChanged()), this, SLOT(SerialPortAutoEndSlot()));
}

/*****************************************************************
** ������: transMode(Mode mode)
** �䡡��: Mode mode:
            TextEditOnlyMode ���ı����
            CalculatorMode   �ı���� + ������
            DrawingBoardMode �ı���� + ��ͼ��
            SerialPortMode   �ı���� + ����ͨ��
** �䡡��: ��
** ����ֵ: ��
** ��������:�л��๦����ʾ
** ������:
** �ա���:
** ˵����:
******************************************************************/
void CenterWidget::transMode(Mode mode)
{
    if(currentMode == TextEditOnlyMode)
    {
        if(mode == CalculatorMode)/*���ı���� ==> �ı���� + ������*/
        {
            addCalculator();
        }
        else if(mode == DrawingBoardMode)/*���ı���� ==> �ı���� + ��ͼ��*/
        {
            addDrawingBoard();
        }
        else if(mode == SerialPortMode)/*���ı���� ==> �ı���� + ����*/
        {
            addSerialPort();
        }
    }
    else if(currentMode == CalculatorMode)
    {
        removeCalculator();

        if(mode == TextEditOnlyMode)/*�ı���� + ������ ==> ���ı����*/
        {
            currentMode = TextEditOnlyMode;
        }
        else if(mode == DrawingBoardMode)/*�ı���� + ������ ==> �ı���� + ��ͼ��*/
        {
            addDrawingBoard();
        }
        else if(mode == SerialPortMode)/*�ı���� + ������ ==> �ı���� + ����*/
        {
            addSerialPort();
        }
    }
    else if(currentMode == DrawingBoardMode)
    {
        removeDrawingBoard();

        if(mode == TextEditOnlyMode)/*�ı���� + ��ͼ�� ==> ���ı����*/
        {
            currentMode = TextEditOnlyMode;
        }
        else if(mode == CalculatorMode)/*�ı���� + ��ͼ�� ==> �ı���� + ������*/
        {
            addCalculator();
        }
        else if(mode == SerialPortMode)/*�ı���� + ��ͼ�� ==> �ı���� + ����*/
        {
            addSerialPort();
        }
    }
    else if(currentMode == SerialPortMode)
    {
        removeSerialPort();

        if(mode == TextEditOnlyMode)/*�ı���� + ���� ==> ���ı����*/
        {
            currentMode = TextEditOnlyMode;
        }
        else if(mode == CalculatorMode)/*�ı���� + ���� ==> �ı���� + ������*/
        {
            addCalculator();
        }
        else if(mode == DrawingBoardMode)/*�ı���� + ���� ==> �ı���� + ��ͼ��*/
        {
            addDrawingBoard();
        }
    }
}

/*****************************************************************
** ������: SerialPortOpenSlot()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:���ڴ򿪲ۺ���
** ������:
** �ա���:
** ˵����:ֻ���ڴ����豸ָ�벻Ϊ��ʱ�ſ������Ӳۺ���
******************************************************************/
void CenterWidget::SerialPortOpenSlot()
{
    connect(mainSerialPort->getSerialPortDev(), SIGNAL(readyRead()), this, SLOT(SerialPortReadSlot()));
}

/*****************************************************************
** ������: SerialPortCloseSlot()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:���ڹرղۺ���
** ������:
** �ա���:
** ˵����:�Ͽ��ۺ�������
******************************************************************/
void CenterWidget::SerialPortCloseSlot()
{
    disconnect(mainSerialPort->getSerialPortDev(), SIGNAL(readyRead()), this, SLOT(SerialPortReadSlot()));
}

/*****************************************************************
** ������: SerialPortClearSlot()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:���ڿ����ı�������ۺ���
** ������:
** �ա���:
** ˵����:
******************************************************************/
void CenterWidget::SerialPortClearSlot()
{
    mainEditor->clear();
}

/*****************************************************************
** ������: SerialPortReadSlot()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:�ı���д�봮�����ݲۺ���
** ������:
** �ա���:
** ˵����:
******************************************************************/
void CenterWidget::SerialPortReadSlot()
{
    mainEditor->insertPlainText(QString(mainSerialPort->getSerialPortDev()->readAll()));
}

/*****************************************************************
** ������: SerialPortAutoEndSlot()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:�ı��򣨴��ڣ��Զ�����
** ������:
** �ա���:
** ˵����:
******************************************************************/
void CenterWidget::SerialPortAutoEndSlot()
{
    QTextCursor cursor = mainEditor->textCursor();

    cursor.movePosition(QTextCursor::End);

    mainEditor->setTextCursor(cursor);
}

/*****************************************************************
** ������: CalculatorProcessSlot
** �䡡��: QQueue<QString> obj : �������
** �䡡��: ��
** ����ֵ: ��
** ��������:�ı�����ʾ�������
** ������:
** �ա���:
** ˵����:
******************************************************************/
void CenterWidget::CalculatorProcessSlot(QQueue<QString> obj)
{
    for(int i = 0; i < obj.length(); i++)
    {
        mainEditor->insertPlainText(obj[i]);
    }
}
