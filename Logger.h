#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <shared_mutex>

class Logger {
public:
    explicit Logger(const std::string& filename);
    ~Logger();

    void log_message(const std::string& message);
    std::string read_last_message();

private:
    std::fstream logfile;
    std::string logfile_path;
    mutable std::shared_mutex mutex_;
};

#endif // LOGGER_H
