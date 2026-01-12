#ifndef STYLEMANAGER_H
#define STYLEMANAGER_H

#include "styleutil.h"

#include <QWidget>
#include <QFileSystemWatcher>
#include <QTimer>
#include <QApplication>

/**
 * @brief 样式管理类，单例
 *
 * 必须在窗口加载之后调用initialize()或lordStyle()
 *
 * 通过lordStyle()来应用ConfigUser中的样式变更
 */
class StyleManager : public QObject
{
    Q_OBJECT
public:
    static StyleManager& instance();

    /**
     * @brief 初始化函数，只用于在程序最开始的时候应用样式
     *
     * 之后请使用lordStyle函数
     */
    void initialize();

    /**
     * @brief 动态监测函数，主要用于样式的热重载，在调试阶段很有用
     * @param enable 启动或否
     */
    void DanamicWatcher(bool enable);

    /**
     * @brief 应用样式函数，可以处理样式更改
     *
     * 不会返回是否成功加载
     */
    void lordStyle();

private:
    StyleManager();
    ~StyleManager();

    StyleManager(const StyleManager&) = delete;
    StyleManager& operator=(const StyleManager&) = delete;

    /**
     * @brief 通过预处理样式键值来加载样式
     * @param styleKey 预处理样式键值，可以在styledefine.h中找到
     * @return 初始化是否成功
     */
    bool lordStyle(QMap<QString, QString> styleKey);

    /**
     * @brief 改变style，主要用于在动态监测中避免二次加载而使用的函数，
     *
     * 如果想使用动态检测，请使用这个函数
     * @param styleKey 预处理样式键值，可以在styledefine.h中找到
     * @return 初始化是否成功
     */
    bool changeStyle(QMap<QString, QString> styleKey);

    QFileSystemWatcher m_watcher;       ///<动态文件检测，检测qss文件，不检测qssa预处理文件
    QTimer m_debounceTimer;                     ///<定时器，用于文件防抖，防止因为多次文件改变产生垃圾文件
    bool m_watcherEnableManual;         ///供DanamicWatcher使用的标志

    StyleUtil* m_styleUtil;             ///<样式帮助工具类，用于处理预处理文件和样式文件

signals:
};

#endif // STYLEMANAGER_H
