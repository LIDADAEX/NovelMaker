#ifndef JSONFILEUTIL_H
#define JSONFILEUTIL_H

#include <QFile>
#include <QJsonDocument>

class JsonFileUtil
{
public:

    /**
     * @brief           读取json文件
     * 读取失败时返回QJsonDocument()
     * @param file      待打开的文件
     * @param readError 读取错误标志
     */
    static QJsonDocument readJsonDocument(QFile& file, bool& readError);

    /**
     * @brief               写json文件
     * @param file          待打开的文件
     * @param jsonDocument  待写入的Json文档
     */
    static bool writeJsonDocument(QFile& file, QJsonDocument& jsonDocument);

    /**
     * @brief               追加写json文件
     * @param file          待打开的文件
     * @param jsonDocument  待写入的Json文档
     */
    static bool appendJsonDocument(QFile& file, QJsonDocument& jsonDocument);
};

#endif // JSONFILEUTIL_H
