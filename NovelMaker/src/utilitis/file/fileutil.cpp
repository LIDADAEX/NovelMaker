#include "fileutil.h"
#include "src/core/logger.h"

#include <QDir>

bool FileUtil::fileOpen(QFile& file, QIODeviceBase::OpenModeFlag openMode)
{
    if(!file.open(openMode))
    {
        LOG_WARNING(file.fileName() + "文件打开失败");
        return false;
    }

    LOG_DEBUG(file.fileName() + "文件打开成功");

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
            LOG_WARNING("文件删除失败");
            return false;
        }
        else
        {
            LOG_INFO("文件删除成功");
            return true;
        }
    }
    else
    {
        LOG_INFO("文件不存在");
        return true;
    }
}

bool FileUtil::dirCreat(QString DirPath)
{
    if(!QDir().mkpath(DirPath))
    {
        LOG_WARNING(DirPath + "文件夹路径创建失败");
        return false;
    }

    LOG_DEBUG(DirPath + "文件夹路径创建或检测成功");
    return true;
}
