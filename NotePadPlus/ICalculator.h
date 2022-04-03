/***********************************************************************************
 * 文件名 : ICalculator.h
 * 负责人 :
 * 创建日期 :
 * 文件描述 : 纯虚函数类，被CalCulatorDec继承，用于UI和Dec之间的数据传递
 * 版权说明 :
 * 其它说明 :
 * 修改日志 :
***********************************************************************************/
#ifndef _ICALCULATOR_H_
#define _ICALCULATOR_H_

#include <QString>
#include <QQueue>

class ICalculator
{
public:
    virtual void expression(QString text) = 0;
    virtual bool result(QString& result, QQueue<QString>& process, bool store) = 0;
};

#endif //_ICALCULATOR_H_
