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
    class Tag
    {
    public:
        virtual ~Tag() = default;
        std::string key() const
        {
            return mKey;
        }
        std::string text() const
        {
            return mText;
        }

    protected:
        Tag(std::string const &key, std::string const &value)
            : mKey(key), mText(key + "=\"" + value + "\"")
        {
        }

    private:
        std::string mKey;
        std::string const mText;
    };
    class LogLevel : public Tag
    {
    public:
        LogLevel(std::string const &text)
            : Tag("log_level", text)
        {
        }
    };
    inline std::string to_string(Tag const &tag)
    {
        return tag.text();
    }

    // we are able to move the stream out of log function
    // because we are using C++17 and we can return a stream
    // stream is passed by value, so it is moved
    inline std::fstream log(std::string_view preMessage = "")
    {
        auto const now = std::chrono::system_clock::now();
        std::time_t const tmNow = std::chrono::system_clock::to_time_t(now);
        auto const ms = duration_cast<std::chrono::milliseconds>(
                            now.time_since_epoch()) %
                        1000;
        std::fstream logFile("application.log", std::ios::app);
        logFile << std::endl
                << std::put_time(std::gmtime(&tmNow), "%Y-%m-%dT%H:%M:%S.")
                << std::setw(3) << std::setfill('0') << std::to_string(ms.count())
                << " " << preMessage << " ";
        return logFile;
    }
    inline std::fstream log(Tag const &tag)
    {
        return log(to_string(tag));
    }
} // namespace MereMemo
#endif // MEREMEMO_LOG_H