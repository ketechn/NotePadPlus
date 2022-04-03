/***********************************************************************************
 * �ļ��� : ICalculator.h
 * ������ :
 * �������� :
 * �ļ����� : ���麯���࣬��CalCulatorDec�̳У�����UI��Dec֮������ݴ���
 * ��Ȩ˵�� :
 * ����˵�� :
 * �޸���־ :
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
