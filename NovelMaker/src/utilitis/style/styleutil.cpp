#include "styleutil.h"
#include "src/core/logger.h"
#include "src/utilitis/file/fileutil.h"

StyleUtil::StyleUtil(QString stylePreDir, QString styleDir, QString styleName)
    :m_stylePreDir(stylePreDir), m_styleDir(styleDir), m_styleName(styleName)
{
    if(!FileUtil::dirCreat(stylePreDir) && !FileUtil::dirCreat(styleDir)) m_isInitialize = false;
}

bool StyleUtil::preProcess(QMap<QString, QString> styleKey)
{
    QStringList fileList = FileUtil::dirFindFiles(m_stylePreDir, QStringList("*.qssa"));

    foreach (auto i, fileList) {
        m_styleFile.setFileName(m_stylePreDir + '/' + i);
        if(!FileUtil::fileOpen(m_styleFile, QIODeviceBase::ReadOnly))
        {
            LOG_WARNING(QString("%1 读取阶段无法打开，预处理阶段无法继续").arg(m_styleFile.fileName()));
            return false;
        }

        QString styleContent = m_styleFile.readAll();
        m_styleFile.close();

        for(auto j = styleKey.constBegin(); j != styleKey.constEnd(); j ++)
        {
            styleContent.replace(j.key(), j.value());
        }

        m_styleFile.setFileName(m_styleDir + '/' + i.removeLast());
        if(!FileUtil::fileOpen(m_styleFile, QIODeviceBase::WriteOnly))
        {
            LOG_WARNING(QString("%1 写入阶段无法打开，预处理阶段无法继续").arg(m_styleFile.fileName()));
            return false;
        }

        m_styleFile.write(styleContent.toUtf8());
        m_styleFile.close();
    }

    return true;
}

bool StyleUtil::merger()
{
    QStringList fileList = FileUtil::dirFindFiles(m_styleDir, QStringList("*.qss"));

    QFile endFile;
    endFile.setFileName(m_styleDir + '/' + m_styleName);
    if(!FileUtil::removeFile(endFile))
    {
        LOG_WARNING(QString("%1 清除阶段无法打开，合成无法继续").arg(endFile.fileName()));
        return false;
    }
    if(!FileUtil::fileOpen(endFile, QIODeviceBase::WriteOnly | QIODeviceBase::Append))
    {
        LOG_WARNING(QString("%1 写入阶段无法打开，合成无法继续").arg(endFile.fileName()));
        return false;
    }

    m_styleFileList.clear();
    foreach (auto i, fileList) {
        m_styleFileList << m_styleDir + '/' + i;
        m_styleFile.setFileName(m_styleFileList.last());
        if(!FileUtil::fileOpen(m_styleFile, QIODeviceBase::ReadOnly))
        {
            LOG_WARNING(QString("%1 读取阶段无法打开，合成无法继续").arg(m_styleFile.fileName()));
            return false;
        }

        endFile.write(m_styleFile.readAll());
        m_styleFile.close();
    }

    endFile.close();
    return true;
}

QStringList StyleUtil::getFileList()
{
    return m_styleFileList;
}

QString StyleUtil::getStyle()
{
    QFile endFile;
    endFile.setFileName(m_styleDir + '/' + m_styleName);
    if(!FileUtil::fileOpen(endFile, QIODeviceBase::ReadOnly))
    {
        LOG_WARNING(QString("%1 读取阶段无法打开，获取样式失败").arg(endFile.fileName()));
        return QString();
    }

    QString styleString = endFile.readAll();
    endFile.close();

    return styleString;
}

