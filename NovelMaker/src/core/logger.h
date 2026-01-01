#ifndef LOGGER_H
#define LOGGER_H

#include <QFile>
#include <QObject>

enum class LogLevel : qint16 {
    Debug = 0,      // 调试信息
    Info,       // 普通信息
    Warning,    // 警告
    Error,      // 错误
    Critical,   // 严重错误
    Fatal       // 致命错误（会终止程序）
};

class Logger
{
public:
    static Logger& instance();

    void initialize(const QString& logDir = "",
                   LogLevel consoleLevel = LogLevel::Info,
                   LogLevel fileLevel = LogLevel::Debug);

    void log(LogLevel level, const QString& message,
             const char* file = "", int line = 0,
             const char* function = "");

    #define LOG_DEBUG(msg)    Logger::instance().log(LogLevel::Debug, msg, \
                                                    __FILE__, __LINE__, __FUNCTION__)
    #define LOG_INFO(msg)     Logger::instance().log(LogLevel::Info, msg, \
                                                    __FILE__, __LINE__, __FUNCTION__)
    #define LOG_WARNING(msg)  Logger::instance().log(LogLevel::Warning, msg, \
                                                    __FILE__, __LINE__, __FUNCTION__)
    #define LOG_ERROR(msg)    Logger::instance().log(LogLevel::Error, msg, \
                                                    __FILE__, __LINE__, __FUNCTION__)
    #define LOG_CRITICAL(msg)    Logger::instance().log(LogLevel::Critical, msg, \
                                                    __FILE__, __LINE__, __FUNCTION__)
    #define LOG_FATAL(msg)    Logger::instance().log(LogLevel::Fatal, msg, \
                                                    __FILE__, __LINE__, __FUNCTION__)

    static void installQtMessageHandler();
    static void qtMessageHandler(QtMsgType type,
                                 const QMessageLogContext& context,
                                 const QString& msg);

    void setLogLevel(LogLevel level, bool forConsole = true);
    void enableFileLogging(bool enable);
    void setLogFileSizeLimit(qint64 maxSizeBytes);

private:
    Logger() = default;
    ~Logger() = default;

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void writeToConsole(LogLevel level, const QString& formattedMsg);
    void writeToFile(LogLevel level, const QString& formattedMsg);
    void rotateLogFileIfNeeded();

    bool m_isInitialize = false;
    bool m_enableFileLogging = true;

    static QtMessageHandler m_oldHandler;

    QFile m_logFile;
    LogLevel m_consoleLevel;
    LogLevel m_fileLevel;
    qint64 m_maxFileSize;
    QString m_logDirectory;
};

#endif // LOGGER_H
