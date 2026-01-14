#include "configworkspace.h"

#include <QJsonObject>

ConfigWorkspace &ConfigWorkspace::instance()
{
    static ConfigWorkspace instance;
    return instance;
}

ConfigWorkspace::ConfigWorkspace()
    : ConfigBase()
{
    m_configType = ConfigList::workspace;
}

void ConfigWorkspace::initialConfigData()
{
    m_qucikUse.lastProjectDir.clear();
    m_qucikUse.lastProjectFileName.clear();
}

QJsonDocument ConfigWorkspace::constructJsonDocument()
{
    QJsonObject quickUseObejct;
    quickUseObejct.insert("lastProjectDir", m_qucikUse.lastProjectDir);
    quickUseObejct.insert("lastProjectFileName", m_qucikUse.lastProjectFileName);

    QJsonObject workspaceObejct;
    workspaceObejct.insert("quickUse", quickUseObejct);

    return QJsonDocument(workspaceObejct);
}

void ConfigWorkspace::constructConfigData(QJsonDocument jsonDocument)
{
    QJsonObject workspaceObejct = jsonDocument.object();

    QJsonObject quickUseObject  = workspaceObejct.value("quickUse").toObject();
    m_qucikUse.lastProjectDir = quickUseObject.value("lastProjectDir").toString();
    m_qucikUse.lastProjectFileName = quickUseObject.value("lastProjectFileName").toString();
}
