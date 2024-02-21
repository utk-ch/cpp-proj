#ifndef MEREMEMO_LOG_H
#define MEREMEMO_LOG_H
#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>
namespace MereMemo
{
    // we are able to move the stream out of log function
    // because we are using C++17 and we can return a stream
    // stream is passed by value, so it is moved
    inline std::fstream log()
    {
        auto const now = std::chrono::system_clock::now();
        std::time_t const tmNow = std::chrono::system_clock::to_time_t(now);
        auto const ms = duration_cast<std::chrono::milliseconds>(
                            now.time_since_epoch()) %
                        1000;
        std::fstream logFile("application.log", std::ios::app);
        logFile << std::endl /* temporary solution to make sure each log message is in a new line*/
                << std::put_time(std::gmtime(&tmNow), "%Y-%m-%dT%H:%M:%S.")
                << std::setw(3) << std::setfill('0') << std::to_string(ms.count())
                << " ";
        return logFile;
    }
} // namespace MereMemo
#endif // MEREMEMO_LOG_H