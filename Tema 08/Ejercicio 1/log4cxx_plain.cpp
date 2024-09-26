#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>
#include <log4cxx/propertyconfigurator.h>
#include <log4cxx/consoleappender.h>
#include <log4cxx/patternlayout.h>
#include <log4cxx/level.h>

using namespace log4cxx;
using namespace log4cxx::helpers;

int main() {
    // Configuración básica del logger
    BasicConfigurator::configure();
    LoggerPtr logger(Logger::getLogger("MyAppLogger"));

    // Establecer el nivel de logging (opcional, por defecto INFO)
    logger->setLevel(Level::getDebug());

    // Emitir mensajes de logging en diferentes niveles
    LOG4CXX_DEBUG(logger, "Este es un mensaje de depuración (DEBUG)");
    LOG4CXX_INFO(logger, "Este es un mensaje informativo (INFO)");
    LOG4CXX_WARN(logger, "Este es un mensaje de advertencia (WARN)");
    LOG4CXX_ERROR(logger, "Este es un mensaje de error (ERROR)");

    return 0;
}
