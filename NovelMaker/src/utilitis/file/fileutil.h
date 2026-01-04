#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QFile>

class FileUtil
{
public:

    /**************************************
     * 函数名：fileOpen
     * 作用：用来以给定的方式打开文件
     * 返回值：bool，用来说明文件是否正常打开
     * 形参：
     * file：QFile&，待打开为文件。注意，函数并没有检查文件是否已经打开，请在打开前关闭文件
     * openMode：QIODeviceBase::OpenModeFlag， 文件的打开方式
     **************************************/
    [[nodiscard("别忘记检查文件是否打开")]]
    static bool fileOpen(QFile& file, QIODeviceBase::OpenModeFlag openMode);

    /**************************************
     * 函数名：isFileExist
     * 作用：判断文件是否存在
     * 返回值：bool，用来说明文件是否存在
     * 形参：
     * file：QFile&，待打开为文件
     **************************************/
    static bool isFileExist(QFile& file);

    /**************************************
     * 函数名：removeFile
     * 作用：移除文件
     * 返回值：bool，用来说明是否正常移除文件
     * 形参：
     * file：QFile&，待打开为文件
     **************************************/
    static bool removeFile(QFile& file);

    /**************************************
     * 函数名：dirCreat
     * 作用：创建文件夹，无论文件夹是否存在，存在则不创建，不存在则创建
     * 返回值：bool，用来说明是否正常创建文件夹，如果是已存在则也为真
     * 形参：
     * DirPath：QString，待创建的文件夹路径
     **************************************/
    [[nodiscard("别忘记检查文件夹是否创建")]]
    static bool dirCreat(QString DirPath);
};

#endif // FILEUTIL_H
