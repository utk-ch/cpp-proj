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
};
inline Color red("red");
inline Color green("green");
inline Color blue("blue");

#endif // MEREMEMO_TESTS_LOGTAGS_H