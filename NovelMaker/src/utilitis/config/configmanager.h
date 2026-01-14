#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>

class ConfigeManager
{
public:

    static ConfigeManager& instance();

    /**
     * @brief 初始化系统和用户配置
     * @return 初始化是否成功
     */
    bool initialize();

    /**
     * @brief 初始化系统和工作区配置
     * @return 返回项目编号，当项目初始化失败时返回INITIALIZE_PROJECT_ERROR(-1)
     * @param projectDir 项目目录
     * @param projectName 项目文件名
     */
    bool initializeProject(QString projectDir, QString projectName);

    /**
     * @brief 关闭项目
     * @return 返回是否关闭，当projectNumber大于等于m_projectNumber时会返回假
     * @param projectNumber 项目编号
     */
    void closeProject();

private:
    ConfigeManager() = default;
    ~ConfigeManager() = default;

    ConfigeManager(const ConfigeManager&) = delete;
    ConfigeManager& operator=(const ConfigeManager&) = delete;

    bool m_isOpenProject;
};

#endif // CONFIGMANAGER_H
