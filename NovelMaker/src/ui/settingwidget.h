#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include "src/ui/enumlistwidget.h"
#include <QWidget>

namespace Ui {
class SettingWidget;
}

class SettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWidget(QWidget *parent = nullptr);
    ~SettingWidget();

private:
    Ui::SettingWidget *ui;

signals:
    void requireChangeWidget(widget targetWidget);
};

#endif // SETTINGWIDGET_H
