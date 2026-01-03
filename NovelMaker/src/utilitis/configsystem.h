#ifndef CONFIGSYSTEM_H
#define CONFIGSYSTEM_H

#define CONFIGSYSTEM_PATH "./res/config"

#include <QObject>

class ConfigSystem
{
public:
    static ConfigSystem& instance();

    void initialize(const QString &logDir = CONFIGSYSTEM_PATH);

private:
    ConfigSystem() = default;
    ~ConfigSystem() = default;

    ConfigSystem(const ConfigSystem&) = delete;
    ConfigSystem& operator=(const ConfigSystem&) = delete;

    bool m_isInitialize = false;
};

#endif // CONFIGSYSTEM_H
