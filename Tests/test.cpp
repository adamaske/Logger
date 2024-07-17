#include <iostream>

#include "Logger.h"

int main() {
	
	Logger::Info("Test #1");
	Logger::Error("Test #2");
	Logger::Warning("Test #3");
	Logger::Debug("Test #4");

	return 0;
}