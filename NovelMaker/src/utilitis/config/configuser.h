#ifndef CONFIGUSER_H
#define CONFIGUSER_H

#include "configbase.h"
#include <QFile>
#include <QObject>

class ConfigUser : public ConfigBase
{
public:
    static ConfigUser& instance();

public:
    /**
     * @brief 编辑器类，主要给设置用
     */
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

private:
};

#endif // CONFIGUSER_H
