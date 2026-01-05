#ifndef CONFIGUSER_H
#define CONFIGUSER_H

#include "src/utilitis/config/configdefine.h"
#include <QFile>
#include <QObject>

class ConfigUser
{
public:
    static ConfigUser& instance();

    void initialize(const QString &configDir = CONFIG_DIR);
    void initialize(const QString &configDir, const QString& fileName);
    bool isInitialize();
    void unInitialize();

    bool saveFile();
    bool lordFile();

public:

    struct Editor
    {
        bool m_islightStyle;

        QStringList m_fontFamilies;
        quint16 m_fontSize;
        quint16 m_fontWeight;
        double m_fontLineHeight;
    }m_editor;

private:
    ConfigUser() = default;
    ~ConfigUser() = default;

    ConfigUser(const ConfigUser&) = delete;
    ConfigUser& operator=(const ConfigUser&) = delete;

private:
    bool m_isInitialize;

    QFile m_configFile;

    QString m_configDir;
    QString m_fileName;
};

#endif // CONFIGUSER_H
