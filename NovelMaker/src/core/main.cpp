#include "src/windows/mainwindow.h"

#include "logger.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Logger::installQtMessageHandler();
    Logger::instance().initialize("./res/logoutput");

    MainWindow w;
    w.show();

    return a.exec();
}
