#include "characterwidget.h"
#include "ui_characterwidget.h"

CharacterWidget::CharacterWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CharacterWidget)
{
    ui->setupUi(this);
}

CharacterWidget::~CharacterWidget()
{
    delete ui;
}
