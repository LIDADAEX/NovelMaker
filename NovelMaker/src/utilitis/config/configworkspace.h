#ifndef CONFIGWORKSPACE_H
#define CONFIGWORKSPACE_H

#include <QFile>
#include <QObject>

class ConfigWorkspace
{
public:
    void initialize(QString configDir, QString fileName);
    bool isInitialize(void);

    bool saveFile();
    bool lordFile();
public:
    struct QuickUse
    {
        QString lastProjectDir;
        QString lastProjectFileName;
    }m_qucikUse;

private:


private:
    QString m_configDir;
    QString m_fileName;
    QFile m_configFile;

    bool m_isInitialize = false;

};

#endif // CONFIGWORKSPACE_H
