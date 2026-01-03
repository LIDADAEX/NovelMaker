#ifndef CONFIGSYSTEM_H
#define CONFIGSYSTEM_H

#include "configdefine.h"

#include <QFile>
#include <QObject>

class ConfigSystem
{
public:
    static ConfigSystem& instance();

    void initialize(const QString &logDir = CONFIG_DIR);
    bool saveFile();
    bool lordFile();

    struct Application
    {
        QString m_name;
        QString m_displayName;
        QString m_version;
        quint32 m_buildNumber;
        QString m_editor;
        QString m_website;
    } m_application;

    struct Paths
    {
        QString m_configDir;
        QString m_styleDir;

        QString m_configSystemFileName;
        QString m_configUserFileName;
        QString m_configWorkspaceName;

    } m_paths;

    struct EditorDefault
    {
        QStringList m_fontFamilies;
        quint16 m_fontSize;
        quint16 m_fontWeight;
        double m_fontLineHeight;
    } m_editorDefault;

private:
    ConfigSystem() = default;
    ~ConfigSystem() = default;

    ConfigSystem(const ConfigSystem&) = delete;
    ConfigSystem& operator=(const ConfigSystem&) = delete;

    bool m_isInitialize = false;

    QFile m_configFile;
};

#endif // CONFIGSYSTEM_H
