/***********************************************************************************
 * 文件名 : ReplaceDialog.h
 * 负责人 :
 * 创建日期 :
 * 文件描述 : 替换对话框
 * 版权说明 :
 * 其它说明 :
 * 修改日志 :
***********************************************************************************/
#ifndef _REPLACEDIALOG_H_
#define _REPLACEDIALOG_H_

#include "FindDialog.h"

class ReplaceDialog : public FindDialog
{
    Q_OBJECT

protected:
    QLabel m_replaceLbl;
    QLineEdit m_replaceEdit;
    QPushButton m_replaceBtn;
    QPushButton m_replaceAllBtn;

    void initControl();
    void connectSlot();

protected slots:
    void onReplaceClicked();
    void onReplaceAllClicked();

public:
    explicit ReplaceDialog(QWidget* parent = 0, QPlainTextEdit* pText = 0);
        
};

#endif // _REPLACEDIALOG_H_
