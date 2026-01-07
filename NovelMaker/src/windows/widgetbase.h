#ifndef WIDGETBASE_H
#define WIDGETBASE_H

#include "src/windows/enumlistwidget.h"
#include <QWidget>

class WidgetBase : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetBase(QWidget *parent = nullptr);

public slots:
    virtual void needInitialize() = 0;

signals:
    void requireChangeWidget(WidgetList targetWidget);
};

#endif // WIDGETBASE_H
