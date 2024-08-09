#include "Logger.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

Logger::Logger(const std::string& filename) : logfile_path(filename), logfile(filename, std::ios::app) {
    if (!logfile.is_open()) {
        throw std::runtime_error("Unable to open log file");
    }
}

Logger::~Logger() {
    if (logfile.is_open()) {
        logfile.close();
    }
}

void Logger::log_message(const std::string& message) {
    std::unique_lock lock(mutex_);
    logfile << message << std::endl;
}

std::string Logger::read_last_message() {
    std::shared_lock lock(mutex_);
    std::string line;
    std::string last_line;
    std::ifstream logreader(logfile_path, std::ios::in);
    while (std::getline(logreader, line)) {
        last_line = line;
    }
    return last_line;
}

