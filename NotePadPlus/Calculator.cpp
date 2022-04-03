/***********************************************************************************
 * 文件名 : Calculator.cpp
 * 负责人 :
 * 创建日期 :
 * 文件描述 : 计算器顶层类
 * 版权说明 :
 * 其它说明 :
 * 修改日志 :
***********************************************************************************/
#include "Calculator.h"

/*****************************************************************
** 函数名: Calculator(QObject* parent)
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述: 返回配置文件中保存的是否有效的信息
** 作　者:
** 日　期:
** 说　明:
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
