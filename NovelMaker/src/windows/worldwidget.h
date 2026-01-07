#ifndef WORLDWIDGET_H
#define WORLDWIDGET_H

#include "widgetbase.h"
#include <QWidget>

namespace Ui {
class WorldWidget;
}

class WorldWidget : public WidgetBase
{
    Q_OBJECT

public:
    explicit WorldWidget(QWidget *parent = nullptr);
    ~WorldWidget();

public slots:
    void needInitialize();

private:
    Ui::WorldWidget *ui;
};

#endif // WORLDWIDGET_H
