#include "configbase.h"

#include "src/utilitis/config/configsystem.h"
#include "src/utilitis/file/fileutil.h"
#include "src/utilitis/file/jsonfileutil.h"
#include "src/core/logger.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

void ConfigBase::initialize(const QString &configDir, const QString &fileName)
{
    switch(m_configType)
    {
    case ConfigList::system:
        m_typeString = "系统";
        break;
    case ConfigList::project:
        m_typeString = "项目";
        break;
    case ConfigList::user:
        m_typeString = "用户";
        break;
    case ConfigList::workspace:
        m_typeString = "工作区";
        break;
    }

    // 通过m_isInitialize来，防止重复初始化
    if(m_isInitialize)
    {
        LOG_WARNING("重复初始化" + m_typeString + "配置文件");
        return;
    }

    m_configDir = configDir;
    m_fileName = fileName;

    // 检测文件夹路径是否存在，不存在则创建
    if(!FileUtil::dirCreat(configDir))
    {
        LOG_WARNING("配置路径创建失败，请检查" + m_typeString + "配置路径");
        return;
    }

    m_configFile.setFileName(configDir + '/' + fileName);

    // 将初始化标志提前的原因是，方便后续的如果文件不存在用来创建文件用的，因为saveFile函数需要初始化完成。
    m_isInitialize = true;

    // 判断系统配置文件是否存在
    if(!m_configFile.exists())
    {
        LOG_INFO("配置文件缺失，正在创建" + m_typeString + "配置文件");

        // 不存在则开始利用硬编码的默认值进行初始化，以下的宏定义的值都能在configdefine.h文件中找到。
        if(m_configType != ConfigList::system)
        {
            if(!ConfigSystem::instance().isInitialize())
            {
                LOG_INFO("系统配置文件未初始化，请先初始化系统配置文件");
                m_isInitialize = false;
                return;
            }
        }

        initialConfigData();
        //初始化结束

        /* 因为saveFile需要完成初始化之后才能调用，所以之前要令初始化完成。
         * 如果保存配置文件出错了，就会重新使得初始化完成为假。*/
        if(!saveFile())
        {
            m_isInitialize = false;
            LOG_WARNING("无法写入" + m_typeString + "配置文件，" + m_typeString + "配置初始化失败");
            return;
        }
    }

    LOG_INFO(m_typeString + "配置初始化完成");
}

bool ConfigBase::isInitialize()
{
    return m_isInitialize;
}

void ConfigBase::unInitialize()
{
    m_isInitialize = false;
}

bool ConfigBase::saveFile()
{
    // 通过m_isInitialize来，防止未初始化的保存
    if(!m_isInitialize)
    {
        LOG_WARNING("请完成初始化后再保存" + m_typeString + "配置文件");
        return false;
    }

    //从类中的数据构造json文件开始。
    QJsonDocument jsonDocument = constructJsonDocument();
    //从类中的数据构造json文件结束。

    //将json文件写入到配置文件中，利用JsonFileUtil的writeJsonDocument函数写入
    if(!JsonFileUtil::writeJsonDocument(m_configFile, jsonDocument))
    {
        LOG_WARNING(m_typeString + "配置文件保存失败");
        return false;
    }
    else
    {
        LOG_INFO( m_typeString + "配置文件保存成功");
        return true;
    }
    //将json文件写入结束。
}

bool ConfigBase::lordFile()
{
    // 通过m_isInitialize来，防止未初始化的保存
    if(!m_isInitialize)
    {
        LOG_WARNING("请完成初始化后再装载" + m_typeString + "配置文件");
        return false;
    }

    // 从文件中读取Json文件，readError是用来判断是否读取成功的。
    bool readError;
    QJsonDocument jsonDocument = JsonFileUtil::readJsonDocument(m_configFile, readError);
    if(readError)
    {
        LOG_WARNING(m_typeString + "配置文件装载失败");
        LOG_INFO(m_typeString + "配置重新初始化中");
        //如果读取失败，因为之前完成过初始化所以大概率是文件本身出问题了，考虑移除之后重新初始化。
        if(!FileUtil::removeFile(m_configFile))
        {
            LOG_WARNING(m_typeString + "配置移除失败");
        }
        else
        {
            m_isInitialize = false;
            initialize(m_configDir, m_fileName);
        }
        return false;
    }

    // 从Json文件中读取数据到类数据中开始
    constructConfigData(jsonDocument);
    // 从Json文件中读取数据结束

    LOG_INFO(m_typeString + "配置文件装载成功");
    return true;
}
