#pragma once

class Core {
    inline static bool WantsToClose = false;

public:
	static void RunEngine();
	static void CloseApp();
};