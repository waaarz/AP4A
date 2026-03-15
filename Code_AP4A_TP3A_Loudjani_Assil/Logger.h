#pragma once
#include <string>
#include <fstream>
#include <mutex>

class Logger {
public:
    Logger(const std::string& grantFile, const std::string& denyFile);
    ~Logger();
    void logGrant(const std::string& line);
    void logDeny(const std::string& line);
private:
    std::ofstream grant_;
    std::ofstream deny_;
    std::mutex mtx_;
};
