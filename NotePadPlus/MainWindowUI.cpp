/***********************************************************************************
 * �ļ��� : MainWindowUI.cpp
 * ������ :
 * �������� :
 * �ļ����� : �๦���ı��༭������ʵ��
 * ��Ȩ˵�� :
 * ����˵�� :
 * �޸���־ :
***********************************************************************************/
#include "MainWindow.h"
#include "AppConfig.h"
#include <QMenu>
#include <QIcon>
#include <QSize>
#include <QStatusBar>
#include <QLabel>
#include <QPalette>
#include <QDebug>

/*****************************************************************
** ������: MainWindow
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������: MainWindow���캯��
** ������:
** �ա���:
** ˵����: �����ı��༭���������CenterWidget��һ���֣�ִ�й��캯��ʱ����û��
          ����CenterWidget��Ҳ����û�������ı��༭��������FindDialog��
          ReplaceDialog����������QPlainTextEdit*ֻ��������ΪNULL
******************************************************************/
MainWindow::MainWindow() : m_pFindDlg(new FindDialog(this, NULL)),
                           m_pReplaceDlg(new ReplaceDialog(this, NULL))
{
    setWindowTitle("�๦���ı��༭��- [ New ]");
    setAcceptDrops(true);

    m_filePath = "";

    m_isTextChanged = false;
}

/*****************************************************************
** ������: NewInstance
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ���׹�������MainWindow
** ������:
** �ա���:
** ˵����:
******************************************************************/
MainWindow* MainWindow::NewInstance()
{
    MainWindow* ret = new MainWindow();

    if((ret == NULL) || !ret->construct())
    {
        delete ret;
        ret = NULL;
    }

    return ret;
}

/*****************************************************************
** ������: construct()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ��ʼ���м�������˵�������������״̬���ȿ��ܷ���ʧ�ܵĳ�ʼ������
            �Լ��ָ��ϴιرն๦���ı��༭��ʱ������
** ������:
** �ա���:
** ˵����: �м�����������ȳ�ʼ������Ϊ�м�������������ı��༭����ǲ˵����е�
          �˵���������еĿ���������������
******************************************************************/
bool MainWindow::construct()
{
    bool ret = true;
    AppConfig config;

    ret = ret && initMainEditor();
    ret = ret && initMenuBar();
    ret = ret && initToolBar();
    ret = ret && initStatusBar();

    if( config.isValid() )
    {
        centerWidget->getMainEditor()->setFont( config.editorFont() );

        if( !config.isAutoWrap() )
        {
            centerWidget->getMainEditor()->setLineWrapMode(QPlainTextEdit::NoWrap);
            findMenuBarAction("�Զ�����")->setChecked(false);
            findToolBarAction("�Զ�����")->setChecked(false);
        }

        if( !config.isToolBarVisible() )
        {
            toolBar()->setVisible(false);
            findMenuBarAction("������")->setChecked(false);
            findToolBarAction("������")->setChecked(false);
        }

        if( !config.isStatusBarVisible() )
        {
            statusBar()->setVisible(false);
            findMenuBarAction("״̬��")->setChecked(false);
            findToolBarAction("״̬��")->setChecked(false);
        }

        move( config.mainWindowPoint() );
        resize( config.mainWindowSize() );
    }

    return ret;
}

/*****************************************************************
** ������: initMenuBar()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ��ʼ���˵���
** ������:
** �ա���:
** ˵����:
******************************************************************/
bool MainWindow::initMenuBar()
{
    bool ret = true;

    QMenuBar* mb = menuBar();

    ret = ret && initFileMenu(mb);
    ret = ret && initEditMenu(mb);
    ret = ret && initFormatMenu(mb);
    ret = ret && initViewMenu(mb);
    ret = ret && initHelpMenu(mb);

    return ret;
}

/*****************************************************************
** ������: initToolBar()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ��ʼ��������
** ������:
** �ա���:
** ˵����:
******************************************************************/
bool MainWindow::initToolBar()
{
    bool ret = true;

    QToolBar* tb = addToolBar("Tool Bar");

    tb->setIconSize(QSize(16,16));

    ret = ret && initFileToolItem(tb);
    tb->addSeparator();

    ret = ret && initEditToolItem(tb);
    tb->addSeparator();

    ret = ret && initFormatToolItem(tb);
    tb->addSeparator();

    ret = ret && initViewToolItem(tb);
    tb->addSeparator();

    ret = ret && initFunctionToolItem(tb);

    return ret;
}

/*****************************************************************
** ������: initStatusBar()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ��ʼ��״̬��
** ������:
** �ա���:
** ˵����:
******************************************************************/
bool MainWindow::initStatusBar()
{
    bool ret = true;
    QStatusBar* sb = statusBar();
    QLabel* label = new QLabel("�����Ŀ���� - ���� ���Ƴ� ���� ����� ����");

    if(label != NULL)
    {
        statusLbl.setMinimumWidth(200);
        statusLbl.setAlignment(Qt::AlignCenter);
        statusLbl.setText("�� : 1    �� : 1");

        label->setMinimumWidth(200);
        label->setAlignment(Qt::AlignCenter);

        sb->addPermanentWidget(new QLabel());
        sb->addPermanentWidget(&statusLbl);
        sb->addPermanentWidget(label);
    }
    else
    {
        ret = false;
    }

    return ret;
}

/*****************************************************************
** ������: initMainEditor()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ��ʼ���м����
** ������:
** �ա���:
** ˵����:
******************************************************************/
bool MainWindow::initMainEditor()
{
    bool ret = true;

    centerWidget = CenterWidget::NewInstance();
    if(centerWidget)
    {
        QPalette p = centerWidget->getMainEditor()->palette();

        p.setColor(QPalette::Inactive, QPalette::Highlight, p.color(QPalette::Active, QPalette::Highlight));
        p.setColor(QPalette::Inactive, QPalette::HighlightedText, p.color(QPalette::Active, QPalette::HighlightedText));

        centerWidget->getMainEditor()->setPalette(p);

        connect(centerWidget->getMainEditor(),SIGNAL(textChanged()),this,SLOT(onTextChanged()));
        connect(centerWidget->getMainEditor(),SIGNAL(copyAvailable(bool)),this,SLOT(onCopyAvailable(bool)));
        connect(centerWidget->getMainEditor(),SIGNAL(redoAvailable(bool)),this,SLOT(onRedoAvailable(bool)));
        connect(centerWidget->getMainEditor(),SIGNAL(undoAvailable(bool)),this,SLOT(onUndoAvailable(bool)));
        connect(centerWidget->getMainEditor(),SIGNAL(cursorPositionChanged()),this,SLOT(onCursorPositionChanged()));

        m_pFindDlg->setPlainTextEdit(centerWidget->getMainEditor());
        m_pReplaceDlg->setPlainTextEdit(centerWidget->getMainEditor());

        setCentralWidget(centerWidget);
    }
    else
    {
        ret = false;
    }

    return ret;
}

/*****************************************************************
** ������: initFileMenu(QMenuBar* mb)
** �䡡��: QMenuBar* mb : �˵���ָ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ��ʼ���ļ������˵���
** ������:
** �ա���:
** ˵����:
******************************************************************/
bool MainWindow::initFileMenu(QMenuBar* mb)
{
    QMenu* menu = new QMenu("�ļ�(&F)",mb);
    bool ret = (menu != NULL);

    if(ret)
    {
        QAction* action = NULL;

        ret = ret && makeAction(action,menu,"�½�(&N)",Qt::CTRL + Qt::Key_N);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),this,SLOT(onFileNew()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"��(&O)...",Qt::CTRL + Qt::Key_O);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),this,SLOT(onFileOpen()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"����(&S)",Qt::CTRL + Qt::Key_S);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),this,SLOT(onFileSave()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"���Ϊ(&A)...",0);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),this,SLOT(onFileSaveAs()));
            menu->addAction(action);
        }

        menu->addSeparator();

        ret = ret && makeAction(action,menu,"��ӡ(&P)...",Qt::CTRL + Qt::Key_P);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),this,SLOT(onFilePrint()));
            menu->addAction(action);
        }

        menu->addSeparator();

        ret = ret && makeAction(action,menu,"�˳�(X)",0);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),this,SLOT(onFileExit()));
            menu->addAction(action);
        }
    }

    if(ret)
    {
        mb->addMenu(menu);
    }
    else
    {
        delete menu;
    }

    return ret;
}

/*****************************************************************
** ������: initEditMenu(QMenuBar* mb)
** �䡡��: QMenuBar* mb : �˵���ָ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ��ʼ���༭�����˵���
** ������:
** �ա���:
** ˵����:
******************************************************************/
bool MainWindow::initEditMenu(QMenuBar* mb)
{
    QMenu* menu = new QMenu("�༭(&E)",mb);
    bool ret = (menu != NULL);

    if(ret)
    {
        QAction* action = NULL;

        ret = ret && makeAction(action,menu,"����(&U)",Qt::CTRL + Qt::Key_Z);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),centerWidget->getMainEditor(),SLOT(undo()));
            action->setEnabled(false);
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"�ָ�(&R)...",Qt::CTRL + Qt::Key_Y);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),centerWidget->getMainEditor(),SLOT(redo()));
            action->setEnabled(false);
            menu->addAction(action);
        }

        menu->addSeparator();

        ret = ret && makeAction(action,menu,"����(&T)",Qt::CTRL + Qt::Key_X);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),centerWidget->getMainEditor(),SLOT(cut()));
            action->setEnabled(false);
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"����(&C)...",Qt::CTRL + Qt::Key_C);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),centerWidget->getMainEditor(),SLOT(copy()));
            action->setEnabled(false);
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"ճ��(&P)...",Qt::CTRL + Qt::Key_V);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),centerWidget->getMainEditor(),SLOT(paste()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"ɾ��(&L)",Qt::Key_Delete);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),this,SLOT(onEditDelete()));
            menu->addAction(action);
        }

        menu->addSeparator();

        ret = ret && makeAction(action,menu,"����(&F)...",Qt::CTRL + Qt::Key_F);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),this,SLOT(onEditFind()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"�滻(&R)...",Qt::CTRL + Qt::Key_H);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),this,SLOT(onEditReplace()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"��λ(&G)...",Qt::CTRL + Qt::Key_G);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),this,SLOT(onEditGoto()));
            menu->addAction(action);
        }

        menu->addSeparator();

        ret = ret && makeAction(action,menu,"ȫѡ(&A)",Qt::CTRL + Qt::Key_A);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),centerWidget->getMainEditor(),SLOT(selectAll()));
            menu->addAction(action);
        }
    }

    if(ret)
    {
        mb->addMenu(menu);
    }
    else
    {
        delete menu;
    }

    return ret;
}

/*****************************************************************
** ������: initFormatMenu(QMenuBar* mb)
** �䡡��: QMenuBar* mb : �˵���ָ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ��ʼ����ʽ�����˵���
** ������:
** �ա���:
** ˵����:
******************************************************************/
bool MainWindow::initFormatMenu(QMenuBar* mb)
{
    QMenu* menu = new QMenu("��ʽ(&O)",mb);
    bool ret = (menu != NULL);

    if(ret)
    {
        QAction* action = NULL;

        ret = ret && makeAction(action,menu,"�Զ�����(&W)",0);
        if(ret)
        {
            action->setCheckable(true);
            action->setChecked(true);
            connect(action,SIGNAL(triggered()),this,SLOT(onFormatWrap()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"����(&F)...",0);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),this,SLOT(onFormatFont()));
            menu->addAction(action);
        }
    }

    if(ret)
    {
        mb->addMenu(menu);
    }
    else
    {
        delete menu;
    }

    return ret;
}

/*****************************************************************
** ������: initViewMenu(QMenuBar* mb)
** �䡡��: QMenuBar* mb : �˵���ָ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ��ʼ���鿴�����˵���
** ������:
** �ա���:
** ˵����:
******************************************************************/
bool MainWindow::initViewMenu(QMenuBar* mb)
{
    QMenu* menu = new QMenu("�鿴(&V)",mb);
    bool ret = (menu != NULL);

    if(ret)
    {
        QAction* action = NULL;

        ret = ret && makeAction(action,menu,"������(&T)",0);
        if(ret)
        {
            action->setCheckable(true);
            action->setChecked(true);
            connect(action,SIGNAL(triggered()),this,SLOT(onViewToolBar()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"״̬��(&S)",0);
        if(ret)
        {
            action->setCheckable(true);
            action->setChecked(true);
            connect(action,SIGNAL(triggered()),this,SLOT(onViewStatusBar()));
            menu->addAction(action);
        }
    }

    if(ret)
    {
        mb->addMenu(menu);
    }
    else
    {
        delete menu;
    }

    return ret;
}

/*****************************************************************
** ������: initHelpMenu(QMenuBar* mb)
** �䡡��: QMenuBar* mb : �˵���ָ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ��ʼ�����������˵���
** ������:
** �ա���:
** ˵����:
******************************************************************/
bool MainWindow::initHelpMenu(QMenuBar* mb)
{
    QMenu* menu = new QMenu("����(&H)",mb);
    bool ret = (menu != NULL);

    if(ret)
    {
        QAction* action = NULL;

        ret = ret && makeAction(action,menu,"ѧԺ����",0);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),this,SLOT(onHelpManual()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"���ڶ๦���ı��༭��...",0);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),this,SLOT(onHelpAbout()));
            menu->addAction(action);
        }
    }

    if(ret)
    {
        mb->addMenu(menu);
    }
    else
    {
        delete menu;
    }

    return ret;
}

/*****************************************************************
** ������: initFileToolItem(QToolBar* tb)
** �䡡��: QToolBar* mb : ������ָ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ��ʼ���ļ�������
** ������:
** �ա���:
** ˵����:
******************************************************************/
bool MainWindow::initFileToolItem(QToolBar* tb)
{
    bool ret = true;
    QAction* action = NULL;

    ret = ret && makeAction(action,tb,"�½�",":/Res/pic/new.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(onFileNew()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"��",":/Res/pic/open.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(onFileOpen()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"����",":Res/pic/save.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(onFileSave()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"���Ϊ",":Res/pic/saveas.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(onFileSaveAs()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"��ӡ",":Res/pic/print.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(onFilePrint()));
        tb->addAction(action);
    }

    return ret;
}

/*****************************************************************
** ������: initEditToolItem(QToolBar* tb)
** �䡡��: QToolBar* mb : ������ָ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ��ʼ���༭������
** ������:
** �ա���:
** ˵����:
******************************************************************/
bool MainWindow::initEditToolItem(QToolBar* tb)
{
    bool ret = true;
    QAction* action = NULL;

    ret = ret && makeAction(action,tb,"����",":/Res/pic/undo.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),centerWidget->getMainEditor(),SLOT(undo()));
        action->setEnabled(false);
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"�ָ�",":/Res/pic/redo.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),centerWidget->getMainEditor(),SLOT(redo()));
        action->setEnabled(false);
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"����",":/Res/pic/cut.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),centerWidget->getMainEditor(),SLOT(cut()));
        action->setEnabled(false);
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"����",":/Res/pic/copy.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),centerWidget->getMainEditor(),SLOT(copy()));
        action->setEnabled(false);
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"ճ��",":/Res/pic/paste.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),centerWidget->getMainEditor(),SLOT(paste()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"����",":/Res/pic/find.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(onEditFind()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"�滻",":/Res/pic/replace.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(onEditReplace()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"��λ",":/Res/pic/goto.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(onEditGoto()));
        tb->addAction(action);
    }

    return ret;
}

/*****************************************************************
** ������: initFormatToolItem(QToolBar* tb)
** �䡡��: QToolBar* mb : ������ָ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ��ʼ����ʽ������
** ������:
** �ա���:
** ˵����:
******************************************************************/
bool MainWindow::initFormatToolItem(QToolBar* tb)
{
    bool ret = true;
    QAction* action = NULL;

    ret = ret && makeAction(action,tb,"�Զ�����",":/Res/pic/wrap.png");
    if(ret)
    {
        action->setCheckable(true);
        action->setChecked(true);
        connect(action,SIGNAL(triggered()),this,SLOT(onFormatWrap()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"����",":/Res/pic/font.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(onFormatFont()));
        tb->addAction(action);
    }

    return ret;
}

/*****************************************************************
** ������: initViewToolItem(QToolBar* tb)
** �䡡��: QToolBar* mb : ������ָ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ��ʼ���鿴������
** ������:
** �ա���:
** ˵����:
******************************************************************/
bool MainWindow::initViewToolItem(QToolBar* tb)
{
    bool ret = true;
    QAction* action = NULL;

    ret = ret && makeAction(action,tb,"������",":/Res/pic/tool.png");
    if(ret)
    {
        action->setCheckable(true);
        action->setChecked(true);
        connect(action,SIGNAL(triggered()),this,SLOT(onViewToolBar()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"״̬��",":/Res/pic/status.png");
    if(ret)
    {
        action->setCheckable(true);
        action->setChecked(true);
        connect(action,SIGNAL(triggered()),this,SLOT(onViewStatusBar()));
        tb->addAction(action);
    }

    return ret;
}

/*****************************************************************
** ������: initFunctionToolItem(QToolBar* tb);
** �䡡��: QToolBar* mb : ������ָ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ��ʼ���๦��ѡ�񹤾���
** ������:
** �ա���:
** ˵����:
******************************************************************/
bool MainWindow::initFunctionToolItem(QToolBar* tb)
{
    bool ret = true;
    QAction* action = NULL;

    ret = ret && makeAction(action, tb, "������", ":/Res/pic/calculator.jpg");
    if(ret)
    {
        action->setCheckable(true);
        action->setChecked(false);
        connect(action,SIGNAL(triggered()),this,SLOT(onCalcFunc()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action, tb, "��ͼ��", ":/Res/pic/drawing.bmp");
    if(ret)
    {
        action->setCheckable(true);
        action->setChecked(false);
        connect(action,SIGNAL(triggered()),this,SLOT(onDrawFunc()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action, tb, "����ͨ��", ":/Res/pic/port.png");
    if(ret)
    {
        action->setCheckable(true);
        action->setChecked(false);
        connect(action,SIGNAL(triggered()),this,SLOT(onPortFunc()));
        tb->addAction(action);
    }

    return ret;
}

/*****************************************************************
** ������: makeAction(QAction*& action,QWidget* parent,QString text,int key)
** �䡡��: QAction*& action :  �����ɵĲ˵���ָ��
          QWidget* parent  :  ���ɲ˵���ĸ�����󣨸ò˵������ڵ������˵��飩
          QString text     :  ��ʾ�ı�
          int key          :  ��ݼ�
** �䡡��: ��
** ����ֵ: ��
** ��������: ���ɲ˵���
** ������:
** �ա���:
** ˵����:
******************************************************************/
bool MainWindow::makeAction(QAction*& action, QWidget* parent, QString text, int key)
{
    bool ret = true;

    action = new QAction(text, parent);

    if(action != NULL)
    {
        action->setShortcut(QKeySequence(key));
    }
    else
    {
        ret = false;
    }

    return ret;
}

/*****************************************************************
** ������: makeAction(QAction*& action,QWidget* parent,QString text,QString icon)
** �䡡��: QAction*& action :  �����ɵĿ����ָ��
          QWidget* parent  :  ���ɿ����ĸ�����󣨸ÿ�������ڵĹ�������
          QString text     :  ��ʾ�ı�
          int key          :  ͼ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ���ɿ����
** ������:
** �ա���:
** ˵����:
******************************************************************/
bool MainWindow::makeAction(QAction*& action, QWidget* parent, QString text, QString icon)
{
    bool ret = true;

    action = new QAction("", parent);

    if(action != NULL)
    {
        action->setToolTip(text);
        action->setIcon(QIcon(icon));
    }
    else
    {
        ret = false;
    }

    return ret;
}

/*****************************************************************
** ������: toolBar()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ���ع�����ָ��
** ������:
** �ա���:
** ˵����:
******************************************************************/
QToolBar* MainWindow::toolBar()
{
    QToolBar* ret = NULL;
    const QObjectList& list = children();

    /*����MainWindow������*/
    for(int i = 0; i < list.count(); i++)
    {
        QToolBar* tb = dynamic_cast<QToolBar*>(list[i]);

        if(tb != NULL)
        {
            ret = tb;
            break;
        }
    }

    return ret;
}

/*****************************************************************
** ������: ~MainWindow()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ��������
** ������:
** �ա���:
** ˵����:
******************************************************************/
MainWindow::~MainWindow()
{

}
