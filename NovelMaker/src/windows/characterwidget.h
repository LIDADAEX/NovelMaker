#ifndef CHARACTERWIDGET_H
#define CHARACTERWIDGET_H

#include <QWidget>

namespace Ui {
class CharacterWidget;
}

class CharacterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CharacterWidget(QWidget *parent = nullptr);
    ~CharacterWidget();

private:
    Ui::CharacterWidget *ui;
};

#endif // CHARACTERWIDGET_H
