#include "configmanager.h"

#include "configsystem.h"
#include "configuser.h"
#include "src/core/logger.h"

ConfigeManager &ConfigeManager::instance()
{
    static ConfigeManager instance;
    return instance;
}

bool ConfigeManager::initialize()
{
    if(ConfigSystem::instance().isInitialize())
    {
        ConfigSystem::instance().unInitialize();
    }
    ConfigSystem::instance().initialize(CONFIG_DIR, CONFIG_SYSTEM_FILENAME);
    if(!ConfigSystem::instance().loadFile())
    {
        LOG_WARNING("主系统配置错误请检查");
        return false;
    }
    LOG_INFO("主系统配置运行正常");

    if(ConfigSystem::instance().m_paths.m_configDir != CONFIG_DIR)
    {
        LOG_INFO("发现次系统配置");
        ConfigSystem::instance().unInitialize();
        ConfigSystem::instance().initialize(ConfigSystem::instance().m_paths.m_configDir, ConfigSystem::instance().m_paths.m_configSystemFileName);
        if(!ConfigSystem::instance().loadFile())
        {
            LOG_WARNING("次系统配置错误请检查,返回主系统配置");
            ConfigSystem::instance().unInitialize();
            ConfigSystem::instance().initialize(CONFIG_DIR, CONFIG_SYSTEM_FILENAME);
            ConfigSystem::instance().loadFile();
        }
        LOG_INFO("切换至次系统配置");
    }

    if(ConfigUser::instance().isInitialize())
    {
        ConfigUser::instance().unInitialize();
    }
    ConfigUser::instance().initialize(ConfigSystem::instance().m_paths.m_configDir, ConfigSystem::instance().m_paths.m_configUserFileName);
    if(!ConfigUser::instance().loadFile()) return false;
    return true;
}

qint16 ConfigeManager::initializeProject(QString projectDir, QString projectName)
{
    ConfigProject configPoject;
    configPoject.initialize(projectDir, projectName);
    if(!configPoject.loadFile()) return INITIALIZE_PROJECT_ERROR;
    m_configPojectList.append(configPoject);

    ConfigWorkspace configWorkspace;
    configWorkspace.initialize(projectDir, ConfigSystem::instance().m_paths.m_configWorkspaceName);
    if(!configWorkspace.loadFile())
    {
        m_configPojectList.removeLast();
        return INITIALIZE_PROJECT_ERROR;
    }
    m_configWorkspaceList.append(configWorkspace);
    m_projectNumber++;
    return m_projectNumber - 1;
}

bool ConfigeManager::closeProject(quint16 projectNumber)
{
    if(projectNumber >= m_projectNumber) return false;
    m_configPojectList.removeAt(projectNumber);
    m_configWorkspaceList.removeAt(projectNumber);
    return true;
}

bool ConfigeManager::getConfig(quint16 projectNumber, ConfigProject *configProject, ConfigWorkspace *configWorkspace)
{
    if(projectNumber >= m_projectNumber) return false;
    configProject = &m_configPojectList[projectNumber];
    configWorkspace = &m_configWorkspaceList[projectNumber];
    return true;
}
