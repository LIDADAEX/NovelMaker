#include "configproject.h"

#include <QJsonDocument>
#include <QJsonObject>

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
