#include "configsystem.h"
#include "configuser.h"
#include "src/core/logger.h"
#include "src/utilitis/file/fileutil.h"
#include "src/utilitis/file/jsonfileutil.h"

#include <QJsonArray>
#include <QJsonObject>

ConfigUser &ConfigUser::instance()
{
    static ConfigUser instance;
    return instance;
}

void ConfigUser::initialize(const QString &configDir)
{
    m_configDir = configDir;
    m_fileName = CONFIG_USER_FILENAME;
    initialize(configDir, CONFIG_USER_FILENAME);
}

void ConfigUser::initialize(const QString &configDir, const QString &fileName)
{
    // 通过m_isInitialize来，防止重复初始化
    if(m_isInitialize)
    {
        LOG_WARNING("重复初始化用户配置文件");
        return;
    }

    m_configDir = configDir;
    m_fileName = fileName;

    // 检测文件夹路径是否存在，不存在则创建
    if(!FileUtil::dirCreat(configDir))
    {
        LOG_WARNING("用户配置路径创建失败，请检查用户配置路径");
        return;
    }

    m_configFile.setFileName(configDir + '/' + fileName);

    // 将初始化标志提前的原因是，方便后续的如果文件不存在用来创建文件用的，因为saveFile函数需要初始化完成。
    m_isInitialize = true;

    // 判断用户配置文件是否存在
    if(!m_configFile.exists())
    {
        LOG_INFO("用户配置文件缺失，正在创建用户配置文件");

        //初始化开始
        if(!ConfigSystem::instance().isInitialize())
        {
            m_isInitialize = false;
            LOG_WARNING("系统文件未初始化无法初始化用户配置文件");
            return;
        }
        m_editor.m_fontFamilies = ConfigSystem::instance().m_editorDefault.m_fontFamilies;
        m_editor.m_fontSize = ConfigSystem::instance().m_editorDefault.m_fontSize;
        m_editor.m_fontWeight = ConfigSystem::instance().m_editorDefault.m_fontWeight;
        m_editor.m_fontLineHeight = ConfigSystem::instance().m_editorDefault.m_fontLineHeight;
        m_editor.m_islightStyle = ConfigSystem::instance().m_editorDefault.m_islightStyle;
        //初始化结束

        /* 因为saveFile需要完成初始化之后才能调用，所以之前要令初始化完成。
         * 如果保存系统配置文件出错了，就会重新使得初始化完成为假。*/
        if(!saveFile())
        {
            m_isInitialize = false;
            LOG_WARNING("无法写入用户配置文件");
            return;
        }
    }

    LOG_INFO("用户配置文件初始化完成");
}

bool ConfigUser::isInitialize()
{
    return m_isInitialize;
}

void ConfigUser::unInitialize()
{
    m_isInitialize = false;
}

bool ConfigUser::saveFile()
{
    // 通过m_isInitialize来，防止未初始化的保存
    if(!m_isInitialize)
    {
        LOG_WARNING("请完成初始化后再保存系统配置文件");
        return false;
    }

    //从类中的数据构造json文件开始。
    QJsonObject editorObject;
    //因为FontFamilies是QStringList所以需要用QJsonArray装载。
    QJsonArray editorFontFamiliesArray;
    foreach (auto i, m_editor.m_fontFamilies)
        editorFontFamiliesArray.append(i);
    editorObject.insert("fontFamilies", editorFontFamiliesArray);
    editorObject.insert("fontSize", m_editor.m_fontSize);
    editorObject.insert("fontWeight", m_editor.m_fontWeight);
    editorObject.insert("fontLineHeight", m_editor.m_fontLineHeight);
    editorObject.insert("islightStyle", m_editor.m_islightStyle);

    QJsonObject userObejct;
    userObejct.insert("editor", editorObject);

    QJsonDocument jsonDocument(userObejct);
    //从类中的数据构造json文件结束。

    //将json文件写入到配置文件中，利用JsonFileUtil的writeJsonDocument函数写入
    if(!JsonFileUtil::writeJsonDocument(m_configFile, jsonDocument))
    {
        LOG_WARNING("系统文件保存失败");
        return false;
    }
    else
    {
        LOG_INFO("系统文件保存成功");
        return true;
    }
    //将json文件写入结束。
}

bool ConfigUser::lordFile()
{
    // 通过m_isInitialize来，防止未初始化的保存
    if(!m_isInitialize)
    {
        LOG_WARNING("请完成初始化后再装载用户配置文件");
        return false;
    }

    // 从文件中读取Json文件，readError是用来判断是否读取成功的。
    bool readError;
    QJsonDocument jsonDocument = JsonFileUtil::readJsonDocument(m_configFile, readError);
    if(readError)
    {
        LOG_WARNING("用户配置文件装载失败");
        LOG_INFO("用户配置重新初始化中");
        //如果读取失败，因为之前完成过初始化所以大概率是文件本身出问题了，考虑移除之后重新初始化。
        if(!FileUtil::removeFile(m_configFile))
        {
            LOG_WARNING("用户配置移除失败");
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
    QJsonObject userObejct = jsonDocument.object();

    QJsonObject editorObject  = userObejct.value("editor").toObject();
    // fontFamilies是QStringList，对应的是QJsonArray，所以此处构造QjsonArray。
    QJsonArray editorFontFamiliesArray;
    editorFontFamiliesArray = editorObject.value("fontFamilies").toArray();
    // 读取前清空m_fontFamilies。
    m_editor.m_fontFamilies.clear();
    foreach (auto i, editorFontFamiliesArray)
        m_editor.m_fontFamilies << i.toString();
    m_editor.m_fontSize = editorObject.value("fontSize").toInt();
    m_editor.m_fontWeight = editorObject.value("fontWeight").toInt();
    m_editor.m_fontLineHeight = editorObject.value("fontLineHeight").toDouble();
    m_editor.m_islightStyle = editorObject.value("islightStyle").toBool();
    // 从Json文件中读取数据结束

    LOG_INFO("用户配置文件装载成功");
    return true;
}
