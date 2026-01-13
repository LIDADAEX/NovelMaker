#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QObject>
#include "src/utilitis/config/configmanager.h"

class ProjectManager
{
public:
    static ProjectManager& instance();

    void creatProject(QString projectDir, QString projectName);
    void creatProject(QWidget* parent);
    QString getPrsentProjectName();
    void switchProject(quint16 projectNumber);
    quint16 getPresentProjectNumber();

    ConfigProject* m_configProject;
    ConfigWorkspace* m_configWorkspace;

private:
    ProjectManager() = default;
    ~ProjectManager() = default;

    ProjectManager(const ProjectManager&) = delete;
    ProjectManager& operator=(const ProjectManager&) = delete;

    QString m_presentProjectDir;
    QString m_presentProjectName;

    quint16 m_projectNumber;
};

#endif // PROJECTMANAGER_H
