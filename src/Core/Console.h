#pragma once

namespace Ducktape
{
    namespace Console
    {
        std::vector<std::pair<std::string, std::string>> logHistory;

        void Log(std::string text)
        {
            std::cout << text;
            logHistory.push_back({"default", text});
        }

        void Log(std::string category, std::string text)
        {
            std::cout << text;
            logHistory.push_back({category, text});
        }
    }
}