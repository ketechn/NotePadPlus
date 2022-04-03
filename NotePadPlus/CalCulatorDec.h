/***********************************************************************************
 * �ļ��� : CalCulatorDec.h
 * ������ :
 * �������� :
 * �ļ����� : �������㷨��
 * ��Ȩ˵�� :
 * ����˵�� :
 * �޸���־ :
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

    /*���ڷ����㷨*/
    bool isNumber(QChar c);
    bool isDot(QChar c);
    bool isSymbol(QChar c);
    bool isLeft(QChar c);
    bool isRight(QChar c);
    bool isSign(QChar c, QChar pre);/*���ڷ����㷨���ж�������*/

    /*���ڼ������ƥ�䣬��׺ת��׺���Լ�������*/
    bool isLeft(QString s);
    bool isRight(QString s);
    bool isNumber(QString s);
    bool isSymbol(QString s);
    int priority(QString s);

    /*���ںϳɼ��㲽��*/
    QString addProcess(double left, double right, QString symbol, double result);

    /*��һ���������㷨*/
    bool split(const QString& text, QQueue<QString>& before);

    /*�ڶ�������������Ƿ�ƥ��*/
    bool check(const QQueue<QString>& before);

    /*����������׺ת��׺*/
    bool transform(const QQueue<QString>& before, QQueue<QString>& after);

    /*���Ĳ������ݺ�׺���ʽ������*/
    bool calculate(const QQueue<QString>& after, QString& result, QQueue<QString>& process);
};

#endif //_CALCULATORDEC_H_
