#include <styles/qssmerger.h>

CommonUI::QssMerger::QssMerger(QObject *parent)
    :m_styleFileWatcher(nullptr), m_outputFileName("style"), QObject{parent}
{
    classCommonInit();
}

CommonUI::QssMerger::QssMerger(QString styleDir, QString outputFileName, QObject *parent)
    :m_styleFileWatcher(nullptr), m_styleDir(styleDir), m_outputFileName(outputFileName),  QObject{parent}
{
    classCommonInit();
}

CommonUI::QssMerger::QssMerger(QDir styleDir, QString outputFileName, QObject *parent)
    :m_styleFileWatcher(nullptr), m_styleDir(styleDir), m_outputFileName(outputFileName), QObject{parent}
{
    classCommonInit();
}

void CommonUI::QssMerger::classCommonInit()
{
    m_styleDir.setFilter(QDir::Files);
    m_styleDir.setNameFilters(QStringList("*.qss"));
    m_styleDir.setSorting(QDir::Name);
}

void CommonUI::QssMerger::setStyleDir(QString styleDir)
{
    m_styleDir = styleDir;
}

void CommonUI::QssMerger::setStyleDir(QDir styleDir)
{
    m_styleDir = styleDir;
}

void CommonUI::QssMerger::setOutputFileName(QString outputFileName)
{
    m_outputFileName = outputFileName;
}

bool CommonUI::QssMerger::isEmptyStyle()
{
    QStringList styleFileList;

    styleFileList = m_styleDir.entryList();

    if(styleFileList.empty())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CommonUI::QssMerger::outputMergeFile()
{
    QStringList styleFileList;

    styleFileList = m_styleDir.entryList();

    qint16 margeFileIndex = styleFileList.indexOf(m_outputFileName + ".qss");
    if(margeFileIndex != -1) styleFileList.removeAt(margeFileIndex);

    if(styleFileList.empty())
    {
        qWarning() << "在执行Qss文件合并过程中，发现待合并的文件数为零或路径不存在，合并终止！";
        return;
    }

    QFile margeFile;
    QFile sourceFile;

    margeFile.setFileName(m_styleDir.absolutePath() + '/' + m_outputFileName + ".qss");
    if(!margeFile.open(QIODeviceBase::WriteOnly))
    {
        qWarning() << "在执行Qss文件合并过程中，发现合并文件不能正常打开或新建，合并终止！";
        return;
    }

    foreach (auto i, styleFileList) {

        sourceFile.setFileName(m_styleDir.absolutePath() + '/' + i);

        if(!sourceFile.open(QIODeviceBase::ReadOnly))
        {
            qWarning() << "在执行Qss文件合并过程中，发现待合并文件不能正常打开，合并终止！";
            return;
        }
        else
        {
            margeFile.write(sourceFile.readAll() + '\n');
        }

        sourceFile.close();
    }

    sourceFile.close();
    margeFile.close();
}

void CommonUI::QssMerger::outputMergeFileAlways()
{
    QStringList styleFileList;

    styleFileList = m_styleDir.entryList();

    qint16 margeFileIndex = styleFileList.indexOf(m_outputFileName + ".qss");
    if(margeFileIndex != -1) styleFileList.removeAt(margeFileIndex);

    for(auto i = styleFileList.begin(); i != styleFileList.end(); i++)
    {
        *i = m_styleDir.absolutePath() + '/' + *i;
    }

    if(styleFileList.empty())
    {
        qWarning() << "在执行Qss文件合并过程中，发现待合并的文件数为零或路径不存在，合并终止！";
        return;
    }

    QFile margeFile;
    QFile sourceFile;

    margeFile.setFileName(m_styleDir.absolutePath() + '/' + m_outputFileName + ".qss");

    if(!margeFile.open(QIODeviceBase::WriteOnly))
    {
        qWarning() << "在执行Qss文件合并过程中，发现合并文件不能正常打开或新建，合并终止！";
        return;
    }

    foreach (auto i, styleFileList) {

        sourceFile.setFileName(i);

        if(!sourceFile.open(QIODeviceBase::ReadOnly))
        {
            qWarning() << "在执行Qss文件合并过程中，发现待合并文件不能正常打开，合并终止！";
            return;
        }
        else
        {
            margeFile.write(sourceFile.readAll() + '\n');
        }

        sourceFile.close();
    }

    sourceFile.close();
    margeFile.close();

    qInfo() << "总Qss文件已合成修改！";

    emit styleMerged();

    if(m_styleFileWatcher != nullptr) m_styleFileWatcher->deleteLater();

    m_styleFileWatcher = new QFileSystemWatcher;

    m_styleFileWatcher->addPaths(styleFileList);

    connect(m_styleFileWatcher, &QFileSystemWatcher::fileChanged, this, &QssMerger::outputMergeFileAlways);
}

void CommonUI::QssMerger::outputMergeFileStop()
{
    if(m_styleFileWatcher != nullptr)
    {
        m_styleFileWatcher->deleteLater();
        m_styleFileWatcher = nullptr;
    }
}
