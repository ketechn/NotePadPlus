/***********************************************************************************
 * 文件名 : main.cpp
 * 负责人 :
 * 创建日期 :
 * 文件描述 : 主程序
 * 版权说明 :
 * 其它说明 :
 * 修改日志 :
***********************************************************************************/
#include <QtGui/QApplication>
#include <QFileInfo>
#include <QTextCodec>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    int ret = -1;
    QApplication a(argc, argv);

    /*加入以下三行，支持中文*/
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
