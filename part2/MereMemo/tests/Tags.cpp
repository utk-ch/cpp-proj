#include "../Log.h"
#include "LogTags.h"
#include "Util.h"
#include "../../MereTDD/Test.h"

TEST("Message can be tagged in log")
{
    std::string message = "simple tag ";
    message += Util::randomString();
    MereMemo::log(error) << message;
    // Confirm that the error tag value exists and that the
    // default info tag value does not.
    std::string logLevelTag = " log_level=\"error\" ";
    std::string defaultLogLevelTag = " log_level=\"info\" ";
    bool result = Util::isTextInFile(message, "application.log",
                                     {logLevelTag}, {defaultLogLevelTag});
    CONFIRM_TRUE(result);
}

TEST("log needs no namespace when used with LogLevel")
{
    log(error) << "no namespace";
}

TEST("Default tags set in main appear in log")
{
    std::string message = "default tag ";
    message += Util::randomString();
    MereMemo::log() << message;
    std::string logLevelTag = " log_level=\"info\" ";
    std::string colorTag = " color=\"green\" ";
    bool result = Util::isTextInFile(message, "application.log",
                                     {logLevelTag, colorTag});
    CONFIRM_TRUE(result);
}

TEST("Multiple tags can be used in log")
{
    std::string message = "multi tags ";
    message += Util::randomString();
    MereMemo::log(debug, red, large) << message;
    std::string logLevelTag = " log_level=\"debug\" ";
    std::string colorTag = " color=\"red\" ";
    std::string sizeTag = " size=\"large\" ";
    bool result = Util::isTextInFile(message, "application.log",
                                     {logLevelTag, colorTag, sizeTag});
    CONFIRM_TRUE(result);
}

TEST("Tags can be streamed to log")
{
    std::string messageBase = " 1 type ";
    std::string message = messageBase + Util::randomString();
    MereMemo::log(info) << Count(1) << message;
    std::string countTag = " count=1 ";
    bool result = Util::isTextInFile(message, "application.log", {countTag});
    CONFIRM_TRUE(result);
    messageBase = " 2 type ";
    message = messageBase + Util::randomString();
    MereMemo::log(info) << Identity(123456789012345) << message;
    std::string idTag = " id=123456789012345 ";
    result = Util::isTextInFile(message, "application.log",
                                {idTag});
    CONFIRM_TRUE(result);
    messageBase = " 3 type ";
    message = messageBase + Util::randomString();
    MereMemo::log(info) << Scale(1.5) << message;
    std::string scaleTag = " scale=1.500000 ";
    result = Util::isTextInFile(message, "application.log",
                                {scaleTag});
    CONFIRM_TRUE(result);
    messageBase = " 4 type ";
    message = messageBase + Util::randomString();
    MereMemo::log(info) << cacheMiss << message;
    std::string cacheTag = " cache_hit=false ";
    result = Util::isTextInFile(message, "application.log",
                                {cacheTag});
    CONFIRM_TRUE(result);
}