#include <styles/qssmanager.h>

CommonUI::QssManager::QssManager(QObject *parent)
    :m_lorder(nullptr), m_merger(nullptr), QObject{parent}
{}

CommonUI::QssManager::QssManager(QDir styleDir, QString outputFileName, QObject *parent)
    :m_lorder(new QssLorder(styleDir.absolutePath() + '/' +outputFileName + ".qss",parent)), m_merger(new QssMerger(styleDir, outputFileName, parent)),  QObject{parent}
{
    connect(m_merger, &QssMerger::styleMerged, m_lorder, &QssLorder::lordStyle);
}

void CommonUI::QssManager::styleMergeLord()
{
    if((m_lorder == nullptr) || (m_merger == nullptr))
    {
        qWarning() << "未选择style的目录！";
        return;
    }

    m_merger->outputMergeFile();
}

void CommonUI::QssManager::dynamicStyleMergeLordStart()
{
    if((m_lorder == nullptr) || (m_merger == nullptr))
    {
        qWarning() << "未选择style的目录！";
        return;
    }

    m_merger->outputMergeFileAlways();
}

void CommonUI::QssManager::dynamicStyleMergeLordStop()
{
    m_merger->outputMergeFileStop();
}

void CommonUI::QssManager::setStyleDir(QDir styleDir, QString outputFileName)
{
    if(m_lorder != nullptr)
    {
        m_lorder->deleteLater();
    }

    if(m_merger != nullptr)
    {
        m_merger->deleteLater();
    }

    m_lorder = new QssLorder(styleDir.absolutePath() + '/' +outputFileName + ".qss", this->parent());
    m_merger = new QssMerger(styleDir.absolutePath(), outputFileName, this->parent());
}
