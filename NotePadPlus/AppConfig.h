/***********************************************************************************
 * 文件名 : AppConfig.h
 * 负责人 :
 * 创建日期 :
 * 文件描述 : 文本编辑器配置文件
 * 版权说明 :
 * 其它说明 :
 * 修改日志 :
***********************************************************************************/
#ifndef _APPCONFIG_H_
#define _APPCONFIG_H_

#include <QObject>
#include <QFont>
#include <QSize>
#include <QPoint>

class AppConfig : public QObject
{
    Q_OBJECT

    QFont m_editorFont;
    QSize m_mainWindowSize;
    QPoint m_mainWindowPoint;
    bool m_isAutoWrap;
    bool m_isToolBarVisible;
    bool m_isStatusBarVisible;
    bool m_isValid;

    bool restore();

public:
    explicit AppConfig(QObject *parent = 0);
    explicit AppConfig(QFont font, QPoint point, QSize size, bool isWrap, bool tbVisible, bool sbVisible, QObject* parent = 0);
    bool store();
    QFont editorFont();
    QSize mainWindowSize();
    QPoint mainWindowPoint();
    bool isAutoWrap();
    bool isToolBarVisible();
    bool isStatusBarVisible();
    bool isValid();
};

#endif // _APPCONFIG_H_
