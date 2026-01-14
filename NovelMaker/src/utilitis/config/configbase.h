#ifndef CONFIGBASE_H
#define CONFIGBASE_H

#include <QFile>
#include <QObject>
#include <QJsonDocument>

/**
 * @brief 配置列表
 *
 * 主要是定义了目前已有的子类类型
 */
enum class ConfigList
{
    system,
    project,
    user,
    workspace
};

/**
 * @brief 配置文件的抽象基类 (Abstract Base Class)
 *
 * 该类定义了所有配置文件管理类的通用接口和流程（初始化 -> 加载 -> 保存）。
 * 它负责处理底层的 JSON 文件读写和文件夹创建，具体的配置字段解析由子类实现。
 *
 * @note 所有的子类（如 ConfigSystem, ConfigUser）都必须实现 initialConfigData 等虚函数。
 */
class ConfigBase
{
public:
    ConfigBase() = default;
    virtual ~ConfigBase() = default;

    /**
     * @brief 拷贝构造函数，注意不会复制QFile的打开情况
     * @param c_configBase 待复制的类
     */
    ConfigBase(const ConfigBase& c_configBase);

    /**
     * @brief 等号运算符，注意不会复制QFile的打开情况
     * @param c_configBase 待复制的类
     */
    ConfigBase& operator=(const ConfigBase&);

    /**
     * @brief 初始化配置类，所有配置类都需要初始化才能使用
     * @param configDir 配置文件的文件目录，默认值可以在configdefine.h文件中找到
     * @param fileName 配置文件的文件名，默认值可以在在configdefine.h文件中找到
     */
    void initialize(const QString &configDir, const QString &fileName);

    /**
     * @brief 返回配置类是否初始化
     */
    bool isInitialize();

    /**
     * @brief 取消初始化，主要用于当文件通过初始化但是中途发现无法使用时重新初始化使用
     */
    void unInitialize();

    /**
     * @brief 用于在找不到配置文件时，用来构造默认配置文件，纯虚函数需要重载
     */
    virtual void initialConfigData() = 0;

    /**
     * @brief 用于将类中的数据构造成Json文档供saveFile函数使用
     * @return 返回需要写入文档的json文档
     */
    virtual QJsonDocument constructJsonDocument() = 0;

    /**
     * @brief 用于处理从loadFile函数中得到的json文档，使其变为类中的数据
     * @param jsonDocument 从文件中解析而来的json文档
     */
    virtual void constructConfigData(QJsonDocument jsonDocument) = 0;

    /**
     * @brief 保存配置类中的数据至对应文件，会检查是否初始化
     */
    bool saveFile();
    /**
     * @brief 读取文件中的数据至对应配置类中，会检查是否初始化
     */
    bool loadFile();

public:
    ConfigList m_configType;        ///<用来区分配置类型

private:

    QString m_typeString;           ///<用来构造日志的辅助字符串，自动生成无需管理
    bool m_isInitialize = false;    ///<初始化标志，默认为false

    QFile m_configFile;             ///< 配置类中的读写所需要的文件

    QString m_configDir;            ///< 配置类中初始化时所使用的路径
    QString m_fileName;             ///< 配置类中初始化时所使用的文件名
};

#endif // CONFIGBASE_H
