#include "worldwidget.h"
#include "ui_worldwidget.h"

WorldWidget::WorldWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WorldWidget)
{
    ui->setupUi(this);
}

WorldWidget::~WorldWidget()
{
    delete ui;
}
