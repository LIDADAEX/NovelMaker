#ifndef QSSMANAGER_H
#define QSSMANAGER_H

#include "qsslorder.h"
#include "qssmerger.h"

#include <QDir>
#include <QObject>

namespace CommonUI {
    class QssManager : public QObject
    {
        Q_OBJECT
    public:
        explicit QssManager(QObject *parent = nullptr);
        explicit QssManager(QString styleDir, QString outputFileName = QString("style"), QObject *parent = nullptr);
        explicit QssManager(QDir styleDir, QString outputFileName = QString("style"), QObject *parent = nullptr);

        void styleMergeLord(void);
        void dynamicStyleMergeLordStart(void);
        void dynamicStyleMergeLordStop(void);

        void setStyleDir(QString styleDir, QString outputFileName = QString("style"));
        void setStyleDir(QDir styleDir, QString outputFileName = QString("style"));

    private:
        QssLorder* m_lorder;
        QssMerger* m_merger;

    signals:
    };
}

#endif // QSSMANAGER_H
