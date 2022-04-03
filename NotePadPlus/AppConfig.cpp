/***********************************************************************************
 * �ļ��� : AppConfig.cpp
 * ������ :
 * �������� :
 * �ļ����� : �ı��༭�������ļ�
 * ��Ȩ˵�� :
 * ����˵�� : �رն๦���ı��༭��֮ǰ�������ý��
 * �޸���־ :
***********************************************************************************/
#include "AppConfig.h"
#include <QFile>
#include <QDataStream>
#include <QApplication>

/*****************************************************************
** ������: AppConfig(QObject* parent)
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������: �����ļ��๹�캯��
** ������:
** �ա���:
** ˵����:
******************************************************************/
AppConfig::AppConfig(QObject* parent) : QObject(parent)
{
    m_isValid = restore();
}

/*****************************************************************
** ������: AppConfig(QObject* parent)
** �䡡��: QFont font ������
          QPoint point : ����
          QSize size : ���ڴ�С
          bool isWrap : �Ƿ��Զ�����
          bool tbVisible : �������Ƿ�ɼ�
          bool sbVisible : ״̬���Ƿ�ɼ�
          QObject* parent : ����
** �䡡��: ��
** ����ֵ: ��
** ��������: �����ļ��๹�캯�������أ�
** ������:
** �ա���:
** ˵����:
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
** ������: restore()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: bool
** ��������: �������ļ������������ļ������ݻָ�����
** ������:
** �ա���:
** ˵����:
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
** ������: store()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: bool
** ��������: ���������ļ�������ǰ���ô��������ļ���
** ������:
** �ա���:
** ˵����:
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
** ������: editorFont()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: QFont
** ��������: ���������ļ��б����������Ϣ
** ������:
** �ա���:
** ˵����:
******************************************************************/
QFont AppConfig::editorFont()
{
    return m_editorFont;
}

/*****************************************************************
** ������: mainWindowSize()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: QSize
** ��������: ���������ļ��б���Ĵ��ڴ�С
** ������:
** �ա���:
** ˵����:
******************************************************************/
QSize AppConfig::mainWindowSize()
{
    return m_mainWindowSize;
}

/*****************************************************************
** ������: mainWindowPoint()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: QPoint
** ��������: ���������ļ��б���Ĵ�������
** ������:
** �ա���:
** ˵����:
******************************************************************/
QPoint AppConfig::mainWindowPoint()
{
    return m_mainWindowPoint;
}

/*****************************************************************
** ������: isAutoWrap()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: bool
** ��������: ���������ļ��б�����Ƿ��Զ�������Ϣ
** ������:
** �ա���:
** ˵����:
******************************************************************/
bool AppConfig::isAutoWrap()
{
    return m_isAutoWrap;
}

/*****************************************************************
** ������: isToolBarVisible()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: bool
** ��������: ���������ļ��б���Ĺ������Ƿ�ɼ�����Ϣ
** ������:
** �ա���:
** ˵����:
******************************************************************/
bool AppConfig::isToolBarVisible()
{
    return m_isToolBarVisible;
}

/*****************************************************************
** ������: isToolBarVisible()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: bool
** ��������: ���������ļ��б����״̬���Ƿ�ɼ�����Ϣ
** ������:
** �ա���:
** ˵����:
******************************************************************/
bool AppConfig::isStatusBarVisible()
{
    return m_isStatusBarVisible;
}

/*****************************************************************
** ������: isValid()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: bool
** ��������: ���������ļ��б�����Ƿ���Ч����Ϣ
** ������:
** �ա���:
** ˵����:
******************************************************************/
bool AppConfig::isValid()
{
    return m_isValid;
}


