#ifndef MEREMEMO_LOG_H
#define MEREMEMO_LOG_H
#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <vector>
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
        virtual std::unique_ptr<Tag> clone() const = 0;

    protected:
        Tag(std::string const &key, std::string const &value)
            : mKey(key), mText(key + "=\"" + value + "\"")
        {
        }
        Tag(std::string const &key, int value)
            : mKey(key), mText(key + "=" + std::to_string(value))
        {
        }
        Tag(std::string const &key, long long value)
            : mKey(key), mText(key + "=" + std::to_string(value))
        {
        }
        Tag(std::string const &key, double value)
            : mKey(key), mText(key + "=" + std::to_string(value))
        {
        }
        Tag(std::string const &key, bool value)
            : mKey(key), mText(key + "=" + (value ? "true" : "false"))
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
        std::unique_ptr<Tag> clone() const override
        {
            return std::unique_ptr<Tag>(
                new LogLevel(*this));
        }
    };
    inline std::string to_string(Tag const &tag)
    {
        return tag.text();
    }
    inline std::fstream &operator<<(std::fstream &&stream, Tag const &tag)
    {
        stream << to_string(tag);
        return stream;
    }
    inline std::map<std::string, std::unique_ptr<Tag>> &getDefaultTags()
    {
        static std::map<std::string, std::unique_ptr<Tag>> tags;
        return tags;
    }

    // we are able to move the stream out of log function
    // because we are using C++17 and we can return a stream
    // stream is passed by value, so it is moved
    inline std::fstream log(std::vector<Tag const *> tags = {})
    {
        auto const now = std::chrono::system_clock::now();
        std::time_t const tmNow = std::chrono::system_clock::to_time_t(now);
        auto const ms = duration_cast<std::chrono::milliseconds>(
                            now.time_since_epoch()) %
                        1000;
        std::fstream logFile("application.log", std::ios::app);
        logFile << std::endl
                << std::put_time(std::gmtime(&tmNow), "%Y-%m-%dT%H:%M:%S.")
                << std::setw(3) << std::setfill('0') << std::to_string(ms.count());
        for (auto const &defaultTag : getDefaultTags())
        {
            if (std::find_if(tags.begin(), tags.end(),
                             [&defaultTag](auto const &tag)
                             {
                                 return defaultTag.first == tag->key();
                             }) == tags.end())
            {
                logFile << " " << defaultTag.second->text();
            }
        }
        for (auto const &tag : tags)
        {
            logFile << " " << tag->text();
        }
        logFile << " ";
        return logFile;
    }

    inline void addDefaultTag(Tag const &tag)
    {
        auto &tags = getDefaultTags();
        tags[tag.key()] = tag.clone();
    }
    inline auto log(Tag const &tag1)
    {
        return log({&tag1});
    }
    inline auto log(Tag const &tag1,
                    Tag const &tag2)
    {
        return log({&tag1, &tag2});
    }
    inline auto log(Tag const &tag1,
                    Tag const &tag2,
                    Tag const &tag3)
    {
        return log({&tag1, &tag2, &tag3});
    }
} // namespace MereMemo
#endif // MEREMEMO_LOG_H