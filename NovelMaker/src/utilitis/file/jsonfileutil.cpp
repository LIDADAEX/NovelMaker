#include "jsonfileutil.h"

#include "src/utilitis/file/fileutil.h"
#include "src/core/logger.h"

QJsonDocument JsonFileUtil::readJsonDocument(QFile& file, bool& readError)
{
    QJsonDocument jsonDocument;
    QJsonParseError jsonParseError;

    if(!FileUtil::fileOpen(file, QIODeviceBase::ReadOnly))
    {
        LOG_INFO("json文件打开失败");
        readError = true;
        return QJsonDocument();
    }

    jsonDocument = QJsonDocument::fromJson(file.readAll(), &jsonParseError);
    file.close();

    if(jsonParseError.error != QJsonParseError::NoError)
    {
        LOG_INFO("json文件解析失败");
        readError = true;
        return QJsonDocument();
    }

    LOG_INFO("json文件解析成功");
    return jsonDocument;
}

bool JsonFileUtil::writeJsonDocument(QFile& file, QJsonDocument& jsonDocument)
{
    if(!FileUtil::fileOpen(file, QIODeviceBase::WriteOnly))
    {
        LOG_INFO("json文件打开失败");
        return false;
    }

    file.write(jsonDocument.toJson());
    file.close();

    LOG_INFO("json文件写入成功");
    return true;
}

bool JsonFileUtil::appendJsonDocument(QFile& file, QJsonDocument &jsonDocument)
{
    if(!FileUtil::fileOpen(file, QIODeviceBase::Append))
    {
        LOG_INFO("json文件打开失败");
        return false;
    }

    file.write(jsonDocument.toJson());
    file.close();

    LOG_INFO("json文件写入成功");
    return true;
}
