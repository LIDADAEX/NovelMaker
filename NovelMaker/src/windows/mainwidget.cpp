#include "mainwidget.h"
#include "ui_mainwidget.h"

#include "src/utilitis/config/configuser.h"
#include "src/utilitis/project/projectmanager.h"

#include <QFileDialog>




MainWidget::MainWidget(QWidget *parent)
    : WidgetBase(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    connect(ui->pushButton_PT_Characters, &QPushButton::clicked, this, [=]{emit requireChangeWidget(WidgetList::characterWidget);});
    connect(ui->pushButton_PT_World, &QPushButton::clicked, this, [=]{emit requireChangeWidget(WidgetList::worldWidget);});
    connect(ui->pushButton_ET_EditorSetting, &QPushButton::clicked, this, [=]{emit requireChangeWidget(WidgetList::settingWidget);});

    connect(ui->pushButton_ET_CreatProject, &QPushButton::clicked, this, [=]{
        ProjectManager& projectManager = ProjectManager::instance();
        projectManager.creatProject(this);
        ui->label_ReadProject_Text->setText(projectManager.getPrsentProjectName());
    });
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::needInitialize()
{
    ConfigUser::instance().loadFile();
    auto& editor = ConfigUser::instance().m_editor;

    QFont font(editor.m_fontFamilies, editor.m_fontSize, editor.m_fontWeight);

    ui->TextB_Preview->setFont(font);
    ui->TextB_Preview->selectAll();
    ui->TextB_Preview->setCurrentFont(font);

    ui->TextB_Preview->setLineHeight(editor.m_fontLineHeight);
}
