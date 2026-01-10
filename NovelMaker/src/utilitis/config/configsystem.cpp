#include "configsystem.h"
#include "src/utilitis/style/styledefine.h"
#include "src/utilitis/config/configdefine.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

ConfigSystem &ConfigSystem::instance()
{
    static ConfigSystem instance;
    return instance;
}

void ConfigSystem::initialConfigData()
{
    m_application.m_name = CONFIG_SYSTEM_APPLICATION_NAME;
    m_application.m_displayName = CONFIG_SYSTEM_APPLICATION_DISPLAYNAME;
    m_application.m_version = CONFIG_SYSTEM_APPLICATION_VERSION;
    m_application.m_buildNumber = CONFIG_SYSTEM_APPLICATION_BUILDNUMBER;
    m_application.m_editor = CONFIG_SYSTEM_APPLICATION_EDITOR;
    m_application.m_website = CONFIG_SYSTEM_APPLICATION_WEBSITE;

    m_paths.m_configDir = CONFIG_DIR;
    m_paths.m_styleDir = STYLE_DIR;
    m_paths.m_logDir = LOG_DIR;
    m_paths.m_configSystemFileName = CONFIG_SYSTEM_FILENAME;
    m_paths.m_configUserFileName = CONFIG_USER_FILENAME;
    m_paths.m_configWorkspaceFileName = CONFIG_WORKSPACE_FILENAME;
    m_paths.m_styleFileName = STYLE_FILENAME;
    m_paths.m_stylePreDirName = STYLE_PRE_DIRNAME;
    m_paths.m_styleDarkDirName = STYLE_DARK_DIRNAME;
    m_paths.m_styleLightDirName = STYLE_LIGHT_DIRNAME;

    // 此处的m_fontFamilies是QStringList，所以需要这么做。并且在初始化之前要清空。
    m_editorDefault.m_fontFamilies.clear();
    m_editorDefault.m_fontFamilies << EDITOR_DEFAULT_FONTFAMILIES_FIRST
                                   << EDITOR_DEFAULT_FONTFAMILIES_SECOND;
    m_editorDefault.m_fontSize = EDITOR_DEFAULT_FONT_SIZE;
    m_editorDefault.m_fontWeight = EDITOR_DEFAULT_FONT_WEIGHT;
    m_editorDefault.m_fontLineHeight = EDITOR_DEFAULT_FONT_LINE_HEIGHT;
    m_editorDefault.m_islightStyle = EDITOR_DEFAULT_IS_LIGHT_STYLE;
}

QJsonDocument ConfigSystem::constructJsonDocument()
{
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
    pathsObject.insert("logDir", m_paths.m_logDir);
    pathsObject.insert("configSystemFileName", m_paths.m_configSystemFileName);
    pathsObject.insert("configUserFileName", m_paths.m_configUserFileName);
    pathsObject.insert("configWorkspaceFileName", m_paths.m_configWorkspaceFileName);
    pathsObject.insert("styleFileName", m_paths.m_styleFileName);
    pathsObject.insert("stylePreDirName", m_paths.m_stylePreDirName);
    pathsObject.insert("styleDarkDirName", m_paths.m_styleDarkDirName);
    pathsObject.insert("styleLightDirName", m_paths.m_styleLightDirName);

    QJsonObject editorDefaultObject;
    //因为FontFamilies是QStringList所以需要用QJsonArray装载。
    QJsonArray editorDefaultFontFamiliesArray;
    foreach (auto i, m_editorDefault.m_fontFamilies)
        editorDefaultFontFamiliesArray.append(i);
    editorDefaultObject.insert("fontFamilies", editorDefaultFontFamiliesArray);
    editorDefaultObject.insert("fontSize", m_editorDefault.m_fontSize);
    editorDefaultObject.insert("fontWeight", m_editorDefault.m_fontWeight);
    editorDefaultObject.insert("fontLineHeight", m_editorDefault.m_fontLineHeight);
    editorDefaultObject.insert("islightStyle", m_editorDefault.m_islightStyle);

    QJsonObject systemObejct;
    systemObejct.insert("application", applicationObejct);
    systemObejct.insert("paths", pathsObject);
    systemObejct.insert("editorDefault", editorDefaultObject);

    return QJsonDocument(systemObejct);
}

void ConfigSystem::constructConfigData(QJsonDocument jsonDocument)
{
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
    m_paths.m_logDir = pathsObject.value("logDir").toString();
    m_paths.m_configSystemFileName = pathsObject.value("configSystemFileName").toString();
    m_paths.m_configUserFileName = pathsObject.value("configUserFileName").toString();
    m_paths.m_configWorkspaceFileName = pathsObject.value("configWorkspaceFileName").toString();
    m_paths.m_styleFileName = pathsObject.value("styleFileName").toString();
    m_paths.m_stylePreDirName = pathsObject.value("stylePreDirName").toString();
    m_paths.m_styleDarkDirName = pathsObject.value("styleDarkDirName").toString();
    m_paths.m_styleLightDirName = pathsObject.value("styleLightDirName").toString();

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
    m_editorDefault.m_islightStyle = editorDefaultObject.value("islightStyle").toBool();
}

ConfigSystem::ConfigSystem()
    : ConfigBase()
{
    m_configType = ConfigList::system;
}
