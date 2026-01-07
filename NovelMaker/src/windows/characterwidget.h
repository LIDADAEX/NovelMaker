#ifndef CHARACTERWIDGET_H
#define CHARACTERWIDGET_H

#include "widgetbase.h"
#include <QWidget>

namespace Ui {
class CharacterWidget;
}

class CharacterWidget : public WidgetBase
{
    Q_OBJECT

public:
    explicit CharacterWidget(QWidget *parent = nullptr);
    ~CharacterWidget();

public slots:
    void needInitialize();

private:
    Ui::CharacterWidget *ui;
};

#endif // CHARACTERWIDGET_H
