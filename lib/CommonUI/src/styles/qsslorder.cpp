#include <styles/qsslorder.h>

CommonUI::QssLorder::QssLorder(QString styleFilePath, QObject *parent)
    :m_styleFilePath(styleFilePath), QObject{parent}
{}

bool CommonUI::QssLorder::isExistStyle()
{
    QFile styleFile(m_styleFilePath);
    return styleFile.exists();
}

void CommonUI::QssLorder::lordStyle()
{
    QFile styleFile(m_styleFilePath);

    if(!styleFile.exists())
    {
        qWarning() << "在给定的路径 " + m_styleFilePath + " 下未找到Qss样式表";
        return;
    }

    if(!styleFile.open(QIODeviceBase::ReadOnly))
    {
        qWarning() << "在给定的路径 " + m_styleFilePath + " 无法打开Qss样式表";
        return;
    }

    qInfo() << "样式表已应用！";
    QString styleSheet = styleFile.readAll();
    qApp->setStyleSheet(styleSheet);

    styleFile.close();
}
