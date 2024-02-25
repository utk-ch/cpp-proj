#ifndef MEREMEMO_TESTS_LOGTAGS_H
#define MEREMEMO_TESTS_LOGTAGS_H
#include "../Log.h"
inline MereMemo::LogLevel error("error");
inline MereMemo::LogLevel info("info");
inline MereMemo::LogLevel debug("debug");
class Color : public MereMemo::Tag
{
public:
    Color(std::string const &text)
        : Tag("color", text)
    {
    }
    std::unique_ptr<Tag> clone() const override
    {
        return std::unique_ptr<Tag>(
            new Color(*this));
    }
};
inline Color red("red");
inline Color green("green");
inline Color blue("blue");

class Size : public MereMemo::Tag
{
public:
    Size(std::string const &text)
        : Tag("size", text)
    {
    }
    std::unique_ptr<Tag> clone() const override
    {
        return std::unique_ptr<Tag>(
            new Size(*this));
    }
};
inline Size small("small");
inline Size medium("medium");
inline Size large("large");

class Count : public MereMemo::Tag
{
public:
    Count(int value)
        : Tag("count", value)
    {
    }
    std::unique_ptr<Tag> clone() const override
    {
        return std::unique_ptr<Tag>(
            new Count(*this));
    }
};
class Identity : public MereMemo::Tag
{
public:
    Identity(long long value)
        : Tag("id", value)
    {
    }
    std::unique_ptr<Tag> clone() const override
    {
        return std::unique_ptr<Tag>(
            new Identity(*this));
    }
};
class Scale : public MereMemo::Tag
{
public:
    Scale(double value)
        : Tag("scale", value)
    {
    }
    std::unique_ptr<Tag> clone() const override
    {
        return std::unique_ptr<Tag>(
            new Scale(*this));
    }
};
class CacheHit : public MereMemo::Tag
{
public:
    CacheHit(bool value)
        : Tag("cache_hit", value)
    {
    }
    std::unique_ptr<Tag> clone() const override
    {
        return std::unique_ptr<Tag>(
            new CacheHit(*this));
    }
};
inline CacheHit cacheHit(true);
inline CacheHit cacheMiss(false);
#endif // MEREMEMO_TESTS_LOGTAGS_H