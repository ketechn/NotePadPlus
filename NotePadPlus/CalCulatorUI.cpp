/***********************************************************************************
 * 文件名 : CalCulatorUI.cpp
 * 负责人 :
 * 创建日期 :
 * 文件描述 : 计算器界面类
 * 版权说明 :
 * 其它说明 :
 * 修改日志 :
***********************************************************************************/
#include "CalCulatorUI.h"
#include <QDebug>

CalculatorUI::CalculatorUI(QWidget* parent) : QWidget(parent, Qt::WindowCloseButtonHint)
{

}

bool CalculatorUI::construct()
{
    bool ret = true;

    const char* m_text[20] =
    {
        "7", "8", "9", "+", "(",
        "4", "5", "6", "-", ")",
        "1", "2", "3", "*", "<-",
        "0", ".", "=", "/", "C"
    };

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            m_button[i * 5 + j] = new QPushButton(this);

            if( m_button[i * 5 + j] != NULL)
            {
                m_button[i * 5 + j]->setText(m_text[i * 5 + j]);
                m_button[i * 5 + j]->move(10 + 40 * j, 50 + 40 * i);
                m_button[i * 5 + j]->resize(30, 30);
                connect(m_button[i * 5 + j], SIGNAL(clicked()), this, SLOT(onButtonPress()));
            }
            else
            {
                ret = false;
                break;
            }
        }
    }

    if(ret)
    {
        m_edit = new QLineEdit(this);
        if(m_edit != NULL)
        {
            m_edit->move(10, 10);
            m_edit->resize(190, 30);
            m_edit->setReadOnly(true);
            m_edit->setAlignment(Qt::AlignRight);
        }

        m_checkProcess = new QCheckBox(this);
        if(m_checkProcess != NULL)
        {
            m_checkProcess->move(10, 205);
            m_checkProcess->resize(200, 20);
            m_checkProcess->setText("显示计算过程");
        }

        m_checkStore = new QCheckBox(this);
        if(m_checkStore != NULL)
        {
            m_checkStore->move(10, 230);
            m_checkStore->resize(200, 20);
            m_checkStore->setText("后台保存计算");
        }

        else
        {
            ret = false;
        }
    }

    return ret;
}

CalculatorUI* CalculatorUI::NewInstance()
{
    CalculatorUI* ret = new CalculatorUI();

    if( !(ret && ret->construct()) )
    {
        delete ret;
        ret = NULL;
    }

    return ret;
}

void CalculatorUI::onButtonPress()
{
    QPushButton* send = dynamic_cast<QPushButton*>(sender());

    if(send != NULL)
    {
        if(send->text() == "C")
        {
            m_edit->setText("");
        }
        else if(send->text() == "<-")
        {
            QString temp = m_edit->text();

            m_edit->setText(temp.mid(0,temp.length()-1));
        }
        else if(send->text() == "=")
        {
            QString result;
            QQueue<QString> process;
            QString expression = m_edit->text();

            cal->expression(expression);
            cal->result(result, process, m_checkStore->isChecked());

            if(result != "Error" && m_checkProcess->isChecked())
            {
                process.insert(0, expression + QString("=") + result + QString("\n"));
                emit sendProcess(process);
            }

            m_edit->setText(result);
        }
        else
        {
            QString temp = m_edit->text();

            temp += send->text();

            m_edit->setText(temp);
        }
    }
}

void CalculatorUI::installCal(ICalculator* cal)
{
    this->cal = cal;
}

void CalculatorUI::show()
{
    QWidget::show();

    setFixedSize(210, 280);
}

/*
  如果析构函数没有实现，则编译会出现
  collect2:ld returned 1 exit status
  的错误
*/
CalculatorUI::~CalculatorUI()
{

}
