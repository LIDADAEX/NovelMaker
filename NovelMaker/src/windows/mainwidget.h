#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "enumlistwidget.h"

#include <QWidget>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;

signals:
    void requireChangeWidget(widget targetWidget);
};

#endif // MAINWIDGET_H
