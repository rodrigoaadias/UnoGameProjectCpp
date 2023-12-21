#pragma once
#include <iostream>
#include <string>

class Core {
    inline static bool WantsToClose = false;

public:
	static void RunEngine();
	static void CloseApp();

    template <typename TData>
    static TData GetInput(const std::string& message)
    {
        TData returnValue;
        std::cout << message;
        std::cin >> returnValue;
        std::cout << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        return returnValue;
    }

    static void WaitAnyKey(const std::string& message);
    static void LogMessage(const std::string& message);
    static void LogError(const std::string& errorMessage);
    static int RandomRange(int min, int maxInclusive);
};