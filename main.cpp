#include <QApplication>
#include <QtCore/QTextCodec>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication mainActivity(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    return mainActivity.exec();
}
