#include <QFile>
#include <QDebug>
#include <QJsonDocument>

#include <config/configmanager.h>

DataManager::ConfigManager::ConfigManager(QString configFilePath, QObject *parent)
    : m_configFilePath(configFilePath), QObject{parent}
{}

bool DataManager::ConfigManager::isExistConfig()
{
    QFile configeFile(m_configFilePath);
    return configeFile.exists();
}

void DataManager::ConfigManager::readConfigData()
{
    QFile configFile(m_configFilePath);
    if(!configFile.open(QIODeviceBase::ReadOnly))
    {
        qWarning() << "配置文件无法打开，请检查文件路径！";
        return;
    }

    QJsonDocument configDocument;
    QJsonParseError parseError;
    configDocument = QJsonDocument::fromJson(configFile.readAll(), &parseError);
    configFile.close();

    if(parseError.error != QJsonParseError::NoError)
    {
        qWarning() << "配置文件损坏，请检查文件！";
        return;
    }

    m_configData = configDocument;

}

void DataManager::ConfigManager::writeConfigData()
{
    QFile configFile(m_configFilePath);
    if(!configFile.open(QIODeviceBase::WriteOnly))
    {
        qWarning() << "配置文件无法写入，请检查文件路径！";
        return;
    }

    configFile.write(m_configData.toJson());
    configFile.close();
}

QJsonDocument DataManager::ConfigManager::getConfigData()
{
    return m_configData;
}

void DataManager::ConfigManager::setConfigData(QJsonDocument configData)
{
    m_configData = configData;
}
