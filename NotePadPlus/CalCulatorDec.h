/***********************************************************************************
 * 文件名 : CalCulatorDec.h
 * 负责人 :
 * 创建日期 :
 * 文件描述 : 计算器算法类
 * 版权说明 :
 * 其它说明 :
 * 修改日志 :
***********************************************************************************/
#ifndef _CALCULATORDEC_H_
#define _CALCULATORDEC_H_

#include "ICalculator.h"
#include <QQueue>
#include <QChar>
#include <QString>
#include <QStack>
#include <QFile>
#include <QApplication>
#include <QDataStream>
#include <QTextStream>
#include <QTime>
#include <QDateTime>

class CalCulatorDec : public ICalculator
{
public:
    CalCulatorDec();

protected:
    QString m_text;

    void expression(QString text);
    bool result(QString& result, QQueue<QString>& process, bool store);

    /*用于分离算法*/
    bool isNumber(QChar c);
    bool isDot(QChar c);
    bool isSymbol(QChar c);
    bool isLeft(QChar c);
    bool isRight(QChar c);
    bool isSign(QChar c, QChar pre);/*用于分离算法中判断正负号*/

    /*用于检查括号匹配，中缀转后缀，以及计算结果*/
    bool isLeft(QString s);
    bool isRight(QString s);
    bool isNumber(QString s);
    bool isSymbol(QString s);
    int priority(QString s);

    /*用于合成计算步骤*/
    QString addProcess(double left, double right, QString symbol, double result);

    /*第一步：分离算法*/
    bool split(const QString& text, QQueue<QString>& before);

    /*第二步：检查括号是否匹配*/
    bool check(const QQueue<QString>& before);

    /*第三步：中缀转后缀*/
    bool transform(const QQueue<QString>& before, QQueue<QString>& after);

    /*第四步：根据后缀表达式计算结果*/
    bool calculate(const QQueue<QString>& after, QString& result, QQueue<QString>& process);
};

#endif //_CALCULATORDEC_H_
