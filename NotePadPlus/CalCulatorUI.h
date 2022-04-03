/***********************************************************************************
 * �ļ��� : CalCulatorUI.h
 * ������ :
 * �������� :
 * �ļ����� : ������������
 * ��Ȩ˵�� :
 * ����˵�� :
 * �޸���־ :
***********************************************************************************/
#ifndef _CALCULATORUI_H_
#define _CALCULATORUI_H_

#include <QtGui/QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include "ICalculator.h"

class CalculatorUI : public QWidget
{
    Q_OBJECT
    
protected:
    QPushButton* m_button[20];
    QLineEdit* m_edit;
    QCheckBox* m_checkProcess;
    QCheckBox* m_checkStore;

    CalculatorUI(QWidget* parent = 0);
    bool construct();
    ~CalculatorUI();
    ICalculator* cal;

protected slots:
    void onButtonPress();

signals:
    void sendProcess(QQueue<QString>);

public:
    static CalculatorUI* NewInstance();
    void show();
    void installCal(ICalculator* cal);
};

#endif //_CALCULATORUI_H_
