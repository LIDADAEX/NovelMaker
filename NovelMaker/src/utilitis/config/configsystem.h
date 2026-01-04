#ifndef CONFIGSYSTEM_H
#define CONFIGSYSTEM_H

#include "configdefine.h"

#include <QFile>
#include <QObject>

class ConfigSystem
{
public:
    static ConfigSystem& instance();

    /***********************************
     * 函数名：initialize
     * 作用：初始化
     * 返回值：void
     * 形参：
     * configDir：系统配置文件的文件目录，默认值可以在configdefine.h文件中找到。
     ***********************************/
    void initialize(const QString &logDir = CONFIG_DIR);

    /***********************************
     * 函数名：saveFile
     * 作用：保存系统配置文件，注意，系统配置文件的保存来源于类内部的数据
     * 返回值：bool，用来说明是否成功保存文件
     * 形参：无
     ***********************************/
    /***********************************
     * 函数名：lordFile
     * 作用：从文件中装载数据至类中。使用类中的QFile文件。
     * 返回值：bool，用来说明是否成功装载文件
     * 形参：无
     ***********************************/
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
        QString m_logDir;

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

private:
    bool m_isInitialize = false;

    QFile m_configFile;
};

#endif // CONFIGSYSTEM_H
