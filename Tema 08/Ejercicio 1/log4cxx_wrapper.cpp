#include <string>
#include "ILogger.h"
#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/consoleappender.h>
#include <log4cxx/fileappender.h>
#include <log4cxx/patternlayout.h>
#include <log4cxx/level.h>
#include <memory>

class ILogger {
public:
    virtual ~ILogger() = default;

    // Métodos genéricos para diferentes niveles de logging
    virtual void debug(const std::string& message) = 0;
    virtual void info(const std::string& message) = 0;
    virtual void warn(const std::string& message) = 0;
    virtual void error(const std::string& message) = 0;
};


class Log4CxxLogger : public ILogger {
public:
    // Constructor con configuración básica
    Log4CxxLogger() {
        // Configuración básica (sin archivo de configuración)
        log4cxx::BasicConfigurator::configure();
        logger = log4cxx::Logger::getLogger("Log4CxxLogger");
    }

    // Constructor que permite cargar desde archivo de configuración (ej. log4cxx.properties)
    explicit Log4CxxLogger(const std::string& configFilePath) {
        log4cxx::PropertyConfigurator::configure(configFilePath);
        logger = log4cxx::Logger::getLogger("Log4CxxLogger");
    }

    // Métodos de logging
    void debug(const std::string& message) override {
        LOG4CXX_DEBUG(logger, message);
    }

    void info(const std::string& message) override {
        LOG4CXX_INFO(logger, message);
    }

    void warn(const std::string& message) override {
        LOG4CXX_WARN(logger, message);
    }

    void error(const std::string& message) override {
        LOG4CXX_ERROR(logger, message);
    }

    // Métodos de configuración avanzada

    // Cambiar nivel de log
    void setLogLevel(const std::string& levelStr) {
        if (levelStr == "DEBUG") {
            logger->setLevel(log4cxx::Level::getDebug());
        } else if (levelStr == "INFO") {
            logger->setLevel(log4cxx::Level::getInfo());
        } else if (levelStr == "WARN") {
            logger->setLevel(log4cxx::Level::getWarn());
        } else if (levelStr == "ERROR") {
            logger->setLevel(log4cxx::Level::getError());
        } else {
            logger->setLevel(log4cxx::Level::getInfo()); // Default
        }
    }

    // Agregar un appender para escribir en archivo
    void addFileAppender(const std::string& filePath, const std::string& layoutPattern = "%d [%t] %-5p %c - %m%n") {
        auto fileAppender = std::make_shared<log4cxx::FileAppender>(
            std::make_shared<log4cxx::PatternLayout>(layoutPattern), filePath, true);
        logger->addAppender(fileAppender);
    }

    // Agregar un appender para la consola
    void addConsoleAppender(const std::string& layoutPattern = "%d [%t] %-5p %c - %m%n") {
        auto consoleAppender = std::make_shared<log4cxx::ConsoleAppender>(
            std::make_shared<log4cxx::PatternLayout>(layoutPattern));
        logger->addAppender(consoleAppender);
    }

    // Cargar configuración desde archivo
    void configureFromFile(const std::string& configFilePath) {
        log4cxx::PropertyConfigurator::configure(configFilePath);
    }

private:
    log4cxx::LoggerPtr logger;
};





