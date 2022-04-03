/***********************************************************************************
 * �ļ��� : CalCulatorDec.cpp
 * ������ :
 * �������� :
 * �ļ����� : �������㷨��
 * ��Ȩ˵�� :
 * ����˵�� :
 * �޸���־ :
***********************************************************************************/
#include "CalCulatorDec.h"


/*****************************************************************
** ������: CalCulatorDec()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: bool
** ��������:�������㷨�๹�캯��
** ������:
** �ա���:
** ˵����:
******************************************************************/
CalCulatorDec::CalCulatorDec()
{

}

/*****************************************************************
** ������: expression
** �䡡��: QString text �� ���ʽ
** �䡡��: ��
** ����ֵ: ��
** ��������: ��ȡ���ʽ
** ������:
** �ա���:
** ˵����:
******************************************************************/
void CalCulatorDec::expression(QString text)
{
    m_text = text;
}

/*****************************************************************
** ������: result
** �䡡��: ��
** �䡡��: QString& result �� ������
** ����ֵ: ��
** ��������: ���������
** ������:
** �ա���:
** ˵����: ����ִ�з����㷨->�����ʽ->��׺ת��׺->������
          �κ�һ�����ڳ�������һ������ִ�У���˲���do...while(0)�ṹ
******************************************************************/
bool CalCulatorDec::result(QString& result, QQueue<QString>& process, bool store)
{
    bool ret = true;
    QQueue<QString> before; /*beforeΪ��׺���ʽ*/
    QQueue<QString> after;  /*afterΪ��׺���ʽ*/

    do
    {
        /*�����㷨*/
        if( !split(m_text, before) )
        {
            result = "Error";
            ret = false;
            break;
        }

        /*���*/
        if( !check(before) )
        {
            result = "Error";
            ret = false;
            break;
        }

        /*��׺ת��׺*/
        if( !transform(before, after) )
        {
            result = "Error";
            ret = false;
            break;
        }

        /*������*/
        if( !calculate(after, result, process) )
        {
            result = "Error";
            ret = false;
            break;
        }
    }while(0);

    /*������ִ�еļ�¼��������̨*/
    if(store)
    {
        QFile file(QApplication::applicationDirPath() + "/CalculateLog.log");

        if( file.open(QIODevice::WriteOnly | QIODevice::Append) )
        {
            QTextStream out(&file);

            out << (QString("[") + QDateTime::currentDateTime().date().toString() + QString("]") + QString("[") + QTime::currentTime().toString() + QString("]") + m_text + QString("=") + result + QString("\n"));

            file.close();
        }
        else
        {
            ret = false;
        }
    }

    return ret;
}

/*****************************************************************
** ������: isNumber
** �䡡��: QChar c : �ַ�
** �䡡��: ��
** ����ֵ: bool
** ��������: �ж��Ƿ�������
** ������:
** �ա���:
** ˵����: ���ڷ����㷨
******************************************************************/
bool CalCulatorDec::isNumber(QChar c)
{
    return (('0' <= c) && (c <= '9'));
}

/*****************************************************************
** ������: isDot
** �䡡��: QChar c : �ַ�
** �䡡��: ��
** ����ֵ: bool
** ��������: �ж��Ƿ���С����
** ������:
** �ա���:
** ˵����: ���ڷ����㷨
******************************************************************/
bool CalCulatorDec::isDot(QChar c)
{
    return (c == '.');
}

/*****************************************************************
** ������: isSymbol
** �䡡��: QChar c : �ַ�
** �䡡��: ��
** ����ֵ: bool
** ��������: �ж��Ƿ��������
** ������:
** �ա���:
** ˵����: ���ڷ����㷨
******************************************************************/
bool CalCulatorDec::isSymbol(QChar c)
{
    return ((c == '+') || (c == '-') || (c == '*') || (c == '/'));
}

/*****************************************************************
** ������: isLeft
** �䡡��: QChar c : �ַ�
** �䡡��: ��
** ����ֵ: bool
** ��������: �ж��Ƿ���������
** ������:
** �ա���:
** ˵����: ���ڷ����㷨
******************************************************************/
bool CalCulatorDec::isLeft(QChar c)
{
    return (c == '(');
}

/*****************************************************************
** ������: isRight
** �䡡��: QChar c : �ַ�
** �䡡��: ��
** ����ֵ: bool
** ��������: �ж��Ƿ���������
** ������:
** �ա���:
** ˵����: ���ڷ����㷨
******************************************************************/
bool CalCulatorDec::isRight(QChar c)
{
    return (c == ')');
}

/*****************************************************************
** ������: isSign
** �䡡��: QChar c : �ַ�
          QChar pre : �ַ�c��ǰһ���ַ�
** �䡡��: ��
** ����ֵ: bool
** ��������: �ж��Ƿ���������
** ������:
** �ա���:
** ˵����: ���ڷ����㷨
******************************************************************/
bool CalCulatorDec::isSign(QChar c, QChar pre)
{
    return (c == '+' || c == '-') && (isSymbol(pre) || isLeft(pre));
}

/*****************************************************************
** ������: isLeft
** �䡡��: QString s : �ַ���
** �䡡��: ��
** ����ֵ: bool
** ��������: �ж��Ƿ���������
** ������:
** �ա���:
** ˵����: ���ڼ�顢��׺ת��׺��������
******************************************************************/
bool CalCulatorDec::isLeft(QString s)
{
    return s == "(";
}

/*****************************************************************
** ������: isRight
** �䡡��: QString s : �ַ���
** �䡡��: ��
** ����ֵ: bool
** ��������: �ж��Ƿ���������
** ������:
** �ա���:
** ˵����: ���ڼ�顢��׺ת��׺��������
******************************************************************/
bool CalCulatorDec::isRight(QString s)
{
    return s == ")";
}

/*****************************************************************
** ������: isNumber
** �䡡��: QString s : �ַ���
** �䡡��: ��
** ����ֵ: bool
** ��������: �ж��Ƿ�������
** ������:
** �ա���:
** ˵����: ���ڼ�顢��׺ת��׺��������
******************************************************************/
bool CalCulatorDec::isNumber(QString s)
{
    bool ret = false;

    s.toDouble(&ret);

    return ret;
}

/*****************************************************************
** ������: isSymbol
** �䡡��: QString s : �ַ���
** �䡡��: ��
** ����ֵ: bool
** ��������: �ж��Ƿ��������
** ������:
** �ա���:
** ˵����: ���ڼ�顢��׺ת��׺��������
******************************************************************/
bool CalCulatorDec::isSymbol(QString s)
{
    return (s == "+") || (s == "-") || (s == "*") || (s == "/");
}

/*****************************************************************
** ������: priority
** �䡡��: ��
** �䡡��: QString s : �ַ���
** ����ֵ: int : ���ȼ������ִ�����ȼ���
** ��������: �ж�����������ȼ�
** ������:
** �ա���:
** ˵����: ���ڼ�����
******************************************************************/
int CalCulatorDec::priority(QString s)
{
    int priority = 0;

    if( s == "+" || s == "-")
    {
        priority = 1;
    }
    else if(s == "*" || s == "/")
    {
        priority = 2;
    }

    return priority;
}

/*****************************************************************
** ������: split
** �䡡��: const QString& text : ���ʽ
** �䡡��: QQueue<QString>& before : ��������׺���ʽ
** ����ֵ: bool
** ��������: �����㷨
** ������:
** �ա���:
** ˵����: �����㷨���ѵ��������ּӼ��ź�������
          �����������˵����+���͡�-����ʵ��Ϊ�����ţ�
          һ����+���͡�-�������ڵ�һ��λ�á�
          ������+���͡�-��ǰ�����������
          ������+���͡�-��ǰ���������š�
          ִ�з����㷨֮��ı��ʽ��ֻʣ���ĸ��ɷ֣������š������š����֡������
******************************************************************/
bool CalCulatorDec::split(const QString& text, QQueue<QString>& before)
{
    bool ret = true;

    QString temp;
    temp.clear();

    /*��һ���ַ�ֻ�������֡��Ӽ��š������ţ�����������Ϊ�Ƿ��������㷨ִ��ʧ��*/
    if((text[0] == '+') || (text[0] == '-') || isNumber(text[0]))
    {
        temp += text[0];
    }
    else if(text[0] == '(')
    {
        temp += text[0];
        before.enqueue(temp);
        temp.clear();
    }
    else
    {
        ret = false;
    }

    if(ret)
    {
        for(int i = 1; i < text.length(); i++)
        {
            if( isSign(text[i], text[i-1]) || isNumber(text[i]) || isDot(text[i]) )
            {
                temp += text[i];
            }
            else
            {
                if( !(temp.isEmpty()) )
                {
                    before.enqueue(temp);
                    temp.clear();
                }

                temp += text[i];
                before.enqueue(temp);
                temp.clear();
            }
        }

        /*����forѭ�����������Ӧ�Ž��������Ҫ����*/
        if( !(temp.isEmpty()) )
        {
            before.enqueue(temp);
        }
    }

    return ret;
}

/*****************************************************************
** ������: check
** �䡡��: const QQueue<QString>& before : ִ�з����㷨֮��ı��ʽ
** �䡡��: ��
** ����ֵ: bool
** ��������: �����ʽ
** ������:
** �ա���:
** ˵����: ��������Ƿ�ƥ��
          ����Ƿ��зǷ�Ԫ�أ��������֣����������������֮��Ķ��ǷǷ����ʽ
          ����ջ���������ƥ�����
          �������У���������ջ��������ջ����ջ
          ע�⣺��ջ������ջ��Ԫ�ز���ʱҪ���ж�ջ�Ƿ�Ϊ��
******************************************************************/
bool CalCulatorDec::check(const QQueue<QString>& before)
{
    bool ret = true;
    QStack<QString> stack;

    stack.clear();

    /*��һ�����������ƥ��*/
    for(int i = 0; i < before.length(); i++)
    {
        if( isLeft(before[i]) )
        {
            stack.push(before[i]);
        }
        else if( isRight(before[i]) )
        {
            if( !stack.isEmpty() )
            {
                stack.pop();
            }
            else
            {
                ret = false;
                break;
            }
        }
    }

    /*�ڶ��������Ƿ�Ԫ��*/
    if( ret && stack.isEmpty() )
    {
        for(int i = 0; i < before.length(); i++)
        {
            if( !(isLeft(before[i]) || isRight(before[i]) || isNumber(before[i]) || isSymbol(before[i])) )
            {
                ret = false;
                break;
            }
        }
    }
    else
    {
        ret = false;
    }

    return ret;
}

/***********************************************************************************************
** ������: transform
** �䡡��: const QQueue<QString>& before : ִ�з����㷨֮��ı��ʽ����׺��
** �䡡��: QQueue<QString>& after : ��׺���ʽ
** ����ֵ: bool
** ��������: ��׺ת��׺
** ������:
** �ա���:
** ˵����: ����������еĸ���Ԫ��
          1.�����ţ���ջ
          2.�����ţ�ջ��Ԫ�������ջ���뵽�¶���ĩβ��ֱ�����������ź���������ͬʱ����ʧ��
          3.���֣�ֱ�ӽ����¶���ĩβ
          4.�������
          ��1�������ж�ջ�Ƿ�Ϊ�գ����Ϊ�գ�ֱ�ӽ������������ջ��Ȼ������¸�Ԫ��
          ��2�����ջ��Ϊ�գ���ջ������������ȼ�С�ڸ�Ԫ�ص����ȼ������Ԫ����ջ��Ȼ������¸�Ԫ��
          ��3�����ջ��Ϊ�գ���ջ������������ȼ����ڻ���ڸ�Ԫ�ص����ȼ�����ջ��Ԫ�س�ջ�ӵ��¶���ĩβ���������裨1��
          ע�⣺��ջ������ջ��Ԫ�ز���ʱҪ���ж�ջ�Ƿ�Ϊ��
************************************************************************************************/
bool CalCulatorDec::transform(const QQueue<QString>& before, QQueue<QString>& after)
{
    bool ret = true;
    QStack<QString> stack;

    after.clear();

    for(int i = 0; i < before.count(); i++)
    {
        if( isLeft(before[i]) )
        {
            stack.push(before[i]);
        }
        else if( isRight(before[i]) )
        {
            while( !isLeft(stack.top()) )
            {
                after.enqueue(stack.pop());
            }

            stack.pop();
        }
        else if( isNumber(before[i]) )
        {
            after.enqueue(before[i]);
        }
        else if( isSymbol(before[i]) )
        {
            do
            {
                if( stack.isEmpty() )
                {
                    stack.push(before[i]);
                    break;
                }
                else if( priority(stack.top()) < priority(before[i]) )
                {
                    stack.push(before[i]);
                    break;
                }
                else if( priority(stack.top()) >= priority(before[i]) )
                {
                    after.enqueue(stack.pop());
                }
            }while(1);
        }
        else
        {
            ret = false;
            break;
        }
    }

    while( !stack.isEmpty() )
    {
        after.enqueue(stack.pop());
    }

    return ret;
}

/***********************************************************************************************
** ������: addProcess
** �䡡��: double left : ��������
          double right : ��������
          QString symbol : �����
** �䡡��: ��
** ����ֵ: QString �� ������ʽ
** ��������:
** ������:
** �ա���:
** ˵����: 1.���֣���ջ
          2.���ţ���ջ��Ԫ�ص�����Ϊ�Ҳ��������ٽ��µ�ջ��Ԫ�ص�����Ϊ����������м��㣬��������ѹջ
          ע�⣺��ջ������ջ��Ԫ�ز���ʱҪ���ж�ջ�Ƿ�Ϊ��
************************************************************************************************/
QString CalCulatorDec::addProcess(double left, double right, QString symbol, double result)
{
    QString qleft = QString().setNum(left);
    QString qright = QString().setNum(right);
    QString qresult = QString().setNum(result);

    return qleft + symbol + qright + QString("=") + qresult + QString("\n");
}

/***********************************************************************************************
** ������: calculate
** �䡡��: const QQueue<QString>& after : ��׺���ʽ
** �䡡��: QString& result �� ������
** ����ֵ: bool
** ��������: ������
** ������:
** �ա���:
** ˵����: 1.���֣���ջ
          2.���ţ���ջ��Ԫ�ص�����Ϊ�Ҳ��������ٽ��µ�ջ��Ԫ�ص�����Ϊ����������м��㣬��������ѹջ
          ע�⣺��ջ������ջ��Ԫ�ز���ʱҪ���ж�ջ�Ƿ�Ϊ��
************************************************************************************************/
bool CalCulatorDec::calculate(const QQueue<QString>& after, QString& result, QQueue<QString>& process)
{
    bool ret = true;
    QStack<double> stack;
    double topush = 0.0;
    double right = 0.0;
    double left = 0.0;

    stack.clear();

    for(int i = 0; i < after.length(); i++)
    {
        if( isNumber(after[i]) )
        {
            topush = after[i].toDouble(&ret);

            if(ret)
            {
                stack.push(topush);
            }
            else
            {
                ret = false;
                break;
            }
        }
        else if( isSymbol(after[i]) )
        {
            if( !stack.isEmpty() )
            {
                right = stack.pop();
            }
            else
            {
                ret = false;
                break;
            }

            if( !stack.isEmpty() )
            {
                left = stack.pop();
            }
            else
            {
                ret = false;
                break;
            }

            if( after[i] == "+" )
            {
                topush = left + right;

                stack.push(topush);

                process.enqueue(addProcess(left, right, after[i], topush));
            }
            else if( after[i] == "-" )
            {
                topush = left - right;

                stack.push(topush);

                process.enqueue(addProcess(left, right, after[i], topush));
            }
            else if( after[i] == "*" )
            {
                topush = left * right;

                stack.push(topush);

                process.enqueue(addProcess(left, right, after[i], topush));
            }
            else if( after[i] == "/" )
            {
                if( !((-0.000000001 < right) && (right < 0.000000001)) )
                {
                    topush = left / right;

                    stack.push(topush);

                    process.enqueue(addProcess(left, right, after[i], topush));
                }
                else
                {
                    ret = false;
                    break;
                }
            }
            else
            {
                ret = false;
                break;
            }
        }
        else
        {
            ret = false;
            break;
        }
    }

    if( ret && !stack.isEmpty() )
    {
        result = QString().sprintf("%lf",stack.pop());
    }
    else
    {
        ret = false;
        result = "";
    }

    if( !stack.isEmpty() )
    {
        ret = false;
        result = "";
    }

    return ret;
}
