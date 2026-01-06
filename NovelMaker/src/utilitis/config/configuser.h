#ifndef CONFIGUSER_H
#define CONFIGUSER_H

#include "src/utilitis/config/configdefine.h"
#include "configbase.h"
#include <QFile>
#include <QObject>

class ConfigUser : public ConfigBase
{
public:
    static ConfigUser& instance();

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
    ConfigUser();
    ~ConfigUser() = default;

    ConfigUser(const ConfigUser&) = delete;
    ConfigUser& operator=(const ConfigUser&) = delete;

    void initialConfigData();
    QJsonDocument constructJsonDocument();
    void constructConfigData(QJsonDocument jsonDocument);

private:
};

#endif // CONFIGUSER_H
