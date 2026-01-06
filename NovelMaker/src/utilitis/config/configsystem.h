#ifndef CONFIGSYSTEM_H
#define CONFIGSYSTEM_H

#include "configbase.h"

#include <QFile>
#include <QObject>

class ConfigSystem : public ConfigBase
{
public:
    static ConfigSystem& instance();

public:
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
        QString m_logDir;

        QString m_configSystemFileName;
        QString m_configUserFileName;
        QString m_configWorkspaceName;

    } m_paths;

    struct EditorDefault
    {
        bool m_islightStyle;

        QStringList m_fontFamilies;
        quint16 m_fontSize;
        quint16 m_fontWeight;
        double m_fontLineHeight;
    } m_editorDefault;

private:
    ConfigSystem();
    ~ConfigSystem() = default;

    ConfigSystem(const ConfigSystem&) = delete;
    ConfigSystem& operator=(const ConfigSystem&) = delete;

    void initialConfigData();
    QJsonDocument constructJsonDocument();
    void constructConfigData(QJsonDocument jsonDocument);

private:
};

#endif // CONFIGSYSTEM_H
