#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <QObject>
#include "configproject.h"
#include "configworkspace.h"

#define INITIALIZE_PROJECT_ERROR -1

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
    qint16 initializeProject(QString projectDir, QString projectName);

    /**
     * @brief 关闭项目
     * @return 返回是否关闭，当projectNumber大于等于m_projectNumber时会返回假
     * @param projectNumber 项目编号
     */
    bool closeProject(quint16 projectNumber);

    /**
     * @brief 得到项目的配置类和工作区配置类
     * @return 返回是否取得，当projectNumber大于等于m_projectNumber时会返回假
     * @param projectNumber 项目编号
     * @param p_configProject 项目配置类的指针
     * @param p_configWorkspace 工作区配置类的指针
     */
    bool getConfig(quint16 projectNumber, ConfigProject* p_configProject, ConfigWorkspace* p_configWorkspace);

private:
    ConfigeManager() = default;
    ~ConfigeManager() = default;

    ConfigeManager(const ConfigeManager&) = delete;
    ConfigeManager& operator=(const ConfigeManager&) = delete;

    quint16 m_projectNumber = 0;                  ///<项目编号，为预期项目编号也就是目前储存的是将来下一个项目的编号
    QList<ConfigProject> m_configPojectList;      ///<项目配置类的链表，储存项目配置类，按照项目编号排序
    QList<ConfigWorkspace> m_configWorkspaceList; ///<工作区配置类的链表，储存工作区配置类，按照项目编号排序

};

#endif // CONFIGMANAGER_H
