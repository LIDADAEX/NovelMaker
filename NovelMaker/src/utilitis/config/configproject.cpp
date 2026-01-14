#include "configproject.h"

#include <QJsonDocument>
#include <QJsonObject>

ConfigProject &ConfigProject::instance()
{
    static ConfigProject instance;
    return instance;
}

ConfigProject::ConfigProject()
    : ConfigBase()
{
    m_configType = ConfigList::project;
}

void ConfigProject::initialConfigData()
{
}

QJsonDocument ConfigProject::constructJsonDocument()
{
    return QJsonDocument(QJsonObject());
}

void ConfigProject::constructConfigData(QJsonDocument jsonDocument)
{

}
