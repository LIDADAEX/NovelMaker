#include "configworkspace.h"
#include "src/core/logger.h"
#include "src/utilitis/file/fileutil.h"
#include "src/utilitis/file/jsonfileutil.h"

#include <QJsonObject>

void ConfigWorkspace::initialize(QString configDir, QString fileName)
{
    // 通过m_isInitialize来，防止重复初始化
    if(m_isInitialize)
    {
        LOG_WARNING("重复初始化工作区配置文件");
        return;
    }

    m_configDir = configDir;
    m_fileName = fileName;

    // 检测文件夹路径是否存在，不存在则创建
    if(!FileUtil::dirCreat(configDir))
    {
        LOG_WARNING("工作区配置路径创建失败，请检查工作区配置路径");
        return;
    }

    m_configFile.setFileName(configDir + '/' + fileName);

    // 将初始化标志提前的原因是，方便后续的如果文件不存在用来创建文件用的，因为saveFile函数需要初始化完成。
    m_isInitialize = true;

    // 判断系统配置文件是否存在
    if(!m_configFile.exists())
    {
        LOG_INFO("工作区配置文件缺失，正在创建工作区配置文件");

        // 不存在则开始利用硬编码的默认值进行初始化，以下的宏定义的值都能在configdefine.h文件中找到。
        //初始化结束
        m_qucikUse.lastProjectDir.clear();
        m_qucikUse.lastProjectFileName.clear();
        /* 因为saveFile需要完成初始化之后才能调用，所以之前要令初始化完成。
         * 如果保存系统配置文件出错了，就会重新使得初始化完成为假。*/
        if(!saveFile())
        {
            m_isInitialize = false;
            LOG_WARNING("无法写入工作区配置文件，工作区配置初始化失败");
            return;
        }
    }
}

bool ConfigWorkspace::isInitialize()
{
    return m_isInitialize;
}

bool ConfigWorkspace::saveFile()
{
    // 通过m_isInitialize来，防止未初始化的保存
    if(!m_isInitialize)
    {
        LOG_WARNING("请完成初始化后再保存工作区配置文件");
        return false;
    }

    //从类中的数据构造json文件开始。
    QJsonObject quickUseObejct;
    quickUseObejct.insert("lastProjectDir", m_qucikUse.lastProjectDir);
    quickUseObejct.insert("lastProjectFileName", m_qucikUse.lastProjectFileName);

    QJsonObject workspaceObejct;
    workspaceObejct.insert("quickUse", quickUseObejct);

    QJsonDocument jsonDocument(workspaceObejct);
    //从类中的数据构造json文件结束。

    //将json文件写入到配置文件中，利用JsonFileUtil的writeJsonDocument函数写入
    if(!JsonFileUtil::writeJsonDocument(m_configFile, jsonDocument))
    {
        LOG_WARNING("工作区文件保存失败");
        return false;
    }
    else
    {
        LOG_INFO("工作区文件保存成功");
        return true;
    }
    //将json文件写入结束。
}

bool ConfigWorkspace::lordFile()
{
    // 通过m_isInitialize来，防止未初始化的保存
    if(!m_isInitialize)
    {
        LOG_WARNING("请完成初始化后再装载工作区配置文件");
        return false;
    }

    // 从文件中读取Json文件，readError是用来判断是否读取成功的。
    bool readError;
    QJsonDocument jsonDocument = JsonFileUtil::readJsonDocument(m_configFile, readError);
    if(readError)
    {
        LOG_WARNING("工作区文件装载失败");
        LOG_INFO("工作区文件重新初始化中");
        //如果读取失败，因为之前完成过初始化所以大概率是文件本身出问题了，考虑移除之后重新初始化。
        if(!FileUtil::removeFile(m_configFile))
        {
            LOG_WARNING("工作区配置文件移除失败");
        }
        else
        {
            m_isInitialize = false;
            initialize(m_configDir, m_fileName);
        }
        return false;
    }

    // 从Json文件中读取数据到类数据中开始
    // 注意这里没有做判断词条不存在的东西，以后记得加上。
    QJsonObject workspaceObejct = jsonDocument.object();

    QJsonObject quickUseObject  = workspaceObejct.value("quickUse").toObject();
    m_qucikUse.lastProjectDir = quickUseObject.value("lastProjectDir").toString();
    m_qucikUse.lastProjectFileName = quickUseObject.value("lastProjectFileName").toString();
    // 从Json文件中读取数据结束

    LOG_INFO("工作区配置文件装载成功");
    return true;
}


