#include "configsystem.h"
#include "src/utilitis/file/fileutil.h"
#include "src/utilitis/file/jsonfileutil.h"
#include "src/core/logger.h"
#include "res/style/styledefine.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

ConfigSystem &ConfigSystem::instance()
{
    static ConfigSystem instance;
    return instance;
}

void ConfigSystem::initialize(const QString &configDir)
{
    // 通过m_isInitialize来，防止重复初始化
    if(m_isInitialize)
    {
        LOG_WARNING("重复初始化系统配置文件");
        return;
    }

    // 检测文件夹路径是否存在，不存在则创建
    if(!FileUtil::dirCreat(configDir))
    {
        LOG_WARNING("系统配置路径创建失败，请检查系统配置路径");
        return;
    }

    /* 设置QFile文件，其中'/'是因为configDir是文件夹路径，CONFIG_SYSTEM_FILENAME是文件名
     * 但此处有点小问题，以后如果想要更换CONFIG_SYSTEM_FILENAME的名字的话，可能没法更改。*/
    m_configFile.setFileName(configDir + '/' + CONFIG_SYSTEM_FILENAME);

    // 将初始化标志提前的原因是，方便后续的如果文件不存在用来创建文件用的，因为saveFile函数需要初始化完成。
    m_isInitialize = true;

    // 判断系统配置文件是否存在
    if(!m_configFile.exists())
    {
        LOG_INFO("系统配置文件缺失，正在创建系统配置文件");

        // 不存在则开始利用硬编码的默认值进行初始化，以下的宏定义的值都能在configdefine.h文件中找到。
        m_application.m_name = CONFIG_SYSTEM_APPLICATION_NAME;
        m_application.m_displayName = CONFIG_SYSTEM_APPLICATION_DISPLAYNAME;
        m_application.m_version = CONFIG_SYSTEM_APPLICATION_VERSION;
        m_application.m_buildNumber = CONFIG_SYSTEM_APPLICATION_BUILDNUMBER;
        m_application.m_editor = CONFIG_SYSTEM_APPLICATION_EDITOR;
        m_application.m_website = CONFIG_SYSTEM_APPLICATION_WEBSITE;

        m_paths.m_configDir = CONFIG_DIR;
        m_paths.m_styleDir = STYLE_DIR;
        m_paths.m_configSystemFileName = CONFIG_SYSTEM_FILENAME;
        m_paths.m_configUserFileName = CONFIG_USER_FILENAME;
        m_paths.m_configWorkspaceName = CONFIG_WORKSPACE_FILENAME;
        //初始化结束

        // 此处的m_fontFamilies是QStringList，所以需要这么做。并且在初始化之前要清空。
        m_editorDefault.m_fontFamilies.clear();
        m_editorDefault.m_fontFamilies << EDITOR_DEFAULT_FONTFAMILIES_FIRST
                                       << EDITOR_DEFAULT_FONTFAMILIES_SECOND;
        m_editorDefault.m_fontSize = EDITOR_DEFAULT_FONT_SIZE;
        m_editorDefault.m_fontWeight = EDITOR_DEFAULT_FONT_WEIGHT;
        m_editorDefault.m_fontLineHeight = EDITOR_DEFAULT_FONT_LINE_HEIGHT;

        /* 因为saveFile需要完成初始化之后才能调用，所以之前要令初始化完成。
         * 如果保存系统配置文件出错了，就会重新使得初始化完成为假。*/
        if(!saveFile())
        {
            m_isInitialize = false;
        }
    }

    LOG_INFO("系统配置初始化完成");
}

bool ConfigSystem::saveFile()
{
    // 通过m_isInitialize来，防止未初始化的保存
    if(!m_isInitialize)
    {
        LOG_WARNING("请完成初始化后再保存系统配置文件");
        return false;
    }

    //从类中的数据构造json文件开始。
    QJsonObject applicationObejct;
    applicationObejct.insert("name", m_application.m_name);
    applicationObejct.insert("displayName", m_application.m_displayName);
    applicationObejct.insert("version", m_application.m_version);
    //m_buildNumber是一个quint32的数据，想要正常保存它需要qint64，因为QJsonValue不支持无符号整型。
    applicationObejct.insert("buildNumber", qint64(m_application.m_buildNumber));
    applicationObejct.insert("editor", m_application.m_editor);
    applicationObejct.insert("website", m_application.m_website);

    QJsonObject pathsObject;
    pathsObject.insert("configDir", m_paths.m_configDir);
    pathsObject.insert("styleDir", m_paths.m_styleDir);
    pathsObject.insert("configSystemFileName", m_paths.m_configSystemFileName);
    pathsObject.insert("configUserFileName", m_paths.m_configUserFileName);
    pathsObject.insert("configWorkspaceName", m_paths.m_configWorkspaceName);

    QJsonObject editorDefaultObject;
    //因为FontFamilies是QStringList所以需要用QJsonArray装载。
    QJsonArray editorDefaultFontFamiliesArray;
    foreach (auto i, m_editorDefault.m_fontFamilies)
        editorDefaultFontFamiliesArray.append(i);
    editorDefaultObject.insert("fontFamilies", editorDefaultFontFamiliesArray);
    editorDefaultObject.insert("fontSize", m_editorDefault.m_fontSize);
    editorDefaultObject.insert("fontWeight", m_editorDefault.m_fontWeight);
    editorDefaultObject.insert("fontLineHeight", m_editorDefault.m_fontLineHeight);

    QJsonObject systemObejct;
    systemObejct.insert("application", applicationObejct);
    systemObejct.insert("paths", pathsObject);
    systemObejct.insert("editorDefault", editorDefaultObject);

    QJsonDocument jsonDocument(systemObejct);
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


bool ConfigSystem::lordFile()
{
    // 通过m_isInitialize来，防止未初始化的保存
    if(!m_isInitialize)
    {
        LOG_WARNING("请完成初始化后再装载系统配置文件");
        return false;
    }

    // 从文件中读取Json文件，readError是用来判断是否读取成功的。
    bool readError;
    QJsonDocument jsonDocument = JsonFileUtil::readJsonDocument(m_configFile, readError);
    if(readError)
    {
        LOG_WARNING("系统配置文件装载失败");
        LOG_INFO("系统配置重新初始化中");
        //如果读取失败，因为之前完成过初始化所以大概率是文件本身出问题了，考虑移除之后重新初始化。
        if(!FileUtil::removeFile(m_configFile))
        {
            LOG_WARNING("系统配置移除失败");
        }
        else
        {
            m_isInitialize = false;
            initialize();
        }
        return false;
    }

    // 从Json文件中读取数据到类数据中开始
    QJsonObject systemObejct = jsonDocument.object();

    QJsonObject applicationObejct = systemObejct.value("application").toObject();
    m_application.m_name = applicationObejct.value("name").toString();
    m_application.m_displayName = applicationObejct.value("displayName").toString();
    m_application.m_version = applicationObejct.value("version").toString();
    m_application.m_buildNumber = applicationObejct.value("buildNumber").toInteger();
    m_application.m_editor = applicationObejct.value("editor").toString();
    m_application.m_website = applicationObejct.value("website").toString();

    QJsonObject pathsObject = systemObejct.value("paths").toObject();
    m_paths.m_configDir = pathsObject.value("configDir").toString();
    m_paths.m_styleDir = pathsObject.value("styleDir").toString();
    m_paths.m_configSystemFileName = pathsObject.value("configSystemFileName").toString();
    m_paths.m_configUserFileName = pathsObject.value("configUserFileName").toString();
    m_paths.m_configWorkspaceName = pathsObject.value("configWorkspaceName").toString();

    QJsonObject editorDefaultObject  = systemObejct.value("editorDefault").toObject();
    // fontFamilies是QStringList，对应的是QJsonArray，所以此处构造QjsonArray。
    QJsonArray editorDefaultFontFamiliesArray;
    editorDefaultFontFamiliesArray = editorDefaultObject.value("fontFamilies").toArray();
    // 读取前清空m_fontFamilies。
    m_editorDefault.m_fontFamilies.clear();
    foreach (auto i, editorDefaultFontFamiliesArray)
        m_editorDefault.m_fontFamilies << i.toString();
    m_editorDefault.m_fontSize = editorDefaultObject.value("fontSize").toInt();
    m_editorDefault.m_fontWeight = editorDefaultObject.value("fontWeight").toInt();
    m_editorDefault.m_fontLineHeight = editorDefaultObject.value("fontLineHeight").toDouble();
    // 从Json文件中读取数据结束

    LOG_INFO("系统配置文件装载成功");
    return true;
}
