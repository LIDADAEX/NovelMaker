#ifndef QSSLORDER_H
#define QSSLORDER_H

#include <QDir>
#include <QObject>
#include <QFileSystemWatcher>
#include <QApplication>

namespace CommonUI {
    class QssLorder : public QObject
    {
        Q_OBJECT
    public:
        explicit QssLorder(QString styleFilePath, QObject *parent = nullptr);

        bool isExistStyle(void);

    public slots:
        void lordStyle(void);

    private:
        QString m_styleFilePath;

    signals:
    };
}

#endif // QSSLORDER_H
