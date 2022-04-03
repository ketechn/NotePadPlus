/***********************************************************************************
 * �ļ��� : Calculator.cpp
 * ������ :
 * �������� :
 * �ļ����� : ������������
 * ��Ȩ˵�� :
 * ����˵�� :
 * �޸���־ :
***********************************************************************************/
#include "Calculator.h"

/*****************************************************************
** ������: Calculator(QObject* parent)
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ���������ļ��б�����Ƿ���Ч����Ϣ
** ������:
** �ա���:
** ˵����:
******************************************************************/
Calculator::Calculator(QObject* parent) : QObject(parent)
{
}

bool Calculator::construct()
{
    bool ret = true;

    ui = CalculatorUI::NewInstance();

    if(ui != NULL)
    {
        ui->installCal(&cal);
    }
    else
    {
        ret = false;
    }

    return ret;
}

Calculator* Calculator::NewInstance()
{
    Calculator* ret = new Calculator();

    if( !(ret && ret->construct()) )
    {
        delete ret;
        ret = NULL;
    }

    return ret;
}

CalculatorUI* Calculator::getUi()
{
    return ui;
}

void Calculator::show()
{
    ui->show();
}

void Calculator::hide()
{
    ui->hide();
}
