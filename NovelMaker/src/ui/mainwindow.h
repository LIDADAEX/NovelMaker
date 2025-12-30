#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <styles/qssmanager.h>
#include "mainwidget.h"
#include "settingwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void changeWidget(widget targetWidget);

private:
    QMap<QString, QString> preProcessDefineKeyInit(void);

private:
    Ui::MainWindow *ui;

    widget m_presentWidget;
    widget m_lastWidget;

    CommonUI::QssManager* m_qssManager;

    MainWidget* m_mainWidget;
    SettingWidget* m_settingWidget;
};
#endif // MAINWINDOW_H
