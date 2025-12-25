#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_presentWidget = widget::mainWidget;
    m_lastWidget = widget::mainWidget;

    m_mainWidget = new MainWidget(this);
    connect(m_mainWidget, &MainWidget::requireChangeWidget, this, &MainWindow::changeWidget);

    m_settingWidget = new SettingWidget(this);
    connect(m_settingWidget, &SettingWidget::requireChangeWidget, this, &MainWindow::changeWidget);

    ui->stackedWidget->addWidget(m_mainWidget);
    ui->stackedWidget->addWidget(m_settingWidget);

    // m_qssManager = new CommonUI::QssManager("./styles/styleDark");
    // m_qssManager->dynamicStyleMergeLordStart();
}

MainWindow::~MainWindow()
{
    delete m_mainWidget;

    delete ui;
}

void MainWindow::changeWidget(widget targetWidget)
{
    if(targetWidget != m_presentWidget)
    {
        ui->stackedWidget->setCurrentIndex(static_cast<quint16>(targetWidget));
        m_lastWidget = m_presentWidget;
        m_presentWidget = targetWidget;
    }
}
