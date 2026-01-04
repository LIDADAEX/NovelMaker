#include "jsonfileutil.h"

#include "src/utilitis/file/fileutil.h"
#include "src/core/logger.h"


QJsonDocument JsonFileUtil::readJsonDocument(QFile& file, bool& readError)
{
    QJsonDocument jsonDocument;
    QJsonParseError jsonParseError;

    readError = false;

    //打开文件
    if(!FileUtil::fileOpen(file, QIODeviceBase::ReadOnly))
    {
        LOG_INFO("json文件打开失败");
        readError = true;
        return QJsonDocument();
    }

    //读取文件，注意jsonParseError
    jsonDocument = QJsonDocument::fromJson(file.readAll(), &jsonParseError);
    file.close();

    //判断是否出错
    if(jsonParseError.error != QJsonParseError::NoError)
    {
        LOG_INFO("json文件解析失败");
        readError = true;
        return QJsonDocument();
    }

    //没有出错则返回
    LOG_INFO("json文件解析成功");
    return jsonDocument;
}


bool JsonFileUtil::writeJsonDocument(QFile& file, QJsonDocument& jsonDocument)
{
    //打开文件
    if(!FileUtil::fileOpen(file, QIODeviceBase::WriteOnly))
    {
        LOG_INFO("json文件打开失败");
        return false;
    }

    //写入文件
    file.write(jsonDocument.toJson());
    file.close();

    LOG_INFO("json文件写入成功");
    return true;
}


bool JsonFileUtil::appendJsonDocument(QFile& file, QJsonDocument &jsonDocument)
{
    //打开文件
    if(!FileUtil::fileOpen(file, QIODeviceBase::Append))
    {
        LOG_INFO("json文件打开失败");
        return false;
    }

    //追加写文件
    file.write(jsonDocument.toJson());
    file.close();

    LOG_INFO("json文件写入成功");
    return true;
}
