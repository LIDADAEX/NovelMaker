#include "projectmanager.h"
#include "src/utilitis/config/configsystem.h"
#include "src/utilitis/file/fileutil.h"
#include "src/utilitis/config/configmanager.h"

#include <QFileDialog>

ProjectManager& ProjectManager::instance()
{
    static ProjectManager instance;
    return instance;
}

bool ProjectManager::creatProject(QString projectDir, QString projectName)
{
    m_presentProjectDir = projectDir;
    m_presentProjectName = projectName;

    return ConfigeManager::instance().initializeProject(projectDir, projectName);
}

bool ProjectManager::creatProject(QWidget* parent)
{
    QString fileName = QFileDialog::getSaveFileName(parent, "创建新项目", QString(), "项目配置文件(*.json)");
    if(fileName.isEmpty()) return false;
    if(fileName.last(5) != ".json") fileName += ".json";
    QFile file(fileName);
    FileUtil::removeFile(file);
    QFileInfo fileInfo(fileName);
    file.setFileName(fileInfo.dir().path() + '/' + ConfigSystem::instance().m_paths.m_configWorkspaceFileName);
    FileUtil::removeFile(file);
    return ProjectManager::instance().creatProject(fileInfo.dir().path(), fileInfo.fileName());
}

void ProjectManager::closeProject(quint16 projectNumber)
{
    ConfigeManager::instance().closeProject();
}

QString ProjectManager::getPrsentProjectName()
{
    return m_presentProjectName.remove(".json");
}

