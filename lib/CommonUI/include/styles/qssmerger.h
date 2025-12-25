#ifndef QSSMERGER_H
#define QSSMERGER_H

#include <QDir>
#include <QFileSystemWatcher>
#include <QObject>

namespace CommonUI {
    class QssMerger : public QObject
    {
        Q_OBJECT
    public:
        explicit QssMerger(QObject *parent = nullptr);
        explicit QssMerger(QString styleDir, QString outputFileName = QString("style"), QObject *parent = nullptr);
        explicit QssMerger(QDir styleDir, QString outputFileName = QString("style"), QObject *parent = nullptr);

        void classCommonInit(void);

        void setStyleDir(QString styleDir);
        void setStyleDir(QDir styleDir);

        void setOutputFileName(QString outputFileName);

        bool isEmptyStyle(void);

    public slots:
        void outputMergeFile(void);
        void outputMergeFileAlways(void);
        void outputMergeFileStop(void);

    private:
        QDir m_styleDir;
        QString m_outputFileName;
        QFileSystemWatcher* m_styleFileWatcher;
    signals:
        void styleMerged(void);
    };
}

#endif // QSSMERGER_H
