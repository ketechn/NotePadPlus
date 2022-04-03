/***********************************************************************************
 * 文件名 : AboutDialog.cpp
 * 负责人 :
 * 创建日期 :
 * 文件描述 : “关于”对话框
 * 版权说明 :
 * 其它说明 :
 * 修改日志 :
***********************************************************************************/
#include "AboutDialog.h"
#include <QPixmap>
#include <QPalette>

/***********************************************************************************
 * 文件名 : AboutDialog.cpp
 * 负责人 :
 * 创建日期 :
 * 文件描述 : “关于”对话框构造函数
 * 版权说明 :
 * 其它说明 :
 * 修改日志 :
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
    m_infoEdit.insertPlainText("多功能文本编辑器软件开发项目\n\n平台: Qt 4.7.4\n\n版本: 1.0.0\n\n著作权: 柯特 付淦臣 李威 李书恒 范悦");

    m_closeBtn.move(273, 175);
    m_closeBtn.resize(100, 30);
    m_closeBtn.setText("关闭");

    m_qqLbl.move(22, 184);
    m_qqLbl.setText("2021级研究生QQ群 : 316757052");

    setFixedSize(390, 230);
    setWindowTitle("关于多功能文本编辑器");

    connect(&m_closeBtn,SIGNAL(clicked()),this,SLOT(close()));
}
