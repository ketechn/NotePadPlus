/***********************************************************************************
 * 文件名 : AppConfig.cpp
 * 负责人 :
 * 创建日期 :
 * 文件描述 : 文本编辑器配置文件
 * 版权说明 :
 * 其它说明 : 关闭多功能文本编辑器之前保存配置结果
 * 修改日志 :
***********************************************************************************/
#include "AppConfig.h"
#include <QFile>
#include <QDataStream>
#include <QApplication>

/*****************************************************************
** 函数名: AppConfig(QObject* parent)
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述: 配置文件类构造函数
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
AppConfig::AppConfig(QObject* parent) : QObject(parent)
{
    m_isValid = restore();
}

/*****************************************************************
** 函数名: AppConfig(QObject* parent)
** 输　入: QFont font ：字体
          QPoint point : 坐标
          QSize size : 窗口大小
          bool isWrap : 是否自动换行
          bool tbVisible : 工具栏是否可见
          bool sbVisible : 状态栏是否可见
          QObject* parent : 父类
** 输　出: 无
** 返回值: 无
** 功能描述: 配置文件类构造函数（重载）
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
AppConfig::AppConfig(QFont font, QPoint point, QSize size, bool isWrap, bool tbVisible, bool sbVisible, QObject* parent)
{
    m_editorFont = font;
    m_mainWindowSize = size;
    m_mainWindowPoint = point;
    m_isAutoWrap = isWrap;
    m_isToolBarVisible = tbVisible;
    m_isStatusBarVisible = sbVisible;
    m_isValid = true;
}

/*****************************************************************
** 函数名: restore()
** 输　入: 无
** 输　出: 无
** 返回值: bool
** 功能描述: 打开配置文件，根据配置文件的内容恢复配置
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
bool AppConfig::restore()
{
    bool ret = true;

    QFile file(QApplication::applicationDirPath() + "/app.config");

    if( file.open(QIODevice::ReadOnly) )
    {
        QDataStream in(&file);

        in.setVersion(QDataStream::Qt_4_7);

        in >> m_editorFont;
        in >> m_mainWindowPoint;
        in >> m_mainWindowSize;
        in >> m_isAutoWrap;
        in >> m_isToolBarVisible;
        in >> m_isStatusBarVisible;

        file.close();
    }
    else
    {
        ret = false;
    }

    return ret;
}

/*****************************************************************
** 函数名: store()
** 输　入: 无
** 输　出: 无
** 返回值: bool
** 功能描述: 创建配置文件，将当前配置存入配置文件中
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
bool AppConfig::store()
{
    bool ret = true;

    QFile file(QApplication::applicationDirPath() + "/app.config");

    if( file.open(QIODevice::WriteOnly) )
    {
        QDataStream out(&file);

        out.setVersion(QDataStream::Qt_4_7);

        out << m_editorFont;
        out << m_mainWindowPoint;
        out << m_mainWindowSize;
        out << m_isAutoWrap;
        out << m_isToolBarVisible;
        out << m_isStatusBarVisible;

        file.close();
    }
    else
    {
        ret = false;
    }

    return ret;
}

/*****************************************************************
** 函数名: editorFont()
** 输　入: 无
** 输　出: 无
** 返回值: QFont
** 功能描述: 返回配置文件中保存的字体信息
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
QFont AppConfig::editorFont()
{
    return m_editorFont;
}

/*****************************************************************
** 函数名: mainWindowSize()
** 输　入: 无
** 输　出: 无
** 返回值: QSize
** 功能描述: 返回配置文件中保存的窗口大小
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
QSize AppConfig::mainWindowSize()
{
    return m_mainWindowSize;
}

/*****************************************************************
** 函数名: mainWindowPoint()
** 输　入: 无
** 输　出: 无
** 返回值: QPoint
** 功能描述: 返回配置文件中保存的窗口坐标
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
QPoint AppConfig::mainWindowPoint()
{
    return m_mainWindowPoint;
}

/*****************************************************************
** 函数名: isAutoWrap()
** 输　入: 无
** 输　出: 无
** 返回值: bool
** 功能描述: 返回配置文件中保存的是否自动换行信息
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
bool AppConfig::isAutoWrap()
{
    return m_isAutoWrap;
}

/*****************************************************************
** 函数名: isToolBarVisible()
** 输　入: 无
** 输　出: 无
** 返回值: bool
** 功能描述: 返回配置文件中保存的工具栏是否可见的信息
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
bool AppConfig::isToolBarVisible()
{
    return m_isToolBarVisible;
}

/*****************************************************************
** 函数名: isToolBarVisible()
** 输　入: 无
** 输　出: 无
** 返回值: bool
** 功能描述: 返回配置文件中保存的状态栏是否可见的信息
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
bool AppConfig::isStatusBarVisible()
{
    return m_isStatusBarVisible;
}

/*****************************************************************
** 函数名: isValid()
** 输　入: 无
** 输　出: 无
** 返回值: bool
** 功能描述: 返回配置文件中保存的是否有效的信息
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
bool AppConfig::isValid()
{
    return m_isValid;
}


