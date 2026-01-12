#include "stylemanager.h"

#include "src/core/logger.h"
#include "src/utilitis/config/configsystem.h"
#include "src/utilitis/config/configuser.h"
#include "src/utilitis/style/styledefine.h"


StyleManager::StyleManager()
    : QObject{}
{
    m_watcherEnableManual = false;

    m_debounceTimer.setSingleShot(true);

    connect(&m_debounceTimer, &QTimer::timeout, this, [=]{
        if(m_styleUtil->merger())
        {
            m_watcher.removePaths(m_watcher.files());
            m_watcher.addPaths(m_styleUtil->getFileList());
        }

        QString styleSheet = m_styleUtil->getStyle();

        if(!styleSheet.isEmpty())
            qApp->setStyleSheet(styleSheet);

        LOG_INFO("样式装载成功");
    });
}

StyleManager::~StyleManager()
{
    delete m_styleUtil;
}

StyleManager &StyleManager::instance()
{
    static StyleManager instance;
    return instance;
}

void StyleManager::initialize()
{
    lordStyle();
}

void StyleManager::DanamicWatcher(bool enable)
{
    m_watcherEnableManual = enable;
    if(enable)
    {
        connect(&m_watcher, &QFileSystemWatcher::fileChanged, this, [=](QString filePath){
            m_debounceTimer.start(100);
        });
    }
    else
    {
        disconnect(&m_watcher, &QFileSystemWatcher::fileChanged, this, nullptr);
    }

}

void StyleManager::lordStyle()
{
    QMap<QString, QString> styleKey;
    auto& editor = ConfigUser::instance().m_editor;
    QString fonmtFamiliesString;
    for(auto i = editor.m_fontFamilies.constBegin(); i != editor.m_fontFamilies.constEnd(); i ++)
    {
        fonmtFamiliesString.append(*i);
        if(i != editor.m_fontFamilies.constEnd() - 1)
        {
            fonmtFamiliesString.append(',');
        }
    }
    styleKey.insert(STYLEKEY_FONT_FAMILIES, fonmtFamiliesString);
    styleKey.insert(STYLEKEY_FONT_LINEHEIGHT, QString::number(editor.m_fontLineHeight));
    styleKey.insert(STYLEKEY_FONT_SIZE, QString::number(editor.m_fontSize) + "px");
    styleKey.insert(STYLEKEY_FONT_WEIGHT, QString::number(editor.m_fontWeight));

    if(m_styleUtil != nullptr) delete m_styleUtil;

    if(editor.m_islightStyle)
        m_styleUtil = new StyleUtil(ConfigSystem::instance().m_paths.m_styleDir + '/' + ConfigSystem::instance().m_paths.m_styleLightDirName
                                        + '/' + ConfigSystem::instance().m_paths.m_stylePreDirName,
                                    ConfigSystem::instance().m_paths.m_styleDir + '/' + ConfigSystem::instance().m_paths.m_styleLightDirName,
                                    ConfigSystem::instance().m_paths.m_styleFileName);
    else
        m_styleUtil = new StyleUtil(ConfigSystem::instance().m_paths.m_styleDir + '/' + ConfigSystem::instance().m_paths.m_styleDarkDirName
                                        + '/' + ConfigSystem::instance().m_paths.m_stylePreDirName,
                                    ConfigSystem::instance().m_paths.m_styleDir + '/' + ConfigSystem::instance().m_paths.m_styleDarkDirName,
                                    ConfigSystem::instance().m_paths.m_styleFileName);

    if(m_watcherEnableManual)
    {
        m_watcher.removePaths(m_watcher.files());
        m_watcher.addPaths(m_styleUtil->getFileList());
        changeStyle(styleKey);
    }
    else
    {
        lordStyle(styleKey);
    }
}

bool StyleManager::lordStyle(QMap<QString, QString> styleKey)
{
    if(!m_styleUtil->preProcess(styleKey))
    {
        LOG_WARNING("预处理失败");
        return false;
    }
    if(!m_styleUtil->merger())
    {
        LOG_WARNING("合并失败");
        return false;
    }
    LOG_INFO("样式装载成功");

    QString styleSheet = m_styleUtil->getStyle();

    if(!styleSheet.isEmpty())
        qApp->setStyleSheet(styleSheet);
    return true;
}

bool StyleManager::changeStyle(QMap<QString, QString> styleKey)
{
    if(!m_styleUtil->preProcess(styleKey))
    {
        LOG_WARNING("预处理失败");
        return false;
    }
    return true;
}
