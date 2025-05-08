#include "utils/Logger.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Logger& Logger::instance() {
    static Logger logger;
    return logger;
}

void Logger::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex);

    std::string timestamp = getTimestamp();
    std::string fullMessage = "[" + timestamp + "] " + message;

    // Выводим в консоль
    std::cout << fullMessage << std::endl;

    // Пишем в файл, если открыт
    if (logFile.is_open()) {
        logFile << fullMessage << std::endl;
        logFile.flush();
    }
}

void Logger::setLogFile(const std::string& filePath) {
    if (logFile.is_open()) {
        logFile.close();
    }

    logFile.open(filePath, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Не удалось открыть файл для логов: " << filePath << std::endl;
    }
}

Logger::Logger() {
    // По умолчанию логируем в текущую директорию
    setLogFile("app.log");
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

std::string Logger::getTimestamp() {
    time_t now = time(nullptr);
    std::tm tm_buf;
    localtime_r(&now, &tm_buf);


    std::ostringstream oss;
    oss << std::put_time(&tm_buf, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}