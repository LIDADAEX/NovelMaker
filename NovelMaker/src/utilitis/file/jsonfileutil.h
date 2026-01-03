#ifndef JSONFILEUTIL_H
#define JSONFILEUTIL_H

#include <QFile>
#include <QJsonDocument>

class JsonFileUtil
{
public:
    static QJsonDocument readJsonDocument(QFile& file, bool& readError);
    static bool writeJsonDocument(QFile& file, QJsonDocument& jsonDocument);
    static bool appendJsonDocument(QFile& file, QJsonDocument& jsonDocument);
};

#endif // JSONFILEUTIL_H
