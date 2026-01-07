#include "settingwidget.h"
#include "ui_settingwidget.h"

SettingWidget::SettingWidget(QWidget *parent)
    : WidgetBase(parent)
    , ui(new Ui::SettingWidget)
{
    ui->setupUi(this);
}

SettingWidget::~SettingWidget()
{
    delete ui;
}

void SettingWidget::needInitialize()
{

}
