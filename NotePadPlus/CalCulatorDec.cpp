/***********************************************************************************
 * 文件名 : CalCulatorDec.cpp
 * 负责人 :
 * 创建日期 :
 * 文件描述 : 计算器算法类
 * 版权说明 :
 * 其它说明 :
 * 修改日志 :
***********************************************************************************/
#include "CalCulatorDec.h"


/*****************************************************************
** 函数名: CalCulatorDec()
** 输　入: 无
** 输　出: 无
** 返回值: bool
** 功能描述:计算器算法类构造函数
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
CalCulatorDec::CalCulatorDec()
{

}

/*****************************************************************
** 函数名: expression
** 输　入: QString text ： 表达式
** 输　出: 无
** 返回值: 无
** 功能描述: 获取表达式
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void CalCulatorDec::expression(QString text)
{
    m_text = text;
}

/*****************************************************************
** 函数名: result
** 输　入: 无
** 输　出: QString& result ： 计算结果
** 返回值: 无
** 功能描述: 输出计算结果
** 作　者:
** 日　期:
** 说　明: 依次执行分离算法->检查表达式->中缀转后缀->计算结果
          任何一个环节出错则下一步不再执行，因此采用do...while(0)结构
******************************************************************/
bool CalCulatorDec::result(QString& result, QQueue<QString>& process, bool store)
{
    bool ret = true;
    QQueue<QString> before; /*before为中缀表达式*/
    QQueue<QString> after;  /*after为后缀表达式*/

    do
    {
        /*分离算法*/
        if( !split(m_text, before) )
        {
            result = "Error";
            ret = false;
            break;
        }

        /*检查*/
        if( !check(before) )
        {
            result = "Error";
            ret = false;
            break;
        }

        /*中缀转后缀*/
        if( !transform(before, after) )
        {
            result = "Error";
            ret = false;
            break;
        }

        /*计算结果*/
        if( !calculate(after, result, process) )
        {
            result = "Error";
            ret = false;
            break;
        }
    }while(0);

    /*将计算执行的记录保存至后台*/
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
** 函数名: isNumber
** 输　入: QChar c : 字符
** 输　出: 无
** 返回值: bool
** 功能描述: 判断是否是数字
** 作　者:
** 日　期:
** 说　明: 用于分离算法
******************************************************************/
bool CalCulatorDec::isNumber(QChar c)
{
    return (('0' <= c) && (c <= '9'));
}

/*****************************************************************
** 函数名: isDot
** 输　入: QChar c : 字符
** 输　出: 无
** 返回值: bool
** 功能描述: 判断是否是小数点
** 作　者:
** 日　期:
** 说　明: 用于分离算法
******************************************************************/
bool CalCulatorDec::isDot(QChar c)
{
    return (c == '.');
}

/*****************************************************************
** 函数名: isSymbol
** 输　入: QChar c : 字符
** 输　出: 无
** 返回值: bool
** 功能描述: 判断是否是运算符
** 作　者:
** 日　期:
** 说　明: 用于分离算法
******************************************************************/
bool CalCulatorDec::isSymbol(QChar c)
{
    return ((c == '+') || (c == '-') || (c == '*') || (c == '/'));
}

/*****************************************************************
** 函数名: isLeft
** 输　入: QChar c : 字符
** 输　出: 无
** 返回值: bool
** 功能描述: 判断是否是左括号
** 作　者:
** 日　期:
** 说　明: 用于分离算法
******************************************************************/
bool CalCulatorDec::isLeft(QChar c)
{
    return (c == '(');
}

/*****************************************************************
** 函数名: isRight
** 输　入: QChar c : 字符
** 输　出: 无
** 返回值: bool
** 功能描述: 判断是否是右括号
** 作　者:
** 日　期:
** 说　明: 用于分离算法
******************************************************************/
bool CalCulatorDec::isRight(QChar c)
{
    return (c == ')');
}

/*****************************************************************
** 函数名: isSign
** 输　入: QChar c : 字符
          QChar pre : 字符c的前一个字符
** 输　出: 无
** 返回值: bool
** 功能描述: 判断是否是正负号
** 作　者:
** 日　期:
** 说　明: 用于分离算法
******************************************************************/
bool CalCulatorDec::isSign(QChar c, QChar pre)
{
    return (c == '+' || c == '-') && (isSymbol(pre) || isLeft(pre));
}

/*****************************************************************
** 函数名: isLeft
** 输　入: QString s : 字符串
** 输　出: 无
** 返回值: bool
** 功能描述: 判断是否是左括号
** 作　者:
** 日　期:
** 说　明: 用于检查、中缀转后缀、计算结果
******************************************************************/
bool CalCulatorDec::isLeft(QString s)
{
    return s == "(";
}

/*****************************************************************
** 函数名: isRight
** 输　入: QString s : 字符串
** 输　出: 无
** 返回值: bool
** 功能描述: 判断是否是右括号
** 作　者:
** 日　期:
** 说　明: 用于检查、中缀转后缀、计算结果
******************************************************************/
bool CalCulatorDec::isRight(QString s)
{
    return s == ")";
}

/*****************************************************************
** 函数名: isNumber
** 输　入: QString s : 字符串
** 输　出: 无
** 返回值: bool
** 功能描述: 判断是否是数字
** 作　者:
** 日　期:
** 说　明: 用于检查、中缀转后缀、计算结果
******************************************************************/
bool CalCulatorDec::isNumber(QString s)
{
    bool ret = false;

    s.toDouble(&ret);

    return ret;
}

/*****************************************************************
** 函数名: isSymbol
** 输　入: QString s : 字符串
** 输　出: 无
** 返回值: bool
** 功能描述: 判断是否是运算符
** 作　者:
** 日　期:
** 说　明: 用于检查、中缀转后缀、计算结果
******************************************************************/
bool CalCulatorDec::isSymbol(QString s)
{
    return (s == "+") || (s == "-") || (s == "*") || (s == "/");
}

/*****************************************************************
** 函数名: priority
** 输　入: 无
** 输　出: QString s : 字符串
** 返回值: int : 优先级（数字大的优先级大）
** 功能描述: 判断运算符的优先级
** 作　者:
** 日　期:
** 说　明: 用于计算结果
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
** 函数名: split
** 输　入: const QString& text : 表达式
** 输　出: QQueue<QString>& before : 分离后的中缀表达式
** 返回值: bool
** 功能描述: 分离算法
** 作　者:
** 日　期:
** 说　明: 分离算法的难点在于区分加减号和正负号
          以下三种情况说明“+”和“-”号实则为正负号：
          一、“+”和“-”出现在第一个位置。
          二、“+”和“-”前面是运算符。
          三、“+”和“-”前面是左括号。
          执行分离算法之后的表达式就只剩下四个成分：左括号、右括号、数字、运算符
******************************************************************/
bool CalCulatorDec::split(const QString& text, QQueue<QString>& before)
{
    bool ret = true;

    QString temp;
    temp.clear();

    /*第一个字符只能是数字、加减号、左括号，出现其它则为非法，分离算法执行失败*/
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

        /*结束for循环的最后内容应放进队列里，不要忘记*/
        if( !(temp.isEmpty()) )
        {
            before.enqueue(temp);
        }
    }

    return ret;
}

/*****************************************************************
** 函数名: check
** 输　入: const QQueue<QString>& before : 执行分离算法之后的表达式
** 输　出: 无
** 返回值: bool
** 功能描述: 检查表达式
** 作　者:
** 日　期:
** 说　明: 检查括号是否匹配
          检查是否有非法元素，除了数字，运算符，左右括号之外的都是非法表达式
          利用栈来检查括号匹配情况
          遍历队列，左括号入栈，右括号栈顶出栈
          注意：对栈做弹出栈顶元素操作时要先判断栈是否为空
******************************************************************/
bool CalCulatorDec::check(const QQueue<QString>& before)
{
    bool ret = true;
    QStack<QString> stack;

    stack.clear();

    /*第一步：检查括号匹配*/
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

    /*第二步：检查非法元素*/
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
** 函数名: transform
** 输　入: const QQueue<QString>& before : 执行分离算法之后的表达式（中缀）
** 输　出: QQueue<QString>& after : 后缀表达式
** 返回值: bool
** 功能描述: 中缀转后缀
** 作　者:
** 日　期:
** 说　明: 逐个遍历队列的各个元素
          1.左括号：入栈
          2.右括号：栈中元素逐个出栈加入到新队列末尾，直到遇到左括号后左右括号同时“消失”
          3.数字：直接进入新队列末尾
          4.运算符：
          （1）首先判断栈是否为空，如果为空，直接将该运算符加入栈，然后遍历下个元素
          （2）如果栈不为空，且栈顶运算符的优先级小于该元素的优先级，则该元素入栈，然后遍历下个元素
          （3）如果栈不为空，且栈顶运算符的优先级大于或等于该元素的优先级，则栈顶元素出栈加到新队列末尾，继续步骤（1）
          注意：对栈做弹出栈顶元素操作时要先判断栈是否为空
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
** 函数名: addProcess
** 输　入: double left : 左运算数
          double right : 右运算数
          QString symbol : 运算符
** 输　出: 无
** 返回值: QString ： 计算表达式
** 功能描述:
** 作　者:
** 日　期:
** 说　明: 1.数字：入栈
          2.符号：将栈顶元素弹出作为右操作数，再将新的栈顶元素弹出作为左操作数进行计算，将计算结果压栈
          注意：对栈做弹出栈顶元素操作时要先判断栈是否为空
************************************************************************************************/
QString CalCulatorDec::addProcess(double left, double right, QString symbol, double result)
{
    QString qleft = QString().setNum(left);
    QString qright = QString().setNum(right);
    QString qresult = QString().setNum(result);

    return qleft + symbol + qright + QString("=") + qresult + QString("\n");
}

/***********************************************************************************************
** 函数名: calculate
** 输　入: const QQueue<QString>& after : 后缀表达式
** 输　出: QString& result ： 计算结果
** 返回值: bool
** 功能描述: 计算结果
** 作　者:
** 日　期:
** 说　明: 1.数字：入栈
          2.符号：将栈顶元素弹出作为右操作数，再将新的栈顶元素弹出作为左操作数进行计算，将计算结果压栈
          注意：对栈做弹出栈顶元素操作时要先判断栈是否为空
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
