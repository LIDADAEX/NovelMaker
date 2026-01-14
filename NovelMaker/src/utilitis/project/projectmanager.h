#ifndef PROJECTMANAGER_H
#define PROJECTMANAGER_H

#include <QObject>

class ProjectManager
{
public:
    static ProjectManager& instance();

    bool creatProject(QString projectDir, QString projectName);
    bool creatProject(QWidget* parent);

    void closeProject(quint16 projectNumber);

    QString getPrsentProjectName();


private:
    ProjectManager() = default;
    ~ProjectManager() = default;

    ProjectManager(const ProjectManager&) = delete;
    ProjectManager& operator=(const ProjectManager&) = delete;

    QString m_presentProjectDir;
    QString m_presentProjectName;
};

#endif // PROJECTMANAGER_H
