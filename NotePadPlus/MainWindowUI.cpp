/***********************************************************************************
 * 文件名 : MainWindowUI.cpp
 * 负责人 :
 * 创建日期 :
 * 文件描述 : 多功能文本编辑器界面实现
 * 版权说明 :
 * 其它说明 :
 * 修改日志 :
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
** 函数名: MainWindow
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述: MainWindow构造函数
** 作　者:
** 日　期:
** 说　明: 由于文本编辑组件现在是CenterWidget的一部分，执行构造函数时还并没有
          生成CenterWidget，也就是没有生成文本编辑组件，因此FindDialog和
          ReplaceDialog的所依赖的QPlainTextEdit*只能先设置为NULL
******************************************************************/
MainWindow::MainWindow() : m_pFindDlg(new FindDialog(this, NULL)),
                           m_pReplaceDlg(new ReplaceDialog(this, NULL))
{
    setWindowTitle("多功能文本编辑器- [ New ]");
    setAcceptDrops(true);

    m_filePath = "";

    m_isTextChanged = false;
}

/*****************************************************************
** 函数名: NewInstance
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述: 二阶构造生成MainWindow
** 作　者:
** 日　期:
** 说　明:
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
** 函数名: construct()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述: 初始化中间组件，菜单栏，工具栏，状态栏等可能返回失败的初始化操作
            以及恢复上次关闭多功能文本编辑器时的配置
** 作　者:
** 日　期:
** 说　明: 中间组件必须首先初始化，因为中间组件所包含的文本编辑组件是菜单栏中的
          菜单项，工具栏中的快捷项所必须的依赖
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
            findMenuBarAction("自动换行")->setChecked(false);
            findToolBarAction("自动换行")->setChecked(false);
        }

        if( !config.isToolBarVisible() )
        {
            toolBar()->setVisible(false);
            findMenuBarAction("工具栏")->setChecked(false);
            findToolBarAction("工具栏")->setChecked(false);
        }

        if( !config.isStatusBarVisible() )
        {
            statusBar()->setVisible(false);
            findMenuBarAction("状态栏")->setChecked(false);
            findToolBarAction("状态栏")->setChecked(false);
        }

        move( config.mainWindowPoint() );
        resize( config.mainWindowSize() );
    }

    return ret;
}

/*****************************************************************
** 函数名: initMenuBar()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述: 初始化菜单栏
** 作　者:
** 日　期:
** 说　明:
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
** 函数名: initToolBar()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述: 初始化工具栏
** 作　者:
** 日　期:
** 说　明:
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
** 函数名: initStatusBar()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述: 初始化状态栏
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
bool MainWindow::initStatusBar()
{
    bool ret = true;
    QStatusBar* sb = statusBar();
    QLabel* label = new QLabel("软件项目开发 - 柯特 付淦臣 李威 李书恒 范悦");

    if(label != NULL)
    {
        statusLbl.setMinimumWidth(200);
        statusLbl.setAlignment(Qt::AlignCenter);
        statusLbl.setText("行 : 1    列 : 1");

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
** 函数名: initMainEditor()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述: 初始化中间组件
** 作　者:
** 日　期:
** 说　明:
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
** 函数名: initFileMenu(QMenuBar* mb)
** 输　入: QMenuBar* mb : 菜单栏指针
** 输　出: 无
** 返回值: 无
** 功能描述: 初始化文件下拉菜单组
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
bool MainWindow::initFileMenu(QMenuBar* mb)
{
    QMenu* menu = new QMenu("文件(&F)",mb);
    bool ret = (menu != NULL);

    if(ret)
    {
        QAction* action = NULL;

        ret = ret && makeAction(action,menu,"新建(&N)",Qt::CTRL + Qt::Key_N);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),this,SLOT(onFileNew()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"打开(&O)...",Qt::CTRL + Qt::Key_O);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),this,SLOT(onFileOpen()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"保存(&S)",Qt::CTRL + Qt::Key_S);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),this,SLOT(onFileSave()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"另存为(&A)...",0);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),this,SLOT(onFileSaveAs()));
            menu->addAction(action);
        }

        menu->addSeparator();

        ret = ret && makeAction(action,menu,"打印(&P)...",Qt::CTRL + Qt::Key_P);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),this,SLOT(onFilePrint()));
            menu->addAction(action);
        }

        menu->addSeparator();

        ret = ret && makeAction(action,menu,"退出(X)",0);
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
** 函数名: initEditMenu(QMenuBar* mb)
** 输　入: QMenuBar* mb : 菜单栏指针
** 输　出: 无
** 返回值: 无
** 功能描述: 初始化编辑下拉菜单组
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
bool MainWindow::initEditMenu(QMenuBar* mb)
{
    QMenu* menu = new QMenu("编辑(&E)",mb);
    bool ret = (menu != NULL);

    if(ret)
    {
        QAction* action = NULL;

        ret = ret && makeAction(action,menu,"撤销(&U)",Qt::CTRL + Qt::Key_Z);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),centerWidget->getMainEditor(),SLOT(undo()));
            action->setEnabled(false);
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"恢复(&R)...",Qt::CTRL + Qt::Key_Y);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),centerWidget->getMainEditor(),SLOT(redo()));
            action->setEnabled(false);
            menu->addAction(action);
        }

        menu->addSeparator();

        ret = ret && makeAction(action,menu,"剪切(&T)",Qt::CTRL + Qt::Key_X);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),centerWidget->getMainEditor(),SLOT(cut()));
            action->setEnabled(false);
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"复制(&C)...",Qt::CTRL + Qt::Key_C);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),centerWidget->getMainEditor(),SLOT(copy()));
            action->setEnabled(false);
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"粘贴(&P)...",Qt::CTRL + Qt::Key_V);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),centerWidget->getMainEditor(),SLOT(paste()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"删除(&L)",Qt::Key_Delete);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),this,SLOT(onEditDelete()));
            menu->addAction(action);
        }

        menu->addSeparator();

        ret = ret && makeAction(action,menu,"查找(&F)...",Qt::CTRL + Qt::Key_F);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),this,SLOT(onEditFind()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"替换(&R)...",Qt::CTRL + Qt::Key_H);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),this,SLOT(onEditReplace()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"定位(&G)...",Qt::CTRL + Qt::Key_G);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),this,SLOT(onEditGoto()));
            menu->addAction(action);
        }

        menu->addSeparator();

        ret = ret && makeAction(action,menu,"全选(&A)",Qt::CTRL + Qt::Key_A);
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
** 函数名: initFormatMenu(QMenuBar* mb)
** 输　入: QMenuBar* mb : 菜单栏指针
** 输　出: 无
** 返回值: 无
** 功能描述: 初始化格式下拉菜单组
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
bool MainWindow::initFormatMenu(QMenuBar* mb)
{
    QMenu* menu = new QMenu("格式(&O)",mb);
    bool ret = (menu != NULL);

    if(ret)
    {
        QAction* action = NULL;

        ret = ret && makeAction(action,menu,"自动换行(&W)",0);
        if(ret)
        {
            action->setCheckable(true);
            action->setChecked(true);
            connect(action,SIGNAL(triggered()),this,SLOT(onFormatWrap()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"字体(&F)...",0);
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
** 函数名: initViewMenu(QMenuBar* mb)
** 输　入: QMenuBar* mb : 菜单栏指针
** 输　出: 无
** 返回值: 无
** 功能描述: 初始化查看下拉菜单组
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
bool MainWindow::initViewMenu(QMenuBar* mb)
{
    QMenu* menu = new QMenu("查看(&V)",mb);
    bool ret = (menu != NULL);

    if(ret)
    {
        QAction* action = NULL;

        ret = ret && makeAction(action,menu,"工具栏(&T)",0);
        if(ret)
        {
            action->setCheckable(true);
            action->setChecked(true);
            connect(action,SIGNAL(triggered()),this,SLOT(onViewToolBar()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"状态栏(&S)",0);
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
** 函数名: initHelpMenu(QMenuBar* mb)
** 输　入: QMenuBar* mb : 菜单栏指针
** 输　出: 无
** 返回值: 无
** 功能描述: 初始化帮助下拉菜单组
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
bool MainWindow::initHelpMenu(QMenuBar* mb)
{
    QMenu* menu = new QMenu("帮助(&H)",mb);
    bool ret = (menu != NULL);

    if(ret)
    {
        QAction* action = NULL;

        ret = ret && makeAction(action,menu,"学院官网",0);
        if(ret)
        {
            connect(action,SIGNAL(triggered()),this,SLOT(onHelpManual()));
            menu->addAction(action);
        }

        ret = ret && makeAction(action,menu,"关于多功能文本编辑器...",0);
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
** 函数名: initFileToolItem(QToolBar* tb)
** 输　入: QToolBar* mb : 工具栏指针
** 输　出: 无
** 返回值: 无
** 功能描述: 初始化文件工具栏
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
bool MainWindow::initFileToolItem(QToolBar* tb)
{
    bool ret = true;
    QAction* action = NULL;

    ret = ret && makeAction(action,tb,"新建",":/Res/pic/new.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(onFileNew()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"打开",":/Res/pic/open.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(onFileOpen()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"保存",":Res/pic/save.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(onFileSave()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"另存为",":Res/pic/saveas.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(onFileSaveAs()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"打印",":Res/pic/print.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(onFilePrint()));
        tb->addAction(action);
    }

    return ret;
}

/*****************************************************************
** 函数名: initEditToolItem(QToolBar* tb)
** 输　入: QToolBar* mb : 工具栏指针
** 输　出: 无
** 返回值: 无
** 功能描述: 初始化编辑工具栏
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
bool MainWindow::initEditToolItem(QToolBar* tb)
{
    bool ret = true;
    QAction* action = NULL;

    ret = ret && makeAction(action,tb,"撤销",":/Res/pic/undo.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),centerWidget->getMainEditor(),SLOT(undo()));
        action->setEnabled(false);
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"恢复",":/Res/pic/redo.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),centerWidget->getMainEditor(),SLOT(redo()));
        action->setEnabled(false);
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"剪切",":/Res/pic/cut.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),centerWidget->getMainEditor(),SLOT(cut()));
        action->setEnabled(false);
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"复制",":/Res/pic/copy.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),centerWidget->getMainEditor(),SLOT(copy()));
        action->setEnabled(false);
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"粘贴",":/Res/pic/paste.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),centerWidget->getMainEditor(),SLOT(paste()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"查找",":/Res/pic/find.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(onEditFind()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"替换",":/Res/pic/replace.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(onEditReplace()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"定位",":/Res/pic/goto.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(onEditGoto()));
        tb->addAction(action);
    }

    return ret;
}

/*****************************************************************
** 函数名: initFormatToolItem(QToolBar* tb)
** 输　入: QToolBar* mb : 工具栏指针
** 输　出: 无
** 返回值: 无
** 功能描述: 初始化格式工具栏
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
bool MainWindow::initFormatToolItem(QToolBar* tb)
{
    bool ret = true;
    QAction* action = NULL;

    ret = ret && makeAction(action,tb,"自动换行",":/Res/pic/wrap.png");
    if(ret)
    {
        action->setCheckable(true);
        action->setChecked(true);
        connect(action,SIGNAL(triggered()),this,SLOT(onFormatWrap()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"字体",":/Res/pic/font.png");
    if(ret)
    {
        connect(action,SIGNAL(triggered()),this,SLOT(onFormatFont()));
        tb->addAction(action);
    }

    return ret;
}

/*****************************************************************
** 函数名: initViewToolItem(QToolBar* tb)
** 输　入: QToolBar* mb : 工具栏指针
** 输　出: 无
** 返回值: 无
** 功能描述: 初始化查看工具栏
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
bool MainWindow::initViewToolItem(QToolBar* tb)
{
    bool ret = true;
    QAction* action = NULL;

    ret = ret && makeAction(action,tb,"工具栏",":/Res/pic/tool.png");
    if(ret)
    {
        action->setCheckable(true);
        action->setChecked(true);
        connect(action,SIGNAL(triggered()),this,SLOT(onViewToolBar()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action,tb,"状态栏",":/Res/pic/status.png");
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
** 函数名: initFunctionToolItem(QToolBar* tb);
** 输　入: QToolBar* mb : 工具栏指针
** 输　出: 无
** 返回值: 无
** 功能描述: 初始化多功能选择工具栏
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
bool MainWindow::initFunctionToolItem(QToolBar* tb)
{
    bool ret = true;
    QAction* action = NULL;

    ret = ret && makeAction(action, tb, "计算器", ":/Res/pic/calculator.jpg");
    if(ret)
    {
        action->setCheckable(true);
        action->setChecked(false);
        connect(action,SIGNAL(triggered()),this,SLOT(onCalcFunc()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action, tb, "画图板", ":/Res/pic/drawing.bmp");
    if(ret)
    {
        action->setCheckable(true);
        action->setChecked(false);
        connect(action,SIGNAL(triggered()),this,SLOT(onDrawFunc()));
        tb->addAction(action);
    }

    ret = ret && makeAction(action, tb, "串口通信", ":/Res/pic/port.png");
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
** 函数名: makeAction(QAction*& action,QWidget* parent,QString text,int key)
** 输　入: QAction*& action :  待生成的菜单项指针
          QWidget* parent  :  生成菜单项的父类对象（该菜单项所在的下拉菜单组）
          QString text     :  显示文本
          int key          :  快捷键
** 输　出: 无
** 返回值: 无
** 功能描述: 生成菜单项
** 作　者:
** 日　期:
** 说　明:
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
** 函数名: makeAction(QAction*& action,QWidget* parent,QString text,QString icon)
** 输　入: QAction*& action :  待生成的快捷项指针
          QWidget* parent  :  生成快捷项的父类对象（该快捷项所在的工具栏）
          QString text     :  显示文本
          int key          :  图标
** 输　出: 无
** 返回值: 无
** 功能描述: 生成快捷项
** 作　者:
** 日　期:
** 说　明:
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
** 函数名: toolBar()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述: 返回工具栏指针
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
QToolBar* MainWindow::toolBar()
{
    QToolBar* ret = NULL;
    const QObjectList& list = children();

    /*遍历MainWindow的子类*/
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
** 函数名: ~MainWindow()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述: 析构函数
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
MainWindow::~MainWindow()
{

}
