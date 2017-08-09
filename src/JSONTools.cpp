#include "JSONTools.h"
#include "BotAssert.h"

namespace JSONTools
{
    void ReadBool(const char * key, const rapidjson::Value & value, bool & dest)
    {
        if (value.HasMember(key))
        {
            BOT_ASSERT(value[key].IsBool(), "%s should be a bool", key);
            dest = value[key].GetBool();
        }
    }

    void ReadString(const char * key, const rapidjson::Value & value, std::string & dest)
    {
        if (value.HasMember(key))
        {
            BOT_ASSERT(value[key].IsString(), "%s should be a string", key);
            dest = value[key].GetString();
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


