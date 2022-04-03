/***********************************************************************************
 * �ļ��� : main.cpp
 * ������ :
 * �������� :
 * �ļ����� : ������
 * ��Ȩ˵�� :
 * ����˵�� :
 * �޸���־ :
***********************************************************************************/
#include <QtGui/QApplication>
#include <QFileInfo>
#include <QTextCodec>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    int ret = -1;
    QApplication a(argc, argv);

    /*�����������У�֧������*/
    QTextCodec::setCodecForTr(QTextCodec::codecForName(QTextCodec::codecForLocale()->name()));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName(QTextCodec::codecForLocale()->name()));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName(QTextCodec::codecForLocale()->name()));

    MainWindow* w = MainWindow::NewInstance();

    if(w != NULL)
    {
        if( argc > 1 )
        {
            QFileInfo fi(argv[1]);

            if( fi.exists() )
            {
                w->openFile(fi.absoluteFilePath());
            }
        }

        w->showMaximized();

        ret = a.exec();
    }

    delete w;

    return ret;
}
