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
    Ui::SettingWidget *ui;
};

#endif // SETTINGWIDGET_H
