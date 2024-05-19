#include <iostream>

#include "Logger.h"
//#include <spdlog/spdlog.h>

int main(int argc, char** argv) {
	
	Logger::Info("Logger Online");
	Logger::Debug("Important Information");
	Logger::Warning("Warning Test");
	Logger::Error("Error Test");
	return 0;
}