/***********************************************************************************
 * 文件名 : AboutDialog.h
 * 负责人 :
 * 创建日期 :
 * 文件描述 : “关于”对话框
 * 版权说明 :
 * 其它说明 :
 * 修改日志 :
***********************************************************************************/
#ifndef _ABOUTDIALOG_H_
#define _ABOUTDIALOG_H_

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QPlainTextEdit>

class AboutDialog : public QDialog
{
    Q_OBJECT

    QLabel m_logoLbl;
    QLabel m_qqLbl;
    QPushButton m_closeBtn;
    QPlainTextEdit m_infoEdit;

public:
    explicit AboutDialog(QWidget *parent = 0);  
};

#endif // _ABOUTDIALOG_H_
