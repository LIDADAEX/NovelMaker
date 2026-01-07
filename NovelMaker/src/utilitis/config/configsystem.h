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
    /**
     * @brief 应用类，主要储存应用的一些数据
     */
    struct Application
    {
        QString m_name;
        QString m_displayName;
        QString m_version;
        quint32 m_buildNumber;
        QString m_editor;
        QString m_website;
    } m_application;

    /**
     * @brief 路径类，主要储存各种路径
     *
     * 但这种路径多半是不可更改的或者更改较少的
     */
    struct Paths
    {
        QString m_configDir;
        QString m_styleDir;
        QString m_logDir;

        QString m_configSystemFileName;
        QString m_configUserFileName;
        QString m_configWorkspaceName;

    } m_paths;

    /**
     * @brief 编辑器默认配置类，用于初始化编辑器
     */
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

    /**
     * @brief 用于在找不到配置文件时，用来构造默认配置文件，纯虚函数需要重载
     */
    void initialConfigData();

    /**
     * @brief 用于将类中的数据构造成Json文档供saveFile函数使用
     * @return 返回需要写入文档的json文档
     */
    QJsonDocument constructJsonDocument();

    /**
     * @brief 用于处理从loadFile函数中得到的json文档，使其变为类中的数据
     * @param jsonDocument 从文件中解析而来的json文档
     */
    void constructConfigData(QJsonDocument jsonDocument);
};

#endif // CONFIGSYSTEM_H
