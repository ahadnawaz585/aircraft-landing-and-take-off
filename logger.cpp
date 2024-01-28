#include "logger.h"

Logger::Logger(const std::string& logFileName) {
    logFile.open(logFileName, std::ios::app);
}

void Logger::logEvent(const std::string& logMessage) {
    logFile << logMessage << "\n";
}
