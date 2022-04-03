/***********************************************************************************
 * 文件名 : Calculator.h
 * 负责人 :
 * 创建日期 :
 * 文件描述 : 计算器顶层类
 * 版权说明 :
 * 其它说明 :
 * 修改日志 :
***********************************************************************************/
#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include <QObject>
#include "CalCulatorDec.h"
#include "CalCulatorUI.h"

class Calculator : public QObject
{
    Q_OBJECT

protected:
    explicit Calculator(QObject *parent = 0);
    bool construct();
    CalCulatorDec cal;
    CalculatorUI* ui;

public:
    static Calculator* NewInstance();
    CalculatorUI* getUi();//add
    void show();
    void hide();
};

#endif //_CALCULATOR_H_
