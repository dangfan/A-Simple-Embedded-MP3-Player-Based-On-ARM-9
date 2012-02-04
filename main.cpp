#include <QtGui/QApplication>
#include <QTextCodec>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
