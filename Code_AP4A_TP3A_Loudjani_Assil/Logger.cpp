#include "Logger.h"
#include <chrono>
#include <ctime>

static std::string nowTimestamp() {
    using namespace std::chrono;
    auto t = system_clock::now();
    std::time_t tt = system_clock::to_time_t(t);
    char buf[64];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&tt));
    return std::string(buf);
}

Logger::Logger(const std::string& grantFile, const std::string& denyFile) {
    grant_.open(grantFile, std::ios::app);
    deny_.open(denyFile, std::ios::app);
}

Logger::~Logger() {
    if (grant_.is_open()) grant_.close();
    if (deny_.is_open()) deny_.close();
}

void Logger::logGrant(const std::string& line) {
    std::lock_guard<std::mutex> lock(mtx_);
    if (grant_.is_open()) grant_ << nowTimestamp() << " " << line << std::endl;
}

void Logger::logDeny(const std::string& line) {
    std::lock_guard<std::mutex> lock(mtx_);
    if (deny_.is_open()) deny_ << nowTimestamp() << " " << line << std::endl;
}
