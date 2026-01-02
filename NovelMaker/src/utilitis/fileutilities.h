#ifndef FILEUTILITIES_H
#define FILEUTILITIES_H

#include <QFile>

class FileUtilities
{
public:
    static bool fileOpen(QFile* file, QIODeviceBase::OpenModeFlag openMode);
    static bool isFileExist(QFile file);
    static bool dirCreat(QString DirPath);
};

#endif // FILEUTILITIES_H
