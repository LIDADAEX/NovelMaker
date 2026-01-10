#ifndef STYLEMANAGER_H
#define STYLEMANAGER_H

#include "styleutil.h"

#include <QWidget>
#include <QFileSystemWatcher>
#include <QTimer>
#include <QApplication>

class StyleManager : public QObject
{
    Q_OBJECT
public:
    static StyleManager& instance();

    void initialize();

    void DanamicWatcher(bool enable);

    void lordStyle();

private:
    StyleManager();
    ~StyleManager();

    StyleManager(const StyleManager&) = delete;
    StyleManager& operator=(const StyleManager&) = delete;

    bool lordStyle(QMap<QString, QString> styleKey);
    bool changeStyle(QMap<QString, QString> styleKey);

    QFileSystemWatcher m_watcher;
    QTimer m_timer;
    bool m_watcherEnable;
    bool m_watcherEnableManual;

    StyleUtil* m_styleUtil;

signals:
};

#endif // STYLEMANAGER_H
