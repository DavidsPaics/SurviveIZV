#include <iostream>
#include <chrono>
#include <iomanip>

namespace logging
{
    template <typename... Args>
    void DEBUG(const Args &...args)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&now_c);
        std::cout << '[' << std::setw(2) << std::setfill('0') << tm.tm_hour << ':'
                  << std::setw(2) << std::setfill('0') << tm.tm_min << ':'
                  << std::setw(2) << std::setfill('0') << tm.tm_sec << "] [DEBUG] ";
        ((std::cout << args << ' '), ...) << std::endl;
    }

    template <typename... Args>
    void INFO(const Args &...args)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&now_c);
        std::cout << '[' << std::setw(2) << std::setfill('0') << tm.tm_hour << ':'
                  << std::setw(2) << std::setfill('0') << tm.tm_min << ':'
                  << std::setw(2) << std::setfill('0') << tm.tm_sec << "] [INFO] ";
        ((std::cout << args << ' '), ...) << std::endl;
    }

    template <typename... Args>
    void WARNING(const Args &...args)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&now_c);
        std::cout << '[' << std::setw(2) << std::setfill('0') << tm.tm_hour << ':'
                  << std::setw(2) << std::setfill('0') << tm.tm_min << ':'
                  << std::setw(2) << std::setfill('0') << tm.tm_sec << "] [WARNING] ";
        ((std::cout << args << ' '), ...) << std::endl;
    }

    template <typename... Args>
    void ERROR(const Args &...args)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&now_c);
        std::cout << '[' << std::setw(2) << std::setfill('0') << tm.tm_hour << ':'
                  << std::setw(2) << std::setfill('0') << tm.tm_min << ':'
                  << std::setw(2) << std::setfill('0') << tm.tm_sec << "] [ERROR] ";
        ((std::cout << args << ' '), ...) << std::endl;
    }

    template <typename... Args>
    void CRITICAL(const Args &...args)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&now_c);
        std::cout << '[' << std::setw(2) << std::setfill('0') << tm.tm_hour << ':'
                  << std::setw(2) << std::setfill('0') << tm.tm_min << ':'
                  << std::setw(2) << std::setfill('0') << tm.tm_sec << "] [CRITICAL] ";
        ((std::cout << args << ' '), ...) << std::endl;
    }
}