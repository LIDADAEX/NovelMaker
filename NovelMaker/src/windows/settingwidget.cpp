#include "settingwidget.h"
#include "src/utilitis/style/stylemanager.h"
#include "ui_settingwidget.h"

#include "src/utilitis/config/configuser.h"
#include "src/utilitis/config/configsystem.h"

SettingWidget::SettingWidget(QWidget *parent)
    : WidgetBase(parent)
    , ui(new Ui::SettingWidget)
{
    ui->setupUi(this);

    connect(ui->pushButton_NT_Font_Add, &QPushButton::clicked, this, [=]{
        QString fontString = ui->lineEdit_NT_Font->text();
        if(!fontString.isEmpty())
            fontString += ',';
        if(fontString.contains(ui->FontCB_NT->currentText())) return;
        fontString += ui->FontCB_NT->currentText();
        ui->lineEdit_NT_Font->setText(fontString);
    });

    connect(ui->pushButton_NT_Font_Delete, &QPushButton::clicked, this, [=]{
        QString fontString = ui->lineEdit_NT_Font->text();
        if(fontString.isEmpty()) return;
        qint16 index = fontString.indexOf(',');
        if(index == -1)
            ui->lineEdit_NT_Font->clear();
        else
            ui->lineEdit_NT_Font->setText(fontString.mid(index + 1));
    });

    connect(ui->checkBox_NT_Dark, &QCheckBox::clicked, ui->checkBox_NT_Light, [=](bool checked){ui->checkBox_NT_Light->setChecked(!checked);});
    connect(ui->checkBox_NT_Light, &QCheckBox::clicked, ui->checkBox_NT_Dark, [=](bool checked){ui->checkBox_NT_Dark->setChecked(!checked);});

    connect(ui->pushButton_ApplyPage, &QPushButton::clicked, this, [=]{
        saveSetting(static_cast<SettingList>(ui->TabW_Main->currentIndex()));
    });

    connect(ui->pushButton_Apply, &QPushButton::clicked, this, [=]{
        saveSetting();
    });

    connect(ui->pushButton_ResetPage, &QPushButton::clicked, this, [=]{
        resetSetting(static_cast<SettingList>(ui->TabW_Main->currentIndex()));
    });

    connect(ui->pushButton_Reset, &QPushButton::clicked, this, [=]{
        resetSetting();
    });

    connect(ui->pushButton_CancelPage, &QPushButton::clicked, this, [=]{
        cancelModify(static_cast<SettingList>(ui->TabW_Main->currentIndex()));
    });

    connect(ui->pushButton_Cancel, &QPushButton::clicked, this, [=]{
        cancelModify();
    });

    connect(ui->pushButton_Confirm, &QPushButton::clicked, this, [=]{emit requireChangeWidget(WidgetList::mainWidget);});
}

SettingWidget::~SettingWidget()
{
    delete ui;
}

void SettingWidget::needInitialize()
{
    cancelModify();
}

void SettingWidget::saveSetting(SettingList settingPage)
{
    auto& editor = ConfigUser::instance().m_editor;
    switch(settingPage)
    {
    case Normal:
        editor.m_fontFamilies = ui->lineEdit_NT_Font->text().split(',');
        editor.m_fontSize = ui->spinBox_NT_FontSize->value();
        editor.m_fontWeight = ui->spinBox_NT_FontWeight->value();
        editor.m_islightStyle = ui->checkBox_NT_Light->isChecked();
        editor.m_fontLineHeight = ui->doubleSpinBox_NT_FontHight->value();
        StyleManager::instance().lordStyle();
        break;
    case Special:
        break;
    }
    ConfigUser::instance().saveFile();
}

void SettingWidget::saveSetting()
{
    auto& editor = ConfigUser::instance().m_editor;
    editor.m_fontFamilies = ui->lineEdit_NT_Font->text().split(',');
    editor.m_fontSize = ui->spinBox_NT_FontSize->value();
    editor.m_fontWeight = ui->spinBox_NT_FontWeight->value();
    editor.m_islightStyle = ui->checkBox_NT_Light->isChecked();
    editor.m_fontLineHeight = ui->doubleSpinBox_NT_FontHight->value();
    ConfigUser::instance().saveFile();
    StyleManager::instance().lordStyle();
}

void SettingWidget::resetSetting(SettingList settingPage)
{
    auto& editor = ConfigSystem::instance().m_editorDefault;

    switch(settingPage)
    {
    case Normal:
    {
        QString fontFamiliesString;
        for(auto i = editor.m_fontFamilies.begin(); i != editor.m_fontFamilies.end(); i ++)
        {
            fontFamiliesString += *i;
            if(i != editor.m_fontFamilies.end() - 1) fontFamiliesString += ',';
        }

        ui->lineEdit_NT_Font->setText(fontFamiliesString);
        ui->spinBox_NT_FontSize->setValue(editor.m_fontSize);
        ui->spinBox_NT_FontWeight->setValue(editor.m_fontWeight);
        ui->checkBox_NT_Light->clicked(editor.m_islightStyle);
        ui->checkBox_NT_Dark->clicked(!editor.m_islightStyle);
        ui->doubleSpinBox_NT_FontHight->setValue(editor.m_fontLineHeight);
        break;
    }
    case Special:
    {
        break;
    }
    }
}

void SettingWidget::resetSetting()
{
    auto& editor = ConfigSystem::instance().m_editorDefault;

    QString fontFamiliesString;
    for(auto i = editor.m_fontFamilies.begin(); i != editor.m_fontFamilies.end(); i ++)
    {
        fontFamiliesString += *i;
        if(i != editor.m_fontFamilies.end() - 1) fontFamiliesString += ',';
    }

    ui->lineEdit_NT_Font->setText(fontFamiliesString);
    ui->spinBox_NT_FontSize->setValue(editor.m_fontSize);
    ui->spinBox_NT_FontWeight->setValue(editor.m_fontWeight);
    ui->checkBox_NT_Light->clicked(editor.m_islightStyle);
    ui->checkBox_NT_Dark->clicked(!editor.m_islightStyle);
    ui->doubleSpinBox_NT_FontHight->setValue(editor.m_fontLineHeight);
}

void SettingWidget::cancelModify(SettingList settingPage)
{
    auto& editor = ConfigUser::instance().m_editor;

    switch(settingPage)
    {
    case Normal:
    {
        QString fontFamiliesString;
        for(auto i = editor.m_fontFamilies.begin(); i != editor.m_fontFamilies.end(); i ++)
        {
            fontFamiliesString += *i;
            if(i != editor.m_fontFamilies.end() - 1) fontFamiliesString += ',';
        }

        ui->lineEdit_NT_Font->setText(fontFamiliesString);
        ui->spinBox_NT_FontSize->setValue(editor.m_fontSize);
        ui->spinBox_NT_FontWeight->setValue(editor.m_fontWeight);
        ui->checkBox_NT_Light->clicked(editor.m_islightStyle);
        ui->checkBox_NT_Dark->clicked(!editor.m_islightStyle);
        ui->doubleSpinBox_NT_FontHight->setValue(editor.m_fontLineHeight);
        break;
    }
    case Special:
        break;
    }
}

void SettingWidget::cancelModify()
{
    auto& editor = ConfigUser::instance().m_editor;

    QString fontFamiliesString;
    for(auto i = editor.m_fontFamilies.begin(); i != editor.m_fontFamilies.end(); i ++)
    {
        fontFamiliesString += *i;
        if(i != editor.m_fontFamilies.end() - 1) fontFamiliesString += ',';
    }

    ui->lineEdit_NT_Font->setText(fontFamiliesString);
    ui->spinBox_NT_FontSize->setValue(editor.m_fontSize);
    ui->spinBox_NT_FontWeight->setValue(editor.m_fontWeight);
    ui->checkBox_NT_Light->clicked(editor.m_islightStyle);
    ui->checkBox_NT_Dark->clicked(!editor.m_islightStyle);
    ui->doubleSpinBox_NT_FontHight->setValue(editor.m_fontLineHeight);
}
