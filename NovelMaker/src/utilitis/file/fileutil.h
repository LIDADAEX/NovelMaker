#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QFile>

class FileUtil
{
public:
    [[nodiscard("别忘记检查文件是否打开")]]
    static bool fileOpen(QFile& file, QIODeviceBase::OpenModeFlag openMode);

    static bool isFileExist(QFile& file);
    static bool removeFile(QFile& file);

    [[nodiscard("别忘记检查文件夹是否创建")]]
    static bool dirCreat(QString DirPath);
};

#endif // FILEUTIL_H
