#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include "widgetbase.h"
#include <QWidget>

namespace Ui {
class SettingWidget;
}

class SettingWidget : public WidgetBase
{
    Q_OBJECT

public:
    explicit SettingWidget(QWidget *parent = nullptr);
    ~SettingWidget();

public slots:
    void needInitialize();

private:
    enum SettingList : quint16{
        Normal,
        Special
    };

    Ui::SettingWidget *ui;

    void saveSetting(SettingList settingPage);
    void saveSetting();
    void resetSetting(SettingList settingPage);
    void resetSetting();
    void cancelModify(SettingList settingPage);
    void cancelModify();
};

#endif // SETTINGWIDGET_H
