/***********************************************************************************
 * �ļ��� : FindDialog.h
 * ������ :
 * �������� :
 * �ļ����� : ���ҶԻ���
 * ��Ȩ˵�� :
 * ����˵�� :
 * �޸���־ :
***********************************************************************************/
#ifndef _FINDDIALOG_H_
#define _FINDDIALOG_H_

#include <QDialog>
#include <QEvent>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QPlainTextEdit>
#include <QPointer>

class FindDialog : public QDialog
{
    Q_OBJECT

protected:
    QGroupBox m_radioGrpBx;

    QGridLayout m_layout;
    QHBoxLayout m_hbLayout;

    QLabel m_findLbl;
    QLineEdit m_findEdit;
    QPushButton m_findBtn;
    QPushButton m_closeBtn;
    QCheckBox m_matchChkBx;
    QRadioButton m_forwardBtn;
    QRadioButton m_backwardBtn;

    QPointer<QPlainTextEdit> m_pText;

    void initControl();
    void connectSlot();

protected slots:
    void onFindClicked();
    void onCloseClicked();

public:
    FindDialog(QWidget* parent = 0,QPlainTextEdit* pText = 0);
    void setPlainTextEdit(QPlainTextEdit* pText);
    QPlainTextEdit* getPlainTextEdit();
    bool event(QEvent* evt);
};

#endif //_FINDDIALOG_H_
