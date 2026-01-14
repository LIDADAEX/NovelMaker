#include "configmanager.h"

#include "configsystem.h"
#include "configuser.h"
#include "src/core/logger.h"
#include "configproject.h"
#include "configworkspace.h"

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

bool ConfigeManager::initializeProject(QString projectDir, QString projectName)
{
    ConfigProject::instance().initialize(projectDir, projectName);
    if(!ConfigProject::instance().loadFile()) return false;

    ConfigWorkspace::instance().initialize(projectDir, ConfigSystem::instance().m_paths.m_configWorkspaceFileName);
    if(!ConfigWorkspace::instance().loadFile())return false;
    m_isOpenProject = true;
    return true;
}

void ConfigeManager::closeProject()
{
    m_isOpenProject = false;
    ConfigProject::instance().unInitialize();
    ConfigWorkspace::instance().unInitialize();
}


