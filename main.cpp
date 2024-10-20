#include "mainwindow.h"
#include <QApplication>
#include<QFile>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile qss("style/style.qss");
    //把qss读出来设到application里面 启动 MainWindow w 再运行
    if(qss.open(QFile::ReadOnly)){
        qDebug("Open success");
        QString style =QLatin1String(qss.readAll());
        a.setStyleSheet(style);
        qss.close();
    }else{
        qDebug("Open failed");
    }
    MainWindow w;
    w.show();
    return a.exec();
}

