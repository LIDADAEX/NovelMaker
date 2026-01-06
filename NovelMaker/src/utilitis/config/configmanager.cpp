#include "configmanager.h"

#include "configsystem.h"
#include "configuser.h"

bool ConfigeManager::initialize()
{
    ConfigSystem::instance().initialize(CONFIG_DIR, CONFIG_SYSTEM_FILENAME);
    if(!ConfigSystem::instance().lordFile()) return false;

    ConfigUser::instance().initialize(ConfigSystem::instance().m_paths.m_configDir, ConfigSystem::instance().m_paths.m_configUserFileName);
    if(!ConfigUser::instance().lordFile()) return false;
    return true;
}

bool ConfigeManager::initializeProject(QString projectDir, QString projectName)
{
    m_configPoject.initialize(projectDir, projectName);
    if(!m_configPoject.lordFile()) return false;

    m_configWorkspace.initialize(projectDir, ConfigSystem::instance().m_paths.m_configWorkspaceName);
    if(!m_configWorkspace.lordFile()) return false;
    return true;
}
