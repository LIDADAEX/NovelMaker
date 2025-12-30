#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QDir>

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

void DataManager::ConfigManager::creatConfig(QString configFilePath, QJsonDocument configInit)
{
    QFileInfo fileInfo(configFilePath);
    QDir path = fileInfo.dir();
    if(!path.exists())
    {
        if(!path.mkpath("."))
        {
            qWarning() << "无法在此位置 "+ path.path() +" 创建配置文件夹，请检查权限或文件夹路径！";
        }
    }

    QFile file(configFilePath);
    if(!file.open(QIODeviceBase::WriteOnly))
    {
        qWarning() << "配置文件正在被占用无法写入！";
        return;
    }

    file.write(configInit.toJson());
    file.close();
    qDebug() << configFilePath + " 配置初始化完毕";
}
