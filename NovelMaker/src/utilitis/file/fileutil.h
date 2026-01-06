#ifndef FILEUTIL_H
#define FILEUTIL_H

#include <QFile>

class FileUtil
{
public:
    /**
     * @brief 用来以给定的方式打开文件
     * @param file 待打开的文件
     * @param openMode 打开方式
     */
    [[nodiscard("别忘记检查文件是否打开")]]
    static bool fileOpen(QFile& file, QFlags<QFile::OpenModeFlag> openMode);

    /**
     * @brief 判断文件是否存在
     * @param file 待打开为文件
     */
    static bool isFileExist(QFile& file);

    /**
     * @brief 移除文件
     *
     * 当文件不存在时也会返回真
     *
     * @param file 待打开为文件
     */
    static bool removeFile(QFile& file);

    /**
     * @brief 创建文件夹，无论文件夹是否存在，存在则不创建，不存在则创建
     * @param DirPath 待创建的文件夹路径
     */
    [[nodiscard("别忘记检查文件夹是否创建")]]
    static bool dirCreat(QString DirPath);
};

#endif // FILEUTIL_H
