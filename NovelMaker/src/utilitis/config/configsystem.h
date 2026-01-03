#ifndef CONFIGSYSTEM_H
#define CONFIGSYSTEM_H

#include "configdefine.h"

#include <QFile>
#include <QObject>

class ConfigSystem
{
public:
    static ConfigSystem& instance();

    void initialize(const QString &logDir = CONFIG_SYSTEM_PATH);
    bool saveFile();
    bool lordFile();

    struct application
    {
        QString name;
        QString displayName;
        QString version;
        quint16 buildNumber;
        QString editor;
        QString website;
    };


private:
    ConfigSystem() = default;
    ~ConfigSystem() = default;

    ConfigSystem(const ConfigSystem&) = delete;
    ConfigSystem& operator=(const ConfigSystem&) = delete;

    bool m_isInitialize = false;

    QFile m_configFile;
};

#endif // CONFIGSYSTEM_H
