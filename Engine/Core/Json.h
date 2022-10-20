/*
Ducktape | An open source C++ 2D & 3D game engine that focuses on being fast, and powerful.
Copyright (C) 2022 Aryan Baburajan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

In case of any further questions feel free to contact me at
the following email address:
aryanbaburajan2007@gmail.com
*/

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace DT
{
    enum JsonType
    {
        Null,
        Boolean,
        Integer,
        Decimal,
        String,
        Array,
        Object
    };

    class Json
    {
    public:
        JsonType type = JsonType::Null;
        
        bool boolean;
        int integer;
        float decimal;
        std::string string;
        std::vector<Json> array;
        std::map<std::string, Json> object;
        
        Json &operator =(const bool &object)
        {
            type = JsonType::Boolean;
            boolean = object;
            return *this;
        }

        Json &operator =(const int &object)
        {
            if (object == NULL)
            {
                type == JsonType::Null;
            }
            else
            {
                type = JsonType::Integer;
                integer = object;
            }
            return *this;
        }
        
        Json &operator =(const float &object)
        {
            type = JsonType::Decimal;
            decimal = object;
            return *this;
        }
        
        Json &operator =(const std::string &object)
        {
            type = JsonType::String;
            string = object;
            return *this;
        }
        
        Json &operator =(const std::vector<Json> &object)
        {
            type = JsonType::Array;
            array = object;
            std::cout << "eq\n";
            return *this;
        }
        
        std::string Dump()
        {
            switch (type)
            {
            case JsonType::Null:
                return "undefined";
                break;
            case JsonType::Boolean:
                if (boolean) return "true";
                else return "false";
                break;
            case JsonType::Integer:
                return std::to_string(integer);
                break;
            case JsonType::Decimal:
                return std::to_string(decimal);
                break;
            case JsonType::String:
                return "\"" + string + "\"";
                break;
            case JsonType::Array:
            {
                std::string result = "[";
                for (Json j : array)
                    result += j.Dump();
                result += "]";
                break;
            }
            case JsonType::Object:
            {
                std::string result = "{";
                for(std::map<std::string, Json>::iterator iter = object.begin(); iter != object.end(); ++iter)
                {
                    result += "\"" + iter->first + "\": ";
                    result += iter->second.Dump();
                    result += ",";
                }
                result += "}";
                break;
            }
            }
        }
    };
}