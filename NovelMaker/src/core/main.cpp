#include "src/utilitis/config/configsystem.h"
#include "src/utilitis/config/configuser.h"
#include "src/utilitis/config/configworkspace.h"
#include "src/windows/mainwindow.h"

#include "logger.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Logger::installQtMessageHandler();
    Logger::instance().initialize(LOG_DIR, LogLevel::Debug);

    ConfigSystem::instance().initialize(CONFIG_DIR, CONFIG_SYSTEM_FILENAME);
    ConfigSystem::instance().lordFile();    

    ConfigUser::instance().initialize(ConfigSystem::instance().m_paths.m_configDir, ConfigSystem::instance().m_paths.m_configUserFileName);
    ConfigUser::instance().lordFile();

    ConfigWorkspace configWorkspace;
    configWorkspace.initialize(ConfigSystem::instance().m_paths.m_configDir, ConfigSystem::instance().m_paths.m_configWorkspaceName);
    configWorkspace.lordFile();

    MainWindow w;
    w.show();

    return a.exec();
}
