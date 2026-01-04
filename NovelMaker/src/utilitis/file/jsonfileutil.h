#ifndef JSONFILEUTIL_H
#define JSONFILEUTIL_H

#include <QFile>
#include <QJsonDocument>

class JsonFileUtil
{
public:
    /**************************************
     * 函数名：readJsonDocument
     * 作用：读取json文件
     * 返回值：QJsonDocument，返回从文件中读取的jsonDocument，
     * 当读取失败时返回QJsonDocument()
     * 形参：
     * file：QFile&，待打开的文件
     * readError:bool&，读取错误标志
     **************************************/
    static QJsonDocument readJsonDocument(QFile& file, bool& readError);

    /**************************************
     * 函数名：writeJsonDocument
     * 作用：写json文件
     * 返回值：bool，用来说明是否写入成功
     * 形参：
     * file：QFile&，待打开的文件
     * jsonDocument:QJsonDocument&，待写入的Json文档
     **************************************/
    static bool writeJsonDocument(QFile& file, QJsonDocument& jsonDocument);

    /**************************************
     * 函数名：appendJsonDocument
     * 作用：追加写json文件
     * 返回值：bool，用来说明是否写入成功
     * 形参：
     * file：QFile&，待打开的文件
     * jsonDocument:QJsonDocument&，待写入的Json文档
     **************************************/
    static bool appendJsonDocument(QFile& file, QJsonDocument& jsonDocument);
};

#endif // JSONFILEUTIL_H
