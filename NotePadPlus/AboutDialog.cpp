/***********************************************************************************
 * �ļ��� : AboutDialog.cpp
 * ������ :
 * �������� :
 * �ļ����� : �����ڡ��Ի���
 * ��Ȩ˵�� :
 * ����˵�� :
 * �޸���־ :
***********************************************************************************/
#include "AboutDialog.h"
#include <QPixmap>
#include <QPalette>

/***********************************************************************************
 * �ļ��� : AboutDialog.cpp
 * ������ :
 * �������� :
 * �ļ����� : �����ڡ��Ի����캯��
 * ��Ȩ˵�� :
 * ����˵�� :
 * �޸���־ :
***********************************************************************************/
AboutDialog::AboutDialog(QWidget* parent) : QDialog(parent, Qt::WindowCloseButtonHint),
                                            m_logoLbl(this),
                                            m_qqLbl(this),
                                            m_closeBtn(this),
                                            m_infoEdit(this)
{
    QPixmap pm(":Res/pic/wri.bmp");

    pm = pm.scaled(120, 120, Qt::KeepAspectRatio);

    m_logoLbl.setPixmap(pm);
    m_logoLbl.move(20, 20);
    m_logoLbl.resize(120, 120);

    QPalette p = m_infoEdit.palette();
    p.setColor(QPalette::Active, QPalette::Base, palette().color(QPalette::Active, QPalette::Background));
    p.setColor(QPalette::Inactive, QPalette::Base, palette().color(QPalette::Inactive, QPalette::Background));

    m_infoEdit.move(200, 30);
    m_infoEdit.resize(180, 130);
    m_infoEdit.setPalette(p);
    m_infoEdit.setFrameStyle(QFrame::NoFrame);
    m_infoEdit.setReadOnly(true);
    m_infoEdit.insertPlainText("�๦���ı��༭�����������Ŀ\n\nƽ̨: Qt 4.7.4\n\n�汾: 1.0.0\n\n����Ȩ: ���� ���Ƴ� ���� ����� ����");

    m_closeBtn.move(273, 175);
    m_closeBtn.resize(100, 30);
    m_closeBtn.setText("�ر�");

    m_qqLbl.move(22, 184);
    m_qqLbl.setText("2021���о���QQȺ : 316757052");

    setFixedSize(390, 230);
    setWindowTitle("���ڶ๦���ı��༭��");

    connect(&m_closeBtn,SIGNAL(clicked()),this,SLOT(close()));
}
