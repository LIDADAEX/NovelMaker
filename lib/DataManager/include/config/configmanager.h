#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include "DataManager_global.h"

#include <QJsonDocument>
#include <QMap>
#include <QObject>

namespace DataManager {

class DATAMANAGER_EXPORT ConfigManager : public QObject
{
public:
    explicit ConfigManager(QObject* parent = nullptr);
    explicit ConfigManager(QString configFilePath, QObject* parent = nullptr);

    void setConfigFilePath(QString configFilePath);
    bool isExistConfig(void);

    void readConfigData(void);
    void writeConfigData(void);

    QJsonDocument getConfigData(void);
    void setConfigData(QJsonDocument configData);

private:

private:

    QString m_configFilePath;

    QJsonDocument m_configData;
};

}


#endif // CONFIGMANAGER_H
