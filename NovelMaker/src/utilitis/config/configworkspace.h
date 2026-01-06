#ifndef CONFIGWORKSPACE_H
#define CONFIGWORKSPACE_H

#include "configbase.h"
#include <QFile>
#include <QObject>

class ConfigWorkspace : public ConfigBase
{
public:
    ConfigWorkspace();
    ~ConfigWorkspace() = default;

public:
    struct QuickUse
    {
        QString lastProjectDir;
        QString lastProjectFileName;
    }m_qucikUse;

private:
    void initialConfigData();
    QJsonDocument constructJsonDocument();
    void constructConfigData(QJsonDocument jsonDocument);

private:
};

#endif // CONFIGWORKSPACE_H
