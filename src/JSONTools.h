#pragma once

#include "Common.h"

namespace JSONTools
{
    template <class T>
    void ReadInt(const char * key, const json & j, T & dest)
    {
        if (j.count(key))
        {
            BOT_ASSERT(j[key].is_number_integer(), "%s should be an int", key);
            dest = (T)j[key];
        }
    }
    
    void ReadBool(const char * key, const json & json, bool & dest);
    void ReadString(const char * key, const json & json, std::string & dest);
    
    std::string ReadFile(const std::string & filename);
}
