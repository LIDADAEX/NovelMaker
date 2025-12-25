#ifndef QSSPREPROCESSOR_H
#define QSSPREPROCESSOR_H

#include <QDir>
#include <QMap>
#include <QObject>

class QssPreProcessor : public QObject
{
    Q_OBJECT
public:
    explicit QssPreProcessor(QObject *parent = nullptr);
    explicit QssPreProcessor(QString styleFilePath, QObject *parent = nullptr);
    explicit QssPreProcessor(QDir stylePath, QObject *parent = nullptr);

    void pathInit(void);

    void setStyleFilePath(QString styleFilePath);
    void setStylePath(QDir stylePath);

    void startFilePreProcess(QMap<QString, QString> defineKey);
    void startDirPreProcess(QMap<QString, QString> defineKey);

private:
    QString m_styleFilePath;
    QDir m_stylePath;
signals:
};

#endif // QSSPREPROCESSOR_H
