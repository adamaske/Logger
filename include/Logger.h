#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <functional>
#include <ctime>
#include <chrono>
#include <thread>
#ifdef USE_SPDLOG
#include "spdlog/spdlog.h"
#include "spdlog/sinks/callback_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#endif
namespace Logging{


std::string TimePointToString(std::chrono::system_clock::time_point time) {
		std::time_t t = std::chrono::system_clock::to_time_t(time);
		char buf[20];
		strftime(buf, 20, "%H:%M:%S", localtime(&t));
		return std::string(buf);
}

enum class LogOutput : int {
	CONSOLE = 0,
	FILE = 1,
	GUI = 2
};
enum class Level : int {
	INFO = 0,
	DEBUG = 1,
	WARN = 2,
	ERROR = 3,
	INVALID = 4
}; 
std::string LevelToString(Level level) {

	if (level == Logging::Level::INFO) {
		return "info";
	}
	if (level == Logging::Level::DEBUG) {
		
		return "debug";
	}
	if (level == Logging::Level::WARN) {
		return "warn";
	}
	if (level == Logging::Level::ERROR) {
		return "error";
	}

	return "invalid";
}
struct Log {
	Level level = INFO;

	std::chrono::system_clock::time_point time_point;
	std::string time_string = "";

	std::string payload = "";
};

std::string LogToString(const Log log) {
	return log.time_string + " [" + LevelToString(log.level) + "] " + log.payload;
}

 class Handler {
public:
	const virtual void Handle(Log msg) = 0;
};

 class FileHandler : public Handler {
 public:
	 const void Handle(Log msg) {
		 //formatter->Format(msg);
		 //write the message to file
		 std::cout << "FILE : " << msg.payload << "\n";

	 };
 };

 class COUTHandler : public Handler {
 public:
	 const void Handle(Log msg) {
		 //
		 //std::cout << msg << "\n";
		 std::cout << "COUT : " << msg.payload << "\n";
	 }
 };

 class QueueHandler : public Handler { //Special handler for threaded mode
	 
 public:
	 std::queue<Log>* queue;

	 QueueHandler(std::queue<Log>* q) {
		 queue = q;
	 }

	 const void Handle(Log msg) {
		 //Add to queue
		 if (!queue) {
			 //Error
			 
		 }
		 queue->push(msg);
	 }
 };

 class QueueListener {
 public:
	QueueListener() {
	};
	std::vector<Handler*> handlers;
	
	std::queue<Log> queue;

	void Listen() {
		while (queue.size() != 0) {
			 auto& msg = queue.front();
			 for (const auto& handler : handlers) {
				 handler->Handle(msg);
			 }
			 queue.pop();
		}
	}

	void ListenThreaded() {
		//Check for close command
		bool close = 0; //check the atmoic variable;
		if (!close) {
			Listen();
		}
		
	}
 };

 class Formatter {
 public:
	 const virtual char* Format(Log msg, int& size) = 0;
 };

 class STD_STRING_Formatter : public Formatter {
 public:
	 const char* Fromat(const char* data, int& size, Log msg) {
		 
	 };
 };

 class CHAR_Formatter : public Formatter {
 public:

 };


class Logger {
public:

	Level level = INFO;
	std::vector<Handler*> handlers;

	QueueHandler queue_handler = QueueHandler(nullptr);
	QueueListener queue_listener = QueueListener();

	std::vector<std::function<void(const Log)>> callback_functions;

	bool threaded = true;

	void Config() {
		if (threaded) {

			queue_listener.ListenThreaded();

		}
	}

	

	static void ConsolePrintLog(const Log log) {
		std::cout << LogToString(log) << "\n";
	}

	void RegisterCallback(std::function<void(const Log)> callback) {
		callback_functions.push_back(callback);
	}

	inline void HandleLog(Level level, const std::string& msg) {
		Log log = {};
		log.level = level;
		log.time_point = std::chrono::system_clock::now();
		log.time_string = TimePointToString(log.time_point);
		log.payload = msg;

		for (auto& callback : callback_functions) {
			callback(log);
		}
	}

	inline void Info(const std::string& msg) {
		HandleLog(INFO, msg);
	}

	inline void Debug(const std::string& msg) {
		HandleLog(DEBUG, msg);
	}

	inline void Warning(const std::string& msg) {
		HandleLog(WARN, msg);
	}

	inline void Error(const std::string& msg) {
		HandleLog(ERROR, msg);
	}
};

#ifdef ENFORCE_STD_STRING_FORMAT
	template<typename T>
	inline Log ConstructLog(LogLevel level, const T& msg) {
		Log log = {};
		log.level = level;
		log.time_point = std::chrono::system_clock::now();
		log.time_string = TimePointToString(log.time_point);
		log.payload = "UNIMPLEMENTED";
		return log;
	}

	template<>
	inline Log ConstructLog(LogLevel level, const std::string& msg) {
		Log log = {};
		log.level = level;
		log.time_point = std::chrono::system_clock::now();
		log.time_string = TimePointToString(log.time_point);
		log.payload = msg;
		return log;
	}

	template<typename T>
	inline void HandleLog(LogLevel level, const T& msg) {
		Log log = ConstructLog(level, msg);

		for (auto& callback : log_callback_functions) {
			callback(log);
		}

		switch (current_output) {
		case L_CONSOLE:
			ConsolePrintLog(log);
			break;
		case L_FILE:

			break;
		case L_GUI:

			break;
		}
	}

	template<typename T>
	inline void Info(const T& msg) {
		HandleLog(L_INFO, msg);
	}

	template<typename T>
	inline void Debug(const T& msg) {
		HandleLog(L_DEBUG, msg);
	}

	template<typename T>
	inline void Warning(const T& msg) {
		HandleLog(L_WARN, msg);
	}

	template<typename T>
	inline void Error(const T& msg) {
		HandleLog(L_ERROR, msg);
	}
#endif


};