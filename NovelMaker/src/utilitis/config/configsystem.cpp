#include "configsystem.h"
#include "./src/utilitis/file/fileutil.h"
#include "./src/core/logger.h"

ConfigSystem &ConfigSystem::instance()
{
    static ConfigSystem instance;
    return instance;
}

void ConfigSystem::initialize(const QString &logDir)
{
    if(!FileUtil::dirCreat(logDir))
    {
        LOG_WARNING("系统配置路径创建失败，请检查系统配置路径");
        return;
    }

    m_configFile.setFileName(logDir + '/' + CONFIG_SYSTEM_FILENAME);

    if(!m_configFile.exists())
    {
        LOG_INFO("系统配置文件缺失，正在创建系统配置文件");
        //此处应该有系统初始化内容。
    }

    m_isInitialize = true;
}

bool ConfigSystem::saveFile()
{
    if(!FileUtil::fileOpen(&m_configFile, QIODeviceBase::WriteOnly))
    {
        LOG_WARNING("无法打开系统配置文件，请检查文件是否存在或是否正在被占用");
        return false;
    }

    m_configFile.close();
    return true;
}

bool ConfigSystem::lordFile()
{
    if(!FileUtil::fileOpen(&m_configFile, QIODeviceBase::ReadOnly))
    {
        LOG_WARNING("无法打开系统配置文件，请检查文件是否存在或是否正在被占用");
        return false;
    }

    m_configFile.close();
    return true;
}
