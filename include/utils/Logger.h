#pragma once
#include <string>
#include <fstream>
#include <mutex>
#include <ctime>

class Logger {
public:
    static Logger& instance();

    void log(const std::string& message);
    void setLogFile(const std::string& filePath);

private:
    Logger();
    ~Logger();

    std::ofstream logFile;
    std::mutex mutex;

    std::string getTimestamp();
};