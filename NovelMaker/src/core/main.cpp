#include "src/utilitis/config/configmanager.h"
#include "src/windows/mainwindow.h"
#include "logger.h"

#include <QApplication>

#include "src/utilitis/config/configsystem.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Logger::installQtMessageHandler();
    Logger::instance().initialize(LOG_DIR, LogLevel::Debug);

    ConfigeManager::instance().initialize();

    QString titleName = QString("%1 v%2").arg(ConfigSystem::instance().m_application.m_displayName).arg(ConfigSystem::instance().m_application.m_version);

    a.setApplicationName(titleName);

    MainWindow w;
    w.setWindowTitle(titleName);
    w.show();

    return a.exec();
}
