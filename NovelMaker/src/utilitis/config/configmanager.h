#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>
#include "configproject.h"
#include "configworkspace.h"

class ConfigeManager
{
public:
    ConfigeManager() = default;
    ~ConfigeManager() = default;

    bool initialize();
    bool initializeProject(QString projectDir, QString projectName);

public:
    ConfigProject m_configPoject;
    ConfigWorkspace m_configWorkspace;
private:

};

#endif // CONFIGMANAGER_H
