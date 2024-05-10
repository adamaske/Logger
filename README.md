# Logger

Simple C++ static library for logging. Optionally a wrapper for [Spdlog](https://github.com/gabime/spdlog).

## Usage
```
#include "Logger.h"

Logger::Initalize(L_INFO, L_CONSOLE)

Logger::Info("Wow, what a great function!");
Logger::Error("An error occured....");
```