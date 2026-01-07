#include "worldwidget.h"
#include "ui_worldwidget.h"

WorldWidget::WorldWidget(QWidget *parent)
    : WidgetBase(parent)
    , ui(new Ui::WorldWidget)
{
    ui->setupUi(this);
}

WorldWidget::~WorldWidget()
{
    delete ui;
}

void WorldWidget::needInitialize()
{

}
