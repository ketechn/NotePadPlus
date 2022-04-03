/***********************************************************************************
 * 文件名 : FindDialog.cpp
 * 负责人 :
 * 创建日期 :
 * 文件描述 : 查找对话框
 * 版权说明 :
 * 其它说明 :
 * 修改日志 :
***********************************************************************************/
#include "FindDialog.h"
#include <QEvent>
#include <QTextCursor>
#include <QMessageBox>

FindDialog::FindDialog(QWidget* parent,QPlainTextEdit* pText)
    : QDialog(parent,Qt::WindowCloseButtonHint | Qt::Drawer)
{
    initControl();
    connectSlot();
    setLayout(&m_layout);
    setWindowTitle("查找");
    setPlainTextEdit(pText);
}

void FindDialog::initControl()
{
    m_findLbl.setText("查找内容:");
    m_findBtn.setText("查找下一个");
    m_closeBtn.setText("关闭");
    m_matchChkBx.setText("区分大小写:");
    m_forwardBtn.setText("上");
    m_backwardBtn.setText("下");
    m_backwardBtn.setChecked(true);
    m_radioGrpBx.setTitle("方向");

    m_hbLayout.addWidget(&m_forwardBtn);
    m_hbLayout.addWidget(&m_backwardBtn);
    m_radioGrpBx.setLayout(&m_hbLayout);

    m_layout.setSpacing(10);
    m_layout.addWidget(&m_findLbl,0,0);
    m_layout.addWidget(&m_findEdit,0,1);
    m_layout.addWidget(&m_findBtn,0,2);
    m_layout.addWidget(&m_matchChkBx,1,0);
    m_layout.addWidget(&m_radioGrpBx,1,1);
    m_layout.addWidget(&m_closeBtn,1,2);
}

void FindDialog::connectSlot()
{
    connect(&m_findBtn,SIGNAL(clicked()),this,SLOT(onFindClicked()));
    connect(&m_closeBtn,SIGNAL(clicked()),this,SLOT(onCloseClicked()));
}

void FindDialog::setPlainTextEdit(QPlainTextEdit* pText)
{
    m_pText = pText;
}

QPlainTextEdit* FindDialog::getPlainTextEdit()
{
    return m_pText;
}

void FindDialog::onFindClicked()
{
    QString target = m_findEdit.text();

    if((m_pText != NULL) && (target != NULL))
    {
        QString text = m_pText->toPlainText();
        QTextCursor c = m_pText->textCursor();
        int index = -1;

        if( m_backwardBtn.isChecked() )
        {
            index = text.indexOf(target, c.position(), m_matchChkBx.isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);

            if(index >= 0)
            {
                c.setPosition(index);
                c.setPosition(index + target.length(), QTextCursor::KeepAnchor);

                m_pText->setTextCursor(c);
            }
        }

        if( m_forwardBtn.isChecked() )
        {
            index = text.lastIndexOf(target, c.position() - text.length() - 1, m_matchChkBx.isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);

            if(index >= 0)
            {
                c.setPosition(index + target.length());
                c.setPosition(index, QTextCursor::KeepAnchor);

                m_pText->setTextCursor(c);
            }
        }

        if( index < 0 )
        {
            QMessageBox msg(this);

            msg.setWindowTitle("查找");
            msg.setText("无法找到 \"" + target + "\" 更多...");
            msg.setIcon(QMessageBox::Information);
            msg.setStandardButtons(QMessageBox::Ok);

            msg.exec();
        }
    }
}

void FindDialog::onCloseClicked()
{
    close();
}

bool FindDialog::event(QEvent* evt)
{
    if(evt->type() == QEvent::Close)
    {
        hide();

        return true;
    }

    return QDialog::event(evt);
}
