#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "characterwidget.h"
#include "mainwidget.h"
#include "settingwidget.h"
#include "worldwidget.h"

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
    void changeWidget(WidgetList targetWidget);

private:
    Ui::MainWindow *ui;

    WidgetList m_presentWidget;
    WidgetList m_lastWidget;

    MainWidget* m_mainWidget;
    SettingWidget* m_settingWidget;
    CharacterWidget* m_characterWidget;
    WorldWidget* m_worldWidget;
};
#endif // MAINWINDOW_H
