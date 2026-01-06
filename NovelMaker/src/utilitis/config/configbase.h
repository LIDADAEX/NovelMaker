#ifndef CONFIGBASE_H
#define CONFIGBASE_H

#include <QFile>
#include <QObject>

enum class ConfigList
{
    system,
    project,
    user,
    workspace
};

class ConfigBase
{
public:
    /***********************************
     * 函数名：initialize
     * 作用：初始化
     * 返回值：void
     * 形参：
     * configDir：配置文件的文件目录，默认值可以在configdefine.h文件中找到。
     ***********************************/

    /***********************************
     * 函数名：initialize
     * 作用：初始化
     * 返回值：void
     * 形参：
     * configDir：配置文件的文件目录，默认值可以在configdefine.h文件中找到。
     * fileName：配置文件的文件名称，默认值可以在configdefine.h文件中找到。
     ***********************************/

    /***********************************
     * 函数名：unInitialize
     * 作用：取消初始化
     * 返回值：void
     * 形参：void
     ***********************************/
    void initialize(const QString &configDir, const QString &fileName);
    bool isInitialize();
    void unInitialize();

    virtual void initialConfigData() = 0;
    virtual QJsonDocument constructJsonDocument() = 0;
    virtual void constructConfigData(QJsonDocument jsonDocument) = 0;

    /***********************************
     * 函数名：saveFile
     * 作用：保存配置文件，注意，系统配置文件的保存来源于类内部的数据
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

public:
    ConfigList m_configType;
private:

private:

    QString m_typeString;
    bool m_isInitialize = false;

    QFile m_configFile;

    QString m_configDir;
    QString m_fileName;
};

#endif // CONFIGBASE_H
