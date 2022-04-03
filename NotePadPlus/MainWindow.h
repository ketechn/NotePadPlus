/***********************************************************************************
 * 文件名 : MainWindow.h
 * 负责人 :
 * 创建日期 :
 * 文件描述 : 主程序类
 * 版权说明 :
 * 其它说明 :
 * 修改日志 :
***********************************************************************************/
#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QtGui/QMainWindow>
#include <QKeySequence>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>
#include <QPlainTextEdit>
#include <QLabel>
#include <QFileDialog>
#include <QSharedPointer>
#include "FindDialog.h"
#include "ReplaceDialog.h"
#include "CenterWidget.h"
#include "Common.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    CenterWidget* centerWidget;
    QLabel statusLbl;
    QString m_filePath;
    bool m_isTextChanged;
    QSharedPointer<FindDialog> m_pFindDlg;
    QSharedPointer<ReplaceDialog> m_pReplaceDlg;

    MainWindow();
    MainWindow(const MainWindow&);
    MainWindow& operator = (const MainWindow&);

    bool construct();
    bool initMenuBar();
    bool initToolBar();
    bool initStatusBar();
    bool initMainEditor();

    bool initFileMenu(QMenuBar* mb);
    bool initEditMenu(QMenuBar* mb);
    bool initFormatMenu(QMenuBar* mb);
    bool initViewMenu(QMenuBar* mb);
    bool initHelpMenu(QMenuBar* mb);

    bool initFileToolItem(QToolBar* tb);
    bool initEditToolItem(QToolBar* tb);
    bool initFormatToolItem(QToolBar* tb);
    bool initViewToolItem(QToolBar* tb);
    bool initFunctionToolItem(QToolBar* tb);

    bool makeAction(QAction*& action,QWidget* parent,QString text,int key);
    bool makeAction(QAction*& action,QWidget* parent,QString tip,QString icon);

    QString showFileDialog(QFileDialog::AcceptMode mode,QString title);
    int showQueryMessage(QString message);
    void ShowErrorMessage(QString message);
    QString saveCurrentData(QString path = "");
    void preEditorChange();
    void openFileToEditor(QString path);
    QAction* findMenuBarAction(QString text);
    QAction* findToolBarAction(QString text);

protected:
    void closeEvent(QCloseEvent* e);
    void dragEnterEvent(QDragEnterEvent* e);
    void dropEvent(QDropEvent* e);

private slots:
    void onFileNew();
    void onFileOpen();
    void onFileSave();
    void onFileSaveAs();
    void onFilePrint();
    void onFileExit();
    void onTextChanged();
    void onCopyAvailable(bool available);
    void onRedoAvailable(bool available);
    void onUndoAvailable(bool available);
    void onCursorPositionChanged();
    void onEditFind();
    void onEditReplace();
    void onEditDelete();
    void onEditGoto();
    void onFormatFont();
    void onFormatWrap();
    void onViewToolBar();
    void onViewStatusBar();
    void onHelpManual();
    void onHelpAbout();
    void onCalcFunc();
    void onDrawFunc();
    void onPortFunc();

public:
    static MainWindow* NewInstance();
    QToolBar* toolBar();
    void openFile(QString path);
    ~MainWindow();
};

#endif // _MAINWINDOW_H_
