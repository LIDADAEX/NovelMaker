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

    void startPreProcess(void);

private:
    QString m_styleFilePath;
    QDir m_stylePath;
signals:
};

#endif // QSSPREPROCESSOR_H
