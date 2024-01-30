#pragma once

#include <fstream>
#include <string>

class Logger {
public:
    Logger(const std::string& logFileName);
    ~Logger();
    void logEvent(const std::string& logMessage);

private:
    std::ofstream logFile;
};
