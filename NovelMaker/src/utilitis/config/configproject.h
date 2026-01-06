#ifndef CONFIGPROJECT_H
#define CONFIGPROJECT_H

#include "configbase.h"


class ConfigProject : public ConfigBase
{
public:
    ConfigProject();
    ~ConfigProject() = default;

public:

private:
    void initialConfigData();
    QJsonDocument constructJsonDocument();
    void constructConfigData(QJsonDocument jsonDocument);

private:
};

#endif // CONFIGPROJECT_H
