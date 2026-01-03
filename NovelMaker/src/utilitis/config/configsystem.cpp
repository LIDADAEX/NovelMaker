#include "configsystem.h"
#include "src/utilitis/file/fileutil.h"
#include "src/core/logger.h"
#include "res/style/styledefine.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

#include <src/utilitis/file/jsonfileutil.h>

ConfigSystem &ConfigSystem::instance()
{
    static ConfigSystem instance;
    return instance;
}

void ConfigSystem::initialize(const QString &logDir)
{
    if(!m_isInitialize)
    {
        LOG_WARNING("重复初始化系统配置文件");
        return;
    }

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

        m_editorDefault.m_fontFamilies.clear();
        m_editorDefault.m_fontFamilies << EDITOR_DEFAULT_FONTFAMILIES_FIRST
                                       << EDITOR_DEFAULT_FONTFAMILIES_SECOND;
        m_editorDefault.m_fontSize = EDITOR_DEFAULT_FONT_SIZE;
        m_editorDefault.m_fontWeight = EDITOR_DEFAULT_FONT_WEIGHT;
        m_editorDefault.m_fontLineHeight = EDITOR_DEFAULT_FONT_LINE_HEIGHT;

        saveFile();
    }

    m_isInitialize = true;
}

bool ConfigSystem::saveFile()
{
    if(!m_isInitialize)
    {
        LOG_WARNING("请完成初始化后再保存系统配置文件");
        return false;
    }

    QJsonObject applicationObejct;
    applicationObejct.insert("name", m_application.m_name);
    applicationObejct.insert("displayName", m_application.m_displayName);
    applicationObejct.insert("version", m_application.m_version);
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

    if(!JsonFileUtil::writeJsonDocument(m_configFile, jsonDocument))
    {
        LOG_WARNING("系统文件保存失败");
        return false;
    }
    else
    {
        LOG_WARNING("系统文件保存成功");
        return true;
    }
}

bool ConfigSystem::lordFile()
{
    if(!m_isInitialize)
    {
        LOG_WARNING("请完成初始化后再装载系统配置文件");
        return false;
    }

    bool readError;
    QJsonDocument jsonDocument = JsonFileUtil::readJsonDocument(m_configFile, readError);
    if(readError)
    {
        LOG_WARNING("系统配置文件装载失败");
        LOG_INFO("系统配置重新初始化中");
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
    QJsonArray editorDefaultFontFamiliesArray;
    editorDefaultFontFamiliesArray = editorDefaultObject.value("fontFamilies").toArray();
    m_editorDefault.m_fontFamilies.clear();
    foreach (auto i, editorDefaultFontFamiliesArray)
        m_editorDefault.m_fontFamilies << i.toString();
    m_editorDefault.m_fontSize = editorDefaultObject.value("fontSize").toInt();
    m_editorDefault.m_fontWeight = editorDefaultObject.value("fontWeight").toInt();
    m_editorDefault.m_fontLineHeight = editorDefaultObject.value("fontLineHeight").toDouble();

    LOG_INFO("系统配置文件装载成功");
    return true;
}
