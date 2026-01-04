#include "logger.h"

#include <QDir>
#include <QFileInfo>
#include <QApplication>

QtMessageHandler Logger::sm_oldHandler = nullptr;

Logger &Logger::instance()
{
    static Logger instance;  // 静态局部变量，线程安全
    return instance;
}

void Logger::initialize(const QString &logDir, LogLevel consoleLevel, LogLevel fileLevel)
{
    //防止重复初始化，因为此时处于初始化环节所以只能够写入控制台
    if(m_isInitialize)
    {
        if(consoleLevel <= LogLevel::Info)
            writeToConsole(LogLevel::Info, "检测到日志重复初始化，已取消");
        return;
    }

    m_logDirectory = logDir;
    m_consoleLevel = consoleLevel;
    m_fileLevel = fileLevel;
    m_maxFileSize = 1024 * 1024; //1MB

    //检查日志目录是否存在，不存在则创建，开始
    if(m_consoleLevel == LogLevel::Debug)
        writeToConsole(LogLevel::Debug, "正在检查日志文件夹");

    QDir dir(logDir);
    if(!dir.exists())
    {
        if(m_consoleLevel == LogLevel::Debug)
            writeToConsole(LogLevel::Debug, "未找到日志文件夹，正在创建");

        if(!dir.mkpath("."))
        {
            writeToConsole(LogLevel::Fatal, "致命错误！日志文件夹创建失败");
            qApp->quit();
        }

        if(m_consoleLevel == LogLevel::Debug)
            writeToConsole(LogLevel::Debug, "日志文件夹创建成功");
    }
    if(m_consoleLevel == LogLevel::Debug)
    writeToConsole(LogLevel::Debug, "日志文件夹检查完毕");
    //检查日志目录是否存在，结束

    //创建新的日志文件，开始
    if(m_consoleLevel == LogLevel::Debug)
        writeToConsole(LogLevel::Debug, "正在创建新日志文件");

    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy_MM_ddThh_mm_ss");

    m_logFile.setFileName(logDir + '/' +
                          "__log_" +currentDateTime +
                          "_.txt");

    if(!m_logFile.open(QIODeviceBase::WriteOnly))
    {
        writeToConsole(LogLevel::Warning, "日志文件初始化失败,停止");
        m_enableFileLogging = false;
    }

    if(m_consoleLevel == LogLevel::Debug)
        writeToConsole(LogLevel::Debug, "日志文件创建成功");

    m_logFile.close();
    //创建新的日志文件，结束

    m_isInitialize = true;

    LOG_INFO("日志初始化完毕");
}

void Logger::log(LogLevel level, const QString& message, const char *file, int line, const char *function)
{
    if(!m_isInitialize) return;

    //如果没有一个满足等级要求就直接返回
    if((qint16(level) < qint16(m_consoleLevel)) && (qint16(level) < qint16(m_fileLevel))) return;

    //构造格式化信息，开始
    QString formattedMsg;
    QString fileString(file);
    fileString = fileString.sliced(fileString.lastIndexOf('/') + 1);
    formattedMsg = formattedMsg
                   + '[' + fileString + ':' + QString::number(line) + ']'
                   + '[' + function + ']'
                   + '[' + message + ']';
    //构造格式化信息，结束

    //写入控制台
    if(qint16(level) >= qint16(m_consoleLevel))
    {
        writeToConsole(level, formattedMsg);
    }

    //写入文件
    if(m_enableFileLogging)
    if(qint16(level) >= qint16(m_fileLevel))
    {
        writeToFile(level, formattedMsg);
    }

    //判断是否超过大小
    rotateLogFileIfNeeded();

    //如果是致命错误就会终止程序
    if(level == LogLevel::Fatal)
    {
        QApplication::closeAllWindows();
        qApp->quit();
        std::exit(EXIT_FAILURE);
    }
}

void Logger::setLogLevel(LogLevel level, bool forConsole)
{
    if(forConsole)
        m_consoleLevel = level;
    else
        m_fileLevel = level;
}

void Logger::enableFileLogging(bool enable)
{
    m_enableFileLogging = enable;
}

void Logger::setLogFileSizeLimit(qint64 maxSizeBytes)
{
    m_maxFileSize = maxSizeBytes;
}

void Logger::installQtMessageHandler()
{
    sm_oldHandler = qInstallMessageHandler(Logger::qtMessageHandler);
}

void Logger::qtMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    //转换QT的格式至LogLevel
    LogLevel level;
    switch (type) {
    case QtDebugMsg:
        level = LogLevel::Debug;
        break;
    case QtInfoMsg:
        level = LogLevel::Info;
        break;
    case QtWarningMsg:
        level = LogLevel::Warning;
        break;
    case QtCriticalMsg:
        level = LogLevel::Critical;
        break;
    case QtFatalMsg:
        level = LogLevel::Fatal;
        break;
    }

    instance().log(level, msg, context.file, context.line, context.function);

    //处理旧处理器
    if (sm_oldHandler) {
        sm_oldHandler(type, context, msg);
    }
}

void Logger::writeToConsole(LogLevel level, const QString &formattedMsg)
{
    QTextStream stream(stdout);
    stream.setEncoding(QStringConverter::System);

    switch(level)
    {
    case LogLevel::Debug:
        stream << "\033[37m" << "[DEBUG]" << formattedMsg << "\033[0m" << Qt::endl;  // 灰色
        break;
    case LogLevel::Info:
        stream << "[INFO]" << formattedMsg << Qt::endl;
        break;
    case LogLevel::Warning:
        stream << "\033[33m" << "[WARNING]" << formattedMsg << "\033[0m" << Qt::endl; //黄色
        break;
    case LogLevel::Error:
        stream << "\033[31m" << "[ERROR]" << formattedMsg << "\033[0m" << Qt::endl; //红色
        break;
    case LogLevel::Critical:
        stream << "\033[31m" << "[CRITICAL]" << formattedMsg << "\033[0m" << Qt::endl; //红色
        break;
    case LogLevel::Fatal:
        stream << "\033[41;37m" << "[FATAL]" << formattedMsg << "\033[0m" << Qt::endl; //红色
        break;
    }

    stream.flush();
}

void Logger::writeToFile(LogLevel level, const QString &formattedMsg)
{
    if(!m_logFile.open(QIODeviceBase::WriteOnly | QIODeviceBase::Append))
    {
        LOG_WARNING("日志正在被占用");
        return;
    }

    switch(level)
    {
    case LogLevel::Debug:
        m_logFile.write(QString("[DEBUG]" + formattedMsg).toUtf8() + '\n');
        break;
    case LogLevel::Info:
        m_logFile.write(QString("[INFO]" + formattedMsg).toUtf8() + '\n');
        break;
    case LogLevel::Warning:
        m_logFile.write(QString("[WARNING]" + formattedMsg).toUtf8() + '\n');
        break;
    case LogLevel::Error:
        m_logFile.write(QString("[ERROR]" + formattedMsg).toUtf8() + '\n');
        break;
    case LogLevel::Critical:
        m_logFile.write(QString("[CRITICAL]" + formattedMsg).toUtf8() + '\n');
        break;
    case LogLevel::Fatal:
        m_logFile.write(QString("[FATAL]" + formattedMsg).toUtf8() + '\n');
        break;
    }

    m_logFile.close();
}

void Logger::rotateLogFileIfNeeded()
{
    if(m_logFile.size() <= m_maxFileSize) return;

    if(!m_logFile.open(QIODeviceBase::ReadOnly))
    {
        qWarning() << "日志文件正在被占用！";
        return;
    }

    QString logFileContents = m_logFile.readAll();
    m_logFile.close();

    //如果大于最大大小就会清除首行直到小于目标最大大小
    while(logFileContents.size() > m_maxFileSize)
    logFileContents.removeAt(logFileContents.indexOf("\n") + 1);

    if(!m_logFile.open(QIODeviceBase::WriteOnly))
    {
        qWarning() << "日志文件正在被占用！";
        return;
    }

    m_logFile.write(logFileContents.toUtf8());
    m_logFile.close();
}


