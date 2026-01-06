#include "jsonfileutil.h"

#include "src/utilitis/file/fileutil.h"
#include "src/core/logger.h"
#include <QFileInfo>


QJsonDocument JsonFileUtil::readJsonDocument(QFile& file, bool& readError)
{
    QJsonDocument jsonDocument;
    QJsonParseError jsonParseError;

    readError = false;

    if(!FileUtil::fileOpen(file, QIODeviceBase::ReadOnly))
    {
        LOG_WARNING(QString("json文件 %1 打开失败").arg(file.fileName()));
        readError = true;
        return QJsonDocument();
    }

    jsonDocument = QJsonDocument::fromJson(file.readAll(), &jsonParseError);
    file.close();

    if(jsonParseError.error != QJsonParseError::NoError)
    {
        LOG_WARNING(QString("json文件 %1 解析失败").arg(file.fileName()));
        readError = true;
        return QJsonDocument();
    }

    return jsonDocument;
}


bool JsonFileUtil::writeJsonDocument(QFile& file, QJsonDocument& jsonDocument)
{
    if(!FileUtil::fileOpen(file, QIODeviceBase::WriteOnly))
    {
        LOG_WARNING(QString("json文件 %1 打开失败").arg(file.fileName()));
        return false;
    }

    file.write(jsonDocument.toJson());
    file.close();

    return true;
}


bool JsonFileUtil::appendJsonDocument(QFile& file, QJsonDocument &jsonDocument)
{
    if(!FileUtil::fileOpen(file, QIODeviceBase::WriteOnly | QIODeviceBase::Append))
    {
        LOG_WARNING(QString("json文件 %1 打开失败").arg(file.fileName()));
        return false;
    }

    file.write(jsonDocument.toJson());
    file.close();
    return true;
}
