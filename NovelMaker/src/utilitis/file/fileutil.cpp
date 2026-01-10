#include "fileutil.h"
#include "src/core/logger.h"

bool FileUtil::fileOpen(QFile& file, QFlags<QFile::OpenModeFlag> openMode)
{
    if(!file.open(openMode))
    {
        LOG_WARNING(QString("%1 文件打开失败").arg(file.fileName()));
        return false;
    }
    return true;
}

bool FileUtil::isFileExist(QFile& file)
{
    return file.exists();
}

bool FileUtil::removeFile(QFile &file)
{
    if(file.exists())
    {
        if(!file.remove())
        {
            LOG_WARNING(QString("%1 文件删除失败").arg(file.fileName()));
            return false;
        }
        else return true;
    }
    else return true;
}

bool FileUtil::dirCreat(QString DirPath)
{
    if(!QDir().mkpath(DirPath))
    {
        LOG_WARNING(QString("%1 文件夹路径创建失败").arg(DirPath));
        return false;
    }
    return true;
}

QStringList FileUtil::dirFindFiles(QString DirPath, QStringList nameFilter, QDir::Filters filters, QDir::SortFlags sortFlags)
{
    QDir dir(DirPath);
    dir.setNameFilters(nameFilter);
    return dir.entryList(filters, sortFlags);
}
