#include "src/utilitis/config/configmanager.h"
#include "src/windows/mainwindow.h"
#include "logger.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Logger::installQtMessageHandler();
    Logger::instance().initialize(LOG_DIR, LogLevel::Debug);

    ConfigeManager::instance().initialize();

    MainWindow w;
    w.show();

    return a.exec();
}
