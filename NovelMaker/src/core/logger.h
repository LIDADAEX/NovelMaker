#ifndef LOGGER_H
#define LOGGER_H

#include "src/utilitis/config/configdefine.h"
#include <QFile>
#include <QObject>

enum class LogLevel : quint16 {
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

    /*****************************************
     * 函数名：initialize
     * 作用：初始化Log实例
     * 返回值:void
     * 形参：
     * logDir：const QString&，日志文件夹位置
     * consoleLevel：LogLevel，控制台最小等级
     * fileLevel：LogLevel，文件最小等级
     *****************************************/
    void initialize(const QString& logDir = LOG_DIR,
                   LogLevel consoleLevel = LogLevel::Info,
                   LogLevel fileLevel = LogLevel::Debug);

    /*****************************************
     * 函数名：log
     * 作用：向文件和控制台写入日志
     * 返回值:void
     * 形参：
     * level：LogLevel，日志等级
     * message：const QString&，日志信息
     * file：const char*，日志产生的文件
     * line：int，日志产生的文件的对应行数
     * function：const char*，日志产生的文件的对应函数
     *****************************************/
    void log(LogLevel level, const QString& message,
             const char* file = "", int line = 0,
             const char* function = "");

    /*便利宏定义，对应等级，__FILE__,__LINE__,__FUNCTION__
    分别是QT的预设宏可以自动填入日志发送的文件，行数和函数*/
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

    /*****************************************
     * 函数名：installQtMessageHandler
     * 作用：安装QT的信息处理，主要是把QT的信息写入到控制台和文件中
     * 返回值:void
     * 形参：void
     *****************************************/
    /*****************************************
     * 函数名：qtMessageHandler
     * 作用：QT的信息处理，主要是把QT的信息写入到控制台和文件中
     * 返回值:void
     * 形参：void
     *****************************************/
    static void installQtMessageHandler();
    static void qtMessageHandler(QtMsgType type,
                                 const QMessageLogContext& context,
                                 const QString& msg);

    /*****************************************
     * 函数名：setLogLevel
     * 作用：设置Log的等级，主要是大于什么等级的才会被记录在控制台或者文件中
     * 返回值:void
     * 形参：
     * level：LogLevel，日志等级
     * forConsole：bool，区分是控制台的还是文件的
     *****************************************/
    /*****************************************
     * 函数名：enableFileLogging
     * 作用：启用写入日志到文件的功能
     * 返回值:void
     * 形参：
     * enable：bool，是否启用
     *****************************************/
    /*****************************************
     * 函数名：setLogFileSizeLimit
     * 作用：设置文件日志大小限制，
     * 返回值:void
     * 形参：
     * maxSizeBytes：qint64，最大日志字节数
     *****************************************/
    void setLogLevel(LogLevel level, bool forConsole = true);
    void enableFileLogging(bool enable);
    void setLogFileSizeLimit(qint64 maxSizeBytes);

private:

    //默认构造与析构函数
    Logger() = default;
    ~Logger() = default;

    //禁用拷贝构造
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    /*****************************************
     * 函数名：writeToConsole
     * 作用：将格式化后的信息写入控制台，不会判断是否大于m_consoleLevel
     * 返回值:void
     * 形参：
     * level：LogLevel，日志等级
     * formattedMsg：const QString&，格式化信息
     *****************************************/
    /*****************************************
     * 函数名：writeToFile
     * 作用：将格式化后的信息写入文件，不会判断是否大于m_fileLevel
     * 返回值:void
     * 形参：
     * level：LogLevel，日志等级
     * formattedMsg：const QString&，格式化信息
     *****************************************/
    /*****************************************
     * 函数名：rotateLogFileIfNeeded
     * 作用：滚动文件，意思就是当文件大小超限了的时候将最早的日志删除，添加最新的在最下方。
     * 返回值:void
     * 形参：void
     *****************************************/
    void writeToConsole(LogLevel level, const QString& formattedMsg);
    void writeToFile(LogLevel level, const QString& formattedMsg);
    void rotateLogFileIfNeeded();

private:
    //m_isInitialize：是否初始化标志
    bool m_isInitialize = false;
    //m_enableFileLogging：是否启用文件日志标志
    bool m_enableFileLogging = true;

    //sm_oldHandler：旧的QT信息处理器
    static QtMessageHandler sm_oldHandler;

    //m_logFile:日志文件
    QFile m_logFile;
    //m_consoleLevel:写入控制台的最小等级
    LogLevel m_consoleLevel;
    //m_fileLevel:写入文件的最小等级
    LogLevel m_fileLevel;
    //m_maxFileSize:日志文件最大大小
    qint64 m_maxFileSize;
    //m_logDirectory:日志文件的所在文件目录
    QString m_logDirectory;
};

#endif // LOGGER_H
