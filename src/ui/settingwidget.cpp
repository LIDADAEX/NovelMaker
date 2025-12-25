#include "settingwidget.h"
#include "ui_settingwidget.h"

SettingWidget::SettingWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SettingWidget)
{
    ui->setupUi(this);

    connect(ui->pushButton_Cancel, &QPushButton::clicked, this, [=]{emit requireChangeWidget(widget::mainWidget);});

}

SettingWidget::~SettingWidget()
{
    delete ui;
}
