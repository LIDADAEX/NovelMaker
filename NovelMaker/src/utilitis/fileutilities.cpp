#include "fileutilities.h"
#include "src/core/logger.h"

#include <QDir>

bool FileUtilities::fileOpen(QFile *file, QIODeviceBase::OpenModeFlag openMode)
{
    if(!file->open(openMode))
    {
        LOG_WARNING(file->fileName() + "文件打开失败");
        return false;
    }

    LOG_DEBUG(file->fileName() + "文件打开成功");
    return true;
}

bool FileUtilities::isFileExist(QFile file)
{
    return file.exists();
}

bool FileUtilities::dirCreat(QString DirPath)
{
    if(!QDir().mkpath(DirPath))
    {
        LOG_WARNING(DirPath + "文件夹路径创建失败");
        return false;
    }

    LOG_DEBUG(DirPath + "文件夹路径创建成功");
    return true;
}
