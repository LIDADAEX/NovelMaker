#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : WidgetBase(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    connect(ui->pushButton_PT_Characters, &QPushButton::clicked, this, [=]{emit requireChangeWidget(WidgetList::characterWidget);});
    connect(ui->pushButton_PT_World, &QPushButton::clicked, this, [=]{emit requireChangeWidget(WidgetList::worldWidget);});
    connect(ui->pushButton_ET_EditorSetting, &QPushButton::clicked, this, [=]{emit requireChangeWidget(WidgetList::settingWidget);});
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::needInitialize()
{

}
