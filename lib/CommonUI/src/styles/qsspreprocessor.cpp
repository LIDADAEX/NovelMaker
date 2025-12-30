#include <styles/qsspreprocessor.h>
#include <QFile>

QssPreProcessor::QssPreProcessor(QObject *parent)
    : QObject{parent}
{
    pathInit();
}

QssPreProcessor::QssPreProcessor(QString styleFilePath, QObject *parent)
    : m_styleFilePath(styleFilePath), QObject{parent}
{
    pathInit();
}

QssPreProcessor::QssPreProcessor(QDir stylePath, QObject *parent)
    : m_stylePath(stylePath), QObject{parent}
{
    pathInit();
}

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

    QFile styleFileDep(m_styleFilePath.removeLast());

    if(styleFileDep.exists())
    {
        if(!styleFileDep.remove())
        {
            qWarning() << "预处理文件" + m_styleFilePath + "无法删除！请检查！";
            return;
        }
    }

    if(!styleFile.copy(m_styleFilePath))
    {
        qWarning() << "预处理文件 " + m_styleFilePath + " 无法完成复制，请检查！";
        return;
    }

    styleFile.setFileName(m_styleFilePath);

    if(!styleFile.open(QIODeviceBase::ReadOnly))
    {
        qWarning() << "预处理文件副本 " + m_styleFilePath + " 无法打开！";
        return;
    }

    QString fileContent = styleFile.readAll();

    for(auto i = defineKey.begin(); i != defineKey.end(); i ++)
    {
        fileContent.replace(i.key(),i.value());
    }

    styleFile.close();

    if(!styleFile.open(QIODeviceBase::WriteOnly))
    {
        qWarning() << "预处理文件" + m_styleFilePath +  " 无法写入！";
        return;
    }

    styleFile.write(fileContent.toUtf8());

    styleFile.close();

    qInfo() << m_styleFilePath + " 预处理完毕！";

}

void QssPreProcessor::startDirPreProcess(QMap<QString, QString> defineKey)
{
    if(!m_stylePath.exists())
    {
        qWarning() << "预处理文件路径不存在，请检查！";
        return;
    }

    QStringList fileList = m_stylePath.entryList();

    foreach (auto i, fileList) {
        setStyleFilePath(m_stylePath.filePath(i));
        startFilePreProcess(defineKey);
    }

    qDebug() << m_stylePath.path() + " 预处理完成！";
}
