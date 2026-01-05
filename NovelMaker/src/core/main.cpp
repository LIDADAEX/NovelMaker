#include "src/utilitis/config/configsystem.h"
#include "src/utilitis/config/configuser.h"
#include "src/windows/mainwindow.h"

#include "logger.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ConfigSystem::instance().initialize();
    ConfigSystem::instance().lordFile();


    Logger::installQtMessageHandler();
    Logger::instance().initialize(ConfigSystem::instance().m_paths.m_logDir, LogLevel::Debug);

    ConfigUser::instance().initialize();
    ConfigUser::instance().lordFile();

    MainWindow w;
    w.show();

    return a.exec();
}
