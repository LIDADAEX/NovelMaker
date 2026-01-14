#ifndef CONFIGPROJECT_H
#define CONFIGPROJECT_H

#include "configbase.h"


class ConfigProject : public ConfigBase
{
public:
    static ConfigProject& instance();

private:
    ConfigProject();
    ~ConfigProject() = default;

    ConfigProject(const ConfigProject&) = default;
    ConfigProject& operator=(const ConfigProject&)  = default;


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

#endif // CONFIGPROJECT_H
