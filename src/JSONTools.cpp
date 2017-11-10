#include "JSONTools.h"
#include "BotAssert.h"

namespace JSONTools
{
    void JSONTools::ReadBool(const char * key, const json & j, bool & dest)
    {
        if (j.count(key))
        {
            BOT_ASSERT(j[key].is_boolean(), "%s should be a bool", key);
            dest = j[key];
        }
    }

    void JSONTools::ReadString(const char * key, const json & j, std::string & dest)
    {
        if (j.count(key))
        {
            BOT_ASSERT(j[key].is_string(), "%s should be a string", key);
            dest = j[key].get<std::string>();
        }
    }


    std::string ReadFile(const std::string & filename)
    {
        std::ifstream t(filename);
        std::stringstream buffer;
        buffer << t.rdbuf();
        return buffer.str();
    }
}


