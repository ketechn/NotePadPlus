/***********************************************************************************
 * 文件名 : MainWindowSlots.cpp
 * 负责人 :
 * 创建日期 :
 * 文件描述 : 多功能文本编辑器相关槽函数
 * 版权说明 :
 * 其它说明 :
 * 修改日志 :
***********************************************************************************/
#include "MainWindow.h"
#include "AboutDialog.h"
#include "AppConfig.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QMap>
#include <QCloseEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QList>
#include <QUrl>
#include <QFileInfo>
#include <QObjectList>
#include <QMenu>
#include <QToolBar>
#include <QPrintDialog>
#include <QInputDialog>
#include <QFontDialog>
#include <QKeyEvent>
#include <QApplication>
#include <QStatusBar>
#include <QDesktopServices>
#include <QDebug>

/*****************************************************************
** 函数名: ShowErrorMessage(QString message)
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述: 显示错误对话框
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::ShowErrorMessage(QString message)
{
    QMessageBox msg(this);

    msg.setWindowTitle("错误");
    msg.setText(message);
    msg.setIcon(QMessageBox::Critical);
    msg.setStandardButtons(QMessageBox::Ok);

    msg.exec();
}

/*****************************************************************
** 函数名: showQueryMessage(QString message)
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述: 显示提示对话框
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
int MainWindow::showQueryMessage(QString message)
{
    QMessageBox msg(this);

    msg.setWindowTitle("提示");
    msg.setText(message);
    msg.setIcon(QMessageBox::Question);
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    return msg.exec();
}

/*****************************************************************
** 函数名: showFileDialog(QFileDialog::AcceptMode mode,QString title)
** 输　入: QFileDialog::AcceptMode mode 文件对话框打开模式
          QString title 对话框标题
** 输　出: 无
** 返回值: 无
** 功能描述: 显示提示对话框
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
QString MainWindow::showFileDialog(QFileDialog::AcceptMode mode, QString title)
{
    QString ret = "";
    QFileDialog fd(this);
    QStringList filters;
    QMap<QString,QString> map;

    const char* filterArray[][2] =
    {
        {"Text Files (*.txt)" , ".txt"},
        {"All Files (*.*)"    , "*"},
        {NULL,                  NULL}
    };

    for(int i = 0; filterArray[i][0] != NULL; i++)
    {
        filters.append(filterArray[i][0]);
        map.insert(filterArray[i][0], filterArray[i][1]);
    }

    fd.setWindowTitle(title);
    fd.setAcceptMode(mode);
    fd.setFilters(filters);

    if(mode == QFileDialog::AcceptOpen)
    {
        fd.setFileMode(QFileDialog::ExistingFile);
    }

    if(fd.exec() == QFileDialog::Accepted)
    {
        ret = fd.selectedFiles()[0];

        if(mode == QFileDialog::AcceptSave)
        {
            QString postfix = map[fd.selectedFilter()];

            if( (postfix != "*") && !ret.endsWith(postfix) )
            {
                ret = ret + postfix;
            }
        }
    }

    return ret;
}

/*****************************************************************
** 函数名: preEditorChange()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述: 询问是否将更改保存到文件中，并根据选择做相应的处理
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::preEditorChange()
{
    if(m_isTextChanged)
    {
        int r = showQueryMessage("是否将更改保存到文件中?");

        switch(r)
        {
            case QMessageBox::Yes:
                saveCurrentData(m_filePath);
                break;
            case QMessageBox::No:
                m_isTextChanged = false;
                break;
            case QMessageBox::Cancel:
                break;
        }
    }
}

/*****************************************************************
** 函数名: onFileNew()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述: 新建文件槽函数
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::onFileNew()
{
    preEditorChange();

    if(!m_isTextChanged)
    {
        centerWidget->getMainEditor()->clear();

        setWindowTitle("多功能文本编辑器 - [ New ]");

        m_filePath = "";

        m_isTextChanged = false;
    }
}

/*****************************************************************
** 函数名: openFileToEditor(QString path)
** 输　入: QString path
** 输　出: 无
** 返回值: 无
** 功能描述: 打开指定路径的文件，将文件数据全部读出显示到文本编辑组件中
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::openFileToEditor(QString path)
{
    if(path != "")
    {
        QFile file(path);

        if( file.open(QIODevice::ReadOnly | QIODevice::Text) )
        {
            centerWidget->getMainEditor()->setPlainText(QString(file.readAll()));

            file.close();

            m_filePath = path;

            m_isTextChanged = false;

            setWindowTitle("多功能文本编辑器 - [ " + m_filePath + " ]");
        }
        else
        {
            ShowErrorMessage(QString("打开文件失败! \n\n") + "\"" + path + "\"");
        }
    }
}

/*****************************************************************
** 函数名: onFileOpen()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述: 打开文件槽函数
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::onFileOpen()
{
    preEditorChange();

    if(!m_isTextChanged)
    {
        QString path = showFileDialog(QFileDialog::AcceptOpen, "打开");

        openFileToEditor(path);
    }
}

/*****************************************************************
** 函数名: openFile(QString path)
** 输　入: QString path : 文件路径
** 输　出: 无
** 返回值: 无
** 功能描述: 打开指定路径的文件
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::openFile(QString path)
{
    preEditorChange();

    if(!m_isTextChanged)
    {
        openFileToEditor(path);
    }
}

/*****************************************************************
** 函数名: saveCurrentData(QString path)
** 输　入: QString path : 文件路径
** 输　出: 无
** 返回值: 无
** 功能描述: 保存文本到指定的
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
QString MainWindow::saveCurrentData(QString path)
{
    QString ret = path;

    if(ret == "")
    {
        ret = showFileDialog(QFileDialog::AcceptSave,"保存");
    }

    if(ret != "")
    {
        QFile file(ret);

        if( file.open(QIODevice::WriteOnly | QIODevice::Text) )
        {
            QTextStream out(&file);

            out << centerWidget->getMainEditor()->toPlainText();

            file.close();

            setWindowTitle("多功能文本编辑器 - [ " + ret + " ]");

            m_isTextChanged = false;
        }
        else
        {
            ShowErrorMessage(QString("保存文件失败! \n\n") + "\"" + ret + "\"");

            ret = "";
        }
    }

    return ret;
}

/*****************************************************************
** 函数名: onFileSave()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述: 保存文本槽函数
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::onFileSave()
{
    QString path = saveCurrentData(m_filePath);

    if(path != "")
    {
        m_filePath = path;
    }
}

/*****************************************************************
** 函数名: onFileSave()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述: 另存为槽函数
** 作　者:
** 日　期:
** 说　明: 注意与onFileSave() 即文件保存槽函数的区别，“另存为”的操作默认为保存
          到新文件中，因此在调用saveCurrentData时不指定路径
******************************************************************/
void MainWindow::onFileSaveAs()
{
    QString path = saveCurrentData();

    if(path != "")
    {
        m_filePath = path;
    }
}

/*****************************************************************
** 函数名: onTextChanged()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述: 响应文本编辑组件发生变化
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::onTextChanged()
{
    if(!m_isTextChanged)
    {
        setWindowTitle("*" + windowTitle());
    }

    m_isTextChanged = true;
}

/*****************************************************************
** 函数名: closeEvent(QCloseEvent* e)
** 输　入: QCloseEvent* e : 关闭事件
** 输　出: 无
** 返回值: 无
** 功能描述: 关闭事件处理函数
** 作　者:
** 日　期:
** 说　明: 关闭之前检查是否保存,并将当前的配置保存到配置文件中
******************************************************************/
void MainWindow::closeEvent(QCloseEvent* e)
{
   preEditorChange();

   if(!m_isTextChanged)
   {
       QFont font = centerWidget->getMainEditor()->font();
       bool isWrap = (centerWidget->getMainEditor()->lineWrapMode() == QPlainTextEdit::WidgetWidth);
       bool tbVisible = toolBar()->isVisible();
       bool sbVisible = statusBar()->isVisible();
       AppConfig config(font, pos(), size(), isWrap, tbVisible, sbVisible);

       config.store();

       QMainWindow::closeEvent(e);
   }
   else
   {
       e->ignore();
   }
}

/*****************************************************************
** 函数名: dragEnterEvent(QDragEnterEvent* e)
** 输　入: QDragEnterEvent* e : 拖入事件
** 输　出: 无
** 返回值: 无
** 功能描述: 拖入事件处理函数
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::dragEnterEvent(QDragEnterEvent* e)
{
    if( e->mimeData()->hasUrls() )
    {
        e->acceptProposedAction();
    }
    else
    {
        e->ignore();
    }
}

/*****************************************************************
** 函数名: dropEvent(QDropEvent* e)
** 输　入: QDropEvent* e ：拖入之后的“放下”事件
** 输　出: 无
** 返回值: 无
** 功能描述: 拖入之后的“放下”事件处理函数
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::dropEvent(QDropEvent* e)
{
    if( e->mimeData()->hasUrls() )
    {
        QList<QUrl> list = e->mimeData()->urls();
        QString path = list[0].toLocalFile();
        QFileInfo fi(path);

        if( fi.isFile() )
        {
            preEditorChange();

            if( !m_isTextChanged )
            {
                openFileToEditor(path);
            }
        }
        else
        {
            ShowErrorMessage("无法打开文件夹!");
        }
    }
    else
    {
        e->ignore();
    }
}

/*****************************************************************
** 函数名: onCopyAvailable(bool available)
** 输　入: bool available
            true : 允许复制和剪切操作
            false : 不允许复制和剪切操作
** 输　出: 无
** 返回值: 无
** 功能描述: 拖入之后的“放下”事件处理函数
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::onCopyAvailable(bool available)
{
    findMenuBarAction("复制")->setEnabled(available);
    findMenuBarAction("剪切")->setEnabled(available);
    findToolBarAction("复制")->setEnabled(available);
    findToolBarAction("剪切")->setEnabled(available);
}

/*****************************************************************
** 函数名: onRedoAvailable(bool available)
** 输　入: bool available
            true : 允许恢复操作
            false : 不允许恢复操作
** 输　出: 无
** 返回值: 无
** 功能描述:
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::onRedoAvailable(bool available)
{
    findMenuBarAction("恢复")->setEnabled(available);
    findToolBarAction("恢复")->setEnabled(available);
}

/*****************************************************************
** 函数名: onUndoAvailable(bool available)
** 输　入: bool available
            true : 允许撤销操作
            false : 不允许撤销操作
** 输　出: 无
** 返回值: 无
** 功能描述:
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::onUndoAvailable(bool available)
{
    findMenuBarAction("撤销")->setEnabled(available);
    findToolBarAction("撤销")->setEnabled(available);
}

/*****************************************************************
** 函数名: findMenuBarAction(QString text)
** 输　入: QString text : 菜单项文本
** 输　出: 无
** 返回值: 无
** 功能描述:根据菜单项文本返回快捷项指针
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
QAction* MainWindow::findMenuBarAction(QString text)
{
    QAction* ret = NULL;
    const QObjectList& list = menuBar()->children();

    for(int i = 0;i < list.count();i++)
    {
        QMenu* menu = dynamic_cast<QMenu*>(list[i]);

        if(menu != NULL)
        {
            QList<QAction*> actions = menu->actions();

            for(int j = 0;j < actions.count();j++)
            {
                if(actions[j]->text().startsWith(text))
                {
                    ret = actions[j];
                    break;
                }
            }
        }
    }

    return ret;
}

/*****************************************************************
** 函数名: findToolBarAction(QString text)
** 输　入: QString text : 快捷项文本（即鼠标停留于快捷项时所显示的文本）
** 输　出: 无
** 返回值: 无
** 功能描述:根据快捷项文本返回快捷项指针
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
QAction* MainWindow::findToolBarAction(QString text)
{
    QAction* ret = NULL;
    QList<QAction*> actions = toolBar()->actions();

    for(int i = 0;i < actions.count();i++)
    {
        if(actions[i]->toolTip().startsWith(text))
        {
            ret = actions[i];
            break;
        }
    }

    return ret;
}

/*****************************************************************
** 函数名: onFilePrint()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:文本打印槽函数
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::onFilePrint()
{
    QPrintDialog dlg(this);

    dlg.setWindowTitle("打印");

    if( dlg.exec() == QPrintDialog::Accepted )
    {
        QPrinter* p = dlg.printer();

        centerWidget->getMainEditor()->document()->print(p);
    }
}

/*****************************************************************
** 函数名: onCursorPositionChanged()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:文本编辑器光标改变槽函数
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::onCursorPositionChanged()
{
    int ln = 1;
    int col = 1;
    int pos = centerWidget->getMainEditor()->textCursor().position();
    QString text = centerWidget->getMainEditor()->toPlainText();

    for(int i = 0;i < pos;i++)
    {
        if(text[i] == '\n')
        {
            col = 1;
            ln++;
        }
        else
        {
            col++;
        }
    }

    statusLbl.setText("行 : " + QString::number(ln) + "    " + "列 : " + QString::number(col));
}

/*****************************************************************
** 函数名: onEditDelete()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:发射删除事件
** 作　者:
** 日　期:
** 说　明:删除事件其实是键盘按下事件
******************************************************************/
void MainWindow::onEditDelete()
{
    QKeyEvent keyPress(QEvent::KeyPress,Qt::Key_Delete,Qt::NoModifier);
    QKeyEvent keyRelease(QEvent::KeyPress,Qt::Key_Delete,Qt::NoModifier);

    QApplication::sendEvent(centerWidget->getMainEditor(),&keyPress);
    QApplication::sendEvent(centerWidget->getMainEditor(),&keyRelease);
}

/*****************************************************************
** 函数名: onEditFind()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:显示查找对话框
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::onEditFind()
{
    m_pFindDlg->show();
}

/*****************************************************************
** 函数名: onEditReplace()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:显示替换对话框
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::onEditReplace()
{
    m_pReplaceDlg->show();
}

/*****************************************************************
** 函数名: onEditGoto()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:显示定位到对话框
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::onEditGoto()
{
    bool ok = false;

    int ln = QInputDialog::getInt(this, "定位", "行: ", 1, 1, centerWidget->getMainEditor()->document()->lineCount(), 1, &ok, Qt::WindowCloseButtonHint | Qt::Drawer);

    if(ok)
    {
        QString text = centerWidget->getMainEditor()->toPlainText();
        QTextCursor c = centerWidget->getMainEditor()->textCursor();
        int next = -1;
        int pos = 0;

        for(int i = 0;i < ln;i++)
        {
            pos  = next + 1;
            next = text.indexOf('\n',pos);
        }

        c.setPosition(pos);

        centerWidget->getMainEditor()->setTextCursor(c);
    }
}

/*****************************************************************
** 函数名: onViewToolBar()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:转换工具栏可视状态
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::onViewToolBar()
{
    QToolBar* tb = toolBar();
    bool visible = tb->isVisible();

    tb->setVisible(!visible);

    findMenuBarAction("工具栏")->setChecked(!visible);
    findToolBarAction("工具栏")->setChecked(!visible);
}

/*****************************************************************
** 函数名: onViewStatusBar()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:转换状态栏可视状态
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::onViewStatusBar()
{
    QStatusBar* sb = statusBar();
    bool visible = sb->isVisible();

    sb->setVisible(!visible);

    findMenuBarAction("状态栏")->setChecked(!visible);
    findToolBarAction("状态栏")->setChecked(!visible);
}

/*****************************************************************
** 函数名: onFormatWrap()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:转换是否允许自动换行状态
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::onFormatWrap()
{
    QPlainTextEdit::LineWrapMode mode = centerWidget->getMainEditor()->lineWrapMode();

    if(mode == QPlainTextEdit::NoWrap)
    {
        centerWidget->getMainEditor()->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        findMenuBarAction("自动换行")->setChecked(true);
        findToolBarAction("自动换行")->setChecked(true);
    }
    else
    {
        centerWidget->getMainEditor()->setLineWrapMode(QPlainTextEdit::NoWrap);
        findMenuBarAction("自动换行")->setChecked(false);
        findToolBarAction("自动换行")->setChecked(false);
    }
}

/*****************************************************************
** 函数名: onFormatFont()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:显示字体对话框
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::onFormatFont()
{
    bool ok = false;

    QFont font = QFontDialog::getFont(&ok, centerWidget->getMainEditor()->font(), this);

    if(ok)
    {
        centerWidget->getMainEditor()->setFont(font);
    }
}

/*****************************************************************
** 函数名: onFileExit()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:文件退出槽函数
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::onFileExit()
{
    close();
}

/*****************************************************************
** 函数名: onHelpManual()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:打开学院官网
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::onHelpManual()
{
    QDesktopServices::openUrl(QUrl("https://www.cict.com/portal/list/index/cid/27.html#resource_4"));
}

/*****************************************************************
** 函数名: onHelpAbout()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:打开关于对话框
** 作　者:
** 日　期:
** 说　明:
******************************************************************/
void MainWindow::onHelpAbout()
{
    AboutDialog(this).exec();
}

/*****************************************************************
** 函数名: onCalcFunc()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:当前模式切换到文本组件 + 计算器或者切换回仅文本组件模式
** 作　者:
** 日　期:
** 说　明:当快捷项按下后已经是isChecked状态
******************************************************************/
void MainWindow::onCalcFunc()
{
    if( findToolBarAction("计算器")->isChecked() )/*切换到文本组件 + 计算器模式*/
    {
        centerWidget->transMode(CalculatorMode);
        findToolBarAction("画图板")->setChecked(false);
        findToolBarAction("串口通信")->setChecked(false);
    }
    else/*切换回仅文本组件模式*/
    {
        centerWidget->transMode(TextEditOnlyMode);
    }
}

/*****************************************************************
** 函数名: onDrawFunc()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:当前模式切换到文本组件 + 画图板或者切换回仅文本组件模式
** 作　者:
** 日　期:
** 说　明:当快捷项按下后已经是isChecked状态
******************************************************************/
void MainWindow::onDrawFunc()
{
    if( findToolBarAction("画图板")->isChecked() )/*切换到文本组件 + 画图板模式*/
    {
        centerWidget->transMode(DrawingBoardMode);
        findToolBarAction("计算器")->setChecked(false);
        findToolBarAction("串口通信")->setChecked(false);
    }
    else/*切换回仅文本组件模式*/
    {
        centerWidget->transMode(TextEditOnlyMode);
    }
}

/*****************************************************************
** 函数名: onPortFunc()
** 输　入: 无
** 输　出: 无
** 返回值: 无
** 功能描述:当前模式切换到文本组件 + 串口通信或者切换回仅文本组件模式
** 作　者:
** 日　期:
** 说　明:当快捷项按下后已经是isChecked状态
******************************************************************/
void MainWindow::onPortFunc()
{
    if( findToolBarAction("串口通信")->isChecked() )/*切换到文本组件 + 串口通信模式*/
    {
        centerWidget->transMode(SerialPortMode);
        findToolBarAction("计算器")->setChecked(false);
        findToolBarAction("画图板")->setChecked(false);
    }
    else/*切换回仅文本组件模式*/
    {
        centerWidget->transMode(TextEditOnlyMode);
    }
}

