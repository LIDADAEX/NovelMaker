#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    connect(ui->pushButton_ET_EditorSetting, &QPushButton::clicked, this, [=]{emit requireChangeWidget(widget::settingWidget);});
}

MainWidget::~MainWidget()
{
    delete ui;
}
