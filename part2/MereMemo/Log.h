#ifndef MEREMEMO_LOG_H
#define MEREMEMO_LOG_H
#include <fstream>
#include <iostream>
#include <string_view>
namespace MereMemo
{
    inline void log(std::string_view message)
    {
        std::fstream logFile("application.log", std::ios::app);
        logFile << message << std::endl;
    }
} // namespace MereMemo
#endif // MEREMEMO_LOG_H