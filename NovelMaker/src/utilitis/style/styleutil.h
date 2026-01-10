#ifndef STYLEUTIL_H
#define STYLEUTIL_H

#include <QFile>
#include <QObject>

class StyleUtil
{
public:
    StyleUtil(QString stylePreDir, QString styleDir, QString styleName);

    bool preProcess(QMap<QString, QString> styleKey);

    bool merger();

    QStringList getFileList();
    QString getStyle();

private:
    QFile m_styleFile;
    QStringList m_styleFileList;
    bool m_isInitialize;
    QString m_stylePreDir;
    QString m_styleDir;
    QString m_styleName;
};

#endif // STYLEUTIL_H
