#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "src/utilitis/style/stylemanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_presentWidget = WidgetList::mainWidget;
    m_lastWidget = WidgetList::mainWidget;

    m_mainWidget = new MainWidget(this);
    connect(m_mainWidget, &WidgetBase::requireChangeWidget, this, &MainWindow::changeWidget);

    m_settingWidget = new SettingWidget(this);
    connect(m_settingWidget, &WidgetBase::requireChangeWidget, this, &MainWindow::changeWidget);

    m_characterWidget = new CharacterWidget(this);
    connect(m_characterWidget, &WidgetBase::requireChangeWidget, this, &MainWindow::changeWidget);

    m_worldWidget = new WorldWidget(this);
    connect(m_worldWidget, &WidgetBase::requireChangeWidget, this, &MainWindow::changeWidget);

    ui->stackedWidget->addWidget(m_mainWidget);
    ui->stackedWidget->addWidget(m_settingWidget);
    ui->stackedWidget->addWidget(m_characterWidget);
    ui->stackedWidget->addWidget(m_worldWidget);

    StyleManager::instance().initialize();
}

MainWindow::~MainWindow()
{
    delete m_mainWidget;
    delete m_settingWidget;
    delete m_characterWidget;
    delete m_worldWidget;

    delete ui;
}

void MainWindow::changeWidget(WidgetList targetWidget)
{
    if(targetWidget != m_presentWidget)
    {
        ui->stackedWidget->setCurrentIndex(quint16(targetWidget));
        static_cast<WidgetBase*>(ui->stackedWidget->currentWidget())->needInitialize();
        m_lastWidget = m_presentWidget;
        m_presentWidget = targetWidget;
    }
}
