#ifndef WORLDWIDGET_H
#define WORLDWIDGET_H

#include <QWidget>

namespace Ui {
class WorldWidget;
}

class WorldWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WorldWidget(QWidget *parent = nullptr);
    ~WorldWidget();

private:
    Ui::WorldWidget *ui;
};

#endif // WORLDWIDGET_H
