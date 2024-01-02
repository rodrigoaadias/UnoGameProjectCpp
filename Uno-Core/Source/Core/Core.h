#pragma once
#include <iostream>
#include <string>

#define TEXT(x) x

class Core {
    inline static bool WantsToClose{false};
    inline static const char* RED_COLOR = "\033[31m";
    inline static const char* DEFAULT_COLOR = "\033[0m";

public:
	static void RunEngine();
	static void CloseApp();

    template <typename TData>
    static TData GetInput(const std::string& message)
    {
        TData returnValue;
        std::cout << message;
        std::cin >> returnValue;
        std::cout << "\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        return returnValue;
    }

    static void WaitAnyKey(const std::string& message);
    static void LogMessage(std::string_view message);
    static void LogError(std::string_view errorMessage);
    static int RandomRange(int min, int maxInclusive);
    static void ClearConsole();
};