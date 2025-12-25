#include <styles/qsspreprocessor.h>
#include <QFile>

QssPreProcessor::QssPreProcessor(QObject *parent)
    : QObject{parent}
{}

QssPreProcessor::QssPreProcessor(QString styleFilePath, QObject *parent)
    : m_styleFilePath(styleFilePath), QObject{parent}
{}

QssPreProcessor::QssPreProcessor(QDir stylePath, QObject *parent)
    : m_stylePath(stylePath), QObject{parent}
{}

void QssPreProcessor::pathInit()
{
    m_stylePath.setFilter(QDir::Files);
    m_stylePath.setNameFilters(QStringList("*.qssa"));
}

void QssPreProcessor::setStyleFilePath(QString styleFilePath)
{
    m_styleFilePath = styleFilePath;
}

void QssPreProcessor::setStylePath(QDir stylePath)
{
    m_stylePath = stylePath;
}

void QssPreProcessor::startFilePreProcess(QMap<QString, QString> defineKey)
{
    QFile styleFile(m_styleFilePath);

    if(!styleFile.open(QIODeviceBase::ReadOnly))
    {
        qWarning() << "预处理文件，m_styleFilePath，无法打开！";
        return;
    }

    QString fileContent = styleFile.readAll();

    for(auto i = defineKey.begin(); i != defineKey.end(); i ++)
    {
        fileContent.replace(i.key(),i.value());
    }

    if(!styleFile.open(QIODeviceBase::WriteOnly))
    {
        qWarning() << "预处理文件，m_styleFilePath，无法写入！";
        return;
    }

    styleFile.write(fileContent.toUtf8());

    styleFile.close();

    qInfo() << "m_styleFilePath 预处理完毕！";

}

void QssPreProcessor::startDirPreProcess(QMap<QString, QString> defineKey)
{
    m_stylePath.entryList();
}
