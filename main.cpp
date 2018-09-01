#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Settings *setting=Settings::S();
    MainWindow w;
    setting->MW=&w;
    w.show();
    a.setWindowIcon(QIcon(Settings::get("app/image")));

    return a.exec();
}
