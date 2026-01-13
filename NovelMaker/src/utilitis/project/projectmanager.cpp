#include "projectmanager.h"

#include <QFileDialog>

ProjectManager& ProjectManager::instance()
{
    static ProjectManager instance;
    return instance;
}

void ProjectManager::creatProject(QString projectDir, QString projectName)
{
    m_presentProjectDir = projectDir;
    m_presentProjectName = projectName;

    m_projectNumber = ConfigeManager::instance().initializeProject(projectDir, projectName);
    ConfigeManager::instance().getConfig(m_projectNumber, m_configProject, m_configWorkspace);

}

void ProjectManager::creatProject(QWidget* parent)
{
    QString fileName = QFileDialog::getSaveFileName(parent, "创建新项目", QString(), "项目配置文件(*.json)");
    if(fileName.isEmpty()) return;
    if(fileName.last(5) != ".json") fileName += ".json";

    QFileInfo fileInfo(fileName);
    ProjectManager::instance().creatProject(fileInfo.dir().path(), fileInfo.fileName());
}

QString ProjectManager::getPrsentProjectName()
{
    return m_presentProjectName.remove(".json");
}

void ProjectManager::switchProject(quint16 projectNumber)
{
    m_projectNumber = projectNumber;
    ConfigeManager::instance().getConfig(m_projectNumber, m_configProject, m_configWorkspace);
}

quint16 ProjectManager::getPresentProjectNumber()
{
    return m_projectNumber;
}
