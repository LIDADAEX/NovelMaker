#include "configsystem.h"
#include "configuser.h"

#include <QJsonArray>
#include <QJsonObject>

ConfigUser &ConfigUser::instance()
{
    static ConfigUser instance;
    return instance;
}

void ConfigUser::initialConfigData()
{
    m_editor.m_fontFamilies = ConfigSystem::instance().m_editorDefault.m_fontFamilies;
    m_editor.m_fontSize = ConfigSystem::instance().m_editorDefault.m_fontSize;
    m_editor.m_fontWeight = ConfigSystem::instance().m_editorDefault.m_fontWeight;
    m_editor.m_fontLineHeight = ConfigSystem::instance().m_editorDefault.m_fontLineHeight;
    m_editor.m_islightStyle = ConfigSystem::instance().m_editorDefault.m_islightStyle;
}

QJsonDocument ConfigUser::constructJsonDocument()
{
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

    return QJsonDocument(userObejct);
}

void ConfigUser::constructConfigData(QJsonDocument jsonDocument)
{
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
}

ConfigUser::ConfigUser()
    : ConfigBase()
{
    m_configType = ConfigList::user;
}
