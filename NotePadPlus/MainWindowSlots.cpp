/***********************************************************************************
 * �ļ��� : MainWindowSlots.cpp
 * ������ :
 * �������� :
 * �ļ����� : �๦���ı��༭����زۺ���
 * ��Ȩ˵�� :
 * ����˵�� :
 * �޸���־ :
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
** ������: ShowErrorMessage(QString message)
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ��ʾ����Ի���
** ������:
** �ա���:
** ˵����:
******************************************************************/
void MainWindow::ShowErrorMessage(QString message)
{
    QMessageBox msg(this);

    msg.setWindowTitle("����");
    msg.setText(message);
    msg.setIcon(QMessageBox::Critical);
    msg.setStandardButtons(QMessageBox::Ok);

    msg.exec();
}

/*****************************************************************
** ������: showQueryMessage(QString message)
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ��ʾ��ʾ�Ի���
** ������:
** �ա���:
** ˵����:
******************************************************************/
int MainWindow::showQueryMessage(QString message)
{
    QMessageBox msg(this);

    msg.setWindowTitle("��ʾ");
    msg.setText(message);
    msg.setIcon(QMessageBox::Question);
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    return msg.exec();
}

/*****************************************************************
** ������: showFileDialog(QFileDialog::AcceptMode mode,QString title)
** �䡡��: QFileDialog::AcceptMode mode �ļ��Ի����ģʽ
          QString title �Ի������
** �䡡��: ��
** ����ֵ: ��
** ��������: ��ʾ��ʾ�Ի���
** ������:
** �ա���:
** ˵����:
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
** ������: preEditorChange()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ѯ���Ƿ񽫸��ı��浽�ļ��У�������ѡ������Ӧ�Ĵ���
** ������:
** �ա���:
** ˵����:
******************************************************************/
void MainWindow::preEditorChange()
{
    if(m_isTextChanged)
    {
        int r = showQueryMessage("�Ƿ񽫸��ı��浽�ļ���?");

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
** ������: onFileNew()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������: �½��ļ��ۺ���
** ������:
** �ա���:
** ˵����:
******************************************************************/
void MainWindow::onFileNew()
{
    preEditorChange();

    if(!m_isTextChanged)
    {
        centerWidget->getMainEditor()->clear();

        setWindowTitle("�๦���ı��༭�� - [ New ]");

        m_filePath = "";

        m_isTextChanged = false;
    }
}

/*****************************************************************
** ������: openFileToEditor(QString path)
** �䡡��: QString path
** �䡡��: ��
** ����ֵ: ��
** ��������: ��ָ��·�����ļ������ļ�����ȫ��������ʾ���ı��༭�����
** ������:
** �ա���:
** ˵����:
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

            setWindowTitle("�๦���ı��༭�� - [ " + m_filePath + " ]");
        }
        else
        {
            ShowErrorMessage(QString("���ļ�ʧ��! \n\n") + "\"" + path + "\"");
        }
    }
}

/*****************************************************************
** ������: onFileOpen()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ���ļ��ۺ���
** ������:
** �ա���:
** ˵����:
******************************************************************/
void MainWindow::onFileOpen()
{
    preEditorChange();

    if(!m_isTextChanged)
    {
        QString path = showFileDialog(QFileDialog::AcceptOpen, "��");

        openFileToEditor(path);
    }
}

/*****************************************************************
** ������: openFile(QString path)
** �䡡��: QString path : �ļ�·��
** �䡡��: ��
** ����ֵ: ��
** ��������: ��ָ��·�����ļ�
** ������:
** �ա���:
** ˵����:
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
** ������: saveCurrentData(QString path)
** �䡡��: QString path : �ļ�·��
** �䡡��: ��
** ����ֵ: ��
** ��������: �����ı���ָ����
** ������:
** �ա���:
** ˵����:
******************************************************************/
QString MainWindow::saveCurrentData(QString path)
{
    QString ret = path;

    if(ret == "")
    {
        ret = showFileDialog(QFileDialog::AcceptSave,"����");
    }

    if(ret != "")
    {
        QFile file(ret);

        if( file.open(QIODevice::WriteOnly | QIODevice::Text) )
        {
            QTextStream out(&file);

            out << centerWidget->getMainEditor()->toPlainText();

            file.close();

            setWindowTitle("�๦���ı��༭�� - [ " + ret + " ]");

            m_isTextChanged = false;
        }
        else
        {
            ShowErrorMessage(QString("�����ļ�ʧ��! \n\n") + "\"" + ret + "\"");

            ret = "";
        }
    }

    return ret;
}

/*****************************************************************
** ������: onFileSave()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������: �����ı��ۺ���
** ������:
** �ա���:
** ˵����:
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
** ������: onFileSave()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ���Ϊ�ۺ���
** ������:
** �ա���:
** ˵����: ע����onFileSave() ���ļ�����ۺ��������𣬡����Ϊ���Ĳ���Ĭ��Ϊ����
          �����ļ��У�����ڵ���saveCurrentDataʱ��ָ��·��
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
** ������: onTextChanged()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������: ��Ӧ�ı��༭��������仯
** ������:
** �ա���:
** ˵����:
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
** ������: closeEvent(QCloseEvent* e)
** �䡡��: QCloseEvent* e : �ر��¼�
** �䡡��: ��
** ����ֵ: ��
** ��������: �ر��¼�������
** ������:
** �ա���:
** ˵����: �ر�֮ǰ����Ƿ񱣴�,������ǰ�����ñ��浽�����ļ���
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
** ������: dragEnterEvent(QDragEnterEvent* e)
** �䡡��: QDragEnterEvent* e : �����¼�
** �䡡��: ��
** ����ֵ: ��
** ��������: �����¼�������
** ������:
** �ա���:
** ˵����:
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
** ������: dropEvent(QDropEvent* e)
** �䡡��: QDropEvent* e ������֮��ġ����¡��¼�
** �䡡��: ��
** ����ֵ: ��
** ��������: ����֮��ġ����¡��¼�������
** ������:
** �ա���:
** ˵����:
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
            ShowErrorMessage("�޷����ļ���!");
        }
    }
    else
    {
        e->ignore();
    }
}

/*****************************************************************
** ������: onCopyAvailable(bool available)
** �䡡��: bool available
            true : �����ƺͼ��в���
            false : �������ƺͼ��в���
** �䡡��: ��
** ����ֵ: ��
** ��������: ����֮��ġ����¡��¼�������
** ������:
** �ա���:
** ˵����:
******************************************************************/
void MainWindow::onCopyAvailable(bool available)
{
    findMenuBarAction("����")->setEnabled(available);
    findMenuBarAction("����")->setEnabled(available);
    findToolBarAction("����")->setEnabled(available);
    findToolBarAction("����")->setEnabled(available);
}

/*****************************************************************
** ������: onRedoAvailable(bool available)
** �䡡��: bool available
            true : ����ָ�����
            false : ������ָ�����
** �䡡��: ��
** ����ֵ: ��
** ��������:
** ������:
** �ա���:
** ˵����:
******************************************************************/
void MainWindow::onRedoAvailable(bool available)
{
    findMenuBarAction("�ָ�")->setEnabled(available);
    findToolBarAction("�ָ�")->setEnabled(available);
}

/*****************************************************************
** ������: onUndoAvailable(bool available)
** �䡡��: bool available
            true : ����������
            false : ������������
** �䡡��: ��
** ����ֵ: ��
** ��������:
** ������:
** �ա���:
** ˵����:
******************************************************************/
void MainWindow::onUndoAvailable(bool available)
{
    findMenuBarAction("����")->setEnabled(available);
    findToolBarAction("����")->setEnabled(available);
}

/*****************************************************************
** ������: findMenuBarAction(QString text)
** �䡡��: QString text : �˵����ı�
** �䡡��: ��
** ����ֵ: ��
** ��������:���ݲ˵����ı����ؿ����ָ��
** ������:
** �ա���:
** ˵����:
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
** ������: findToolBarAction(QString text)
** �䡡��: QString text : ������ı��������ͣ���ڿ����ʱ����ʾ���ı���
** �䡡��: ��
** ����ֵ: ��
** ��������:���ݿ�����ı����ؿ����ָ��
** ������:
** �ա���:
** ˵����:
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
** ������: onFilePrint()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:�ı���ӡ�ۺ���
** ������:
** �ա���:
** ˵����:
******************************************************************/
void MainWindow::onFilePrint()
{
    QPrintDialog dlg(this);

    dlg.setWindowTitle("��ӡ");

    if( dlg.exec() == QPrintDialog::Accepted )
    {
        QPrinter* p = dlg.printer();

        centerWidget->getMainEditor()->document()->print(p);
    }
}

/*****************************************************************
** ������: onCursorPositionChanged()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:�ı��༭�����ı�ۺ���
** ������:
** �ա���:
** ˵����:
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

    statusLbl.setText("�� : " + QString::number(ln) + "    " + "�� : " + QString::number(col));
}

/*****************************************************************
** ������: onEditDelete()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:����ɾ���¼�
** ������:
** �ա���:
** ˵����:ɾ���¼���ʵ�Ǽ��̰����¼�
******************************************************************/
void MainWindow::onEditDelete()
{
    QKeyEvent keyPress(QEvent::KeyPress,Qt::Key_Delete,Qt::NoModifier);
    QKeyEvent keyRelease(QEvent::KeyPress,Qt::Key_Delete,Qt::NoModifier);

    QApplication::sendEvent(centerWidget->getMainEditor(),&keyPress);
    QApplication::sendEvent(centerWidget->getMainEditor(),&keyRelease);
}

/*****************************************************************
** ������: onEditFind()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:��ʾ���ҶԻ���
** ������:
** �ա���:
** ˵����:
******************************************************************/
void MainWindow::onEditFind()
{
    m_pFindDlg->show();
}

/*****************************************************************
** ������: onEditReplace()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:��ʾ�滻�Ի���
** ������:
** �ա���:
** ˵����:
******************************************************************/
void MainWindow::onEditReplace()
{
    m_pReplaceDlg->show();
}

/*****************************************************************
** ������: onEditGoto()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:��ʾ��λ���Ի���
** ������:
** �ա���:
** ˵����:
******************************************************************/
void MainWindow::onEditGoto()
{
    bool ok = false;

    int ln = QInputDialog::getInt(this, "��λ", "��: ", 1, 1, centerWidget->getMainEditor()->document()->lineCount(), 1, &ok, Qt::WindowCloseButtonHint | Qt::Drawer);

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
** ������: onViewToolBar()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:ת������������״̬
** ������:
** �ա���:
** ˵����:
******************************************************************/
void MainWindow::onViewToolBar()
{
    QToolBar* tb = toolBar();
    bool visible = tb->isVisible();

    tb->setVisible(!visible);

    findMenuBarAction("������")->setChecked(!visible);
    findToolBarAction("������")->setChecked(!visible);
}

/*****************************************************************
** ������: onViewStatusBar()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:ת��״̬������״̬
** ������:
** �ա���:
** ˵����:
******************************************************************/
void MainWindow::onViewStatusBar()
{
    QStatusBar* sb = statusBar();
    bool visible = sb->isVisible();

    sb->setVisible(!visible);

    findMenuBarAction("״̬��")->setChecked(!visible);
    findToolBarAction("״̬��")->setChecked(!visible);
}

/*****************************************************************
** ������: onFormatWrap()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:ת���Ƿ������Զ�����״̬
** ������:
** �ա���:
** ˵����:
******************************************************************/
void MainWindow::onFormatWrap()
{
    QPlainTextEdit::LineWrapMode mode = centerWidget->getMainEditor()->lineWrapMode();

    if(mode == QPlainTextEdit::NoWrap)
    {
        centerWidget->getMainEditor()->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        findMenuBarAction("�Զ�����")->setChecked(true);
        findToolBarAction("�Զ�����")->setChecked(true);
    }
    else
    {
        centerWidget->getMainEditor()->setLineWrapMode(QPlainTextEdit::NoWrap);
        findMenuBarAction("�Զ�����")->setChecked(false);
        findToolBarAction("�Զ�����")->setChecked(false);
    }
}

/*****************************************************************
** ������: onFormatFont()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:��ʾ����Ի���
** ������:
** �ա���:
** ˵����:
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
** ������: onFileExit()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:�ļ��˳��ۺ���
** ������:
** �ա���:
** ˵����:
******************************************************************/
void MainWindow::onFileExit()
{
    close();
}

/*****************************************************************
** ������: onHelpManual()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:��ѧԺ����
** ������:
** �ա���:
** ˵����:
******************************************************************/
void MainWindow::onHelpManual()
{
    QDesktopServices::openUrl(QUrl("https://www.cict.com/portal/list/index/cid/27.html#resource_4"));
}

/*****************************************************************
** ������: onHelpAbout()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:�򿪹��ڶԻ���
** ������:
** �ա���:
** ˵����:
******************************************************************/
void MainWindow::onHelpAbout()
{
    AboutDialog(this).exec();
}

/*****************************************************************
** ������: onCalcFunc()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:��ǰģʽ�л����ı���� + �����������л��ؽ��ı����ģʽ
** ������:
** �ա���:
** ˵����:�������º��Ѿ���isChecked״̬
******************************************************************/
void MainWindow::onCalcFunc()
{
    if( findToolBarAction("������")->isChecked() )/*�л����ı���� + ������ģʽ*/
    {
        centerWidget->transMode(CalculatorMode);
        findToolBarAction("��ͼ��")->setChecked(false);
        findToolBarAction("����ͨ��")->setChecked(false);
    }
    else/*�л��ؽ��ı����ģʽ*/
    {
        centerWidget->transMode(TextEditOnlyMode);
    }
}

/*****************************************************************
** ������: onDrawFunc()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:��ǰģʽ�л����ı���� + ��ͼ������л��ؽ��ı����ģʽ
** ������:
** �ա���:
** ˵����:�������º��Ѿ���isChecked״̬
******************************************************************/
void MainWindow::onDrawFunc()
{
    if( findToolBarAction("��ͼ��")->isChecked() )/*�л����ı���� + ��ͼ��ģʽ*/
    {
        centerWidget->transMode(DrawingBoardMode);
        findToolBarAction("������")->setChecked(false);
        findToolBarAction("����ͨ��")->setChecked(false);
    }
    else/*�л��ؽ��ı����ģʽ*/
    {
        centerWidget->transMode(TextEditOnlyMode);
    }
}

/*****************************************************************
** ������: onPortFunc()
** �䡡��: ��
** �䡡��: ��
** ����ֵ: ��
** ��������:��ǰģʽ�л����ı���� + ����ͨ�Ż����л��ؽ��ı����ģʽ
** ������:
** �ա���:
** ˵����:�������º��Ѿ���isChecked״̬
******************************************************************/
void MainWindow::onPortFunc()
{
    if( findToolBarAction("����ͨ��")->isChecked() )/*�л����ı���� + ����ͨ��ģʽ*/
    {
        centerWidget->transMode(SerialPortMode);
        findToolBarAction("������")->setChecked(false);
        findToolBarAction("��ͼ��")->setChecked(false);
    }
    else/*�л��ؽ��ı����ģʽ*/
    {
        centerWidget->transMode(TextEditOnlyMode);
    }
}

