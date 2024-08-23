#include <iostream>

#include "Logger.h"

int main() {
	//What kind of handlers do we have
	Logging::FileHandler fh;
	Logging::COUTHandler ch;


	Logging::Logger il;
	il.level = Logging::Level::DEBUG;

	Logging::Logger dl;
	dl.level = Logging::Level::DEBUG;

	il.Config();
	dl.Config();

	il.handlers.push_back(&fh);
	il.handlers.push_back(&ch);

	dl.handlers.push_back(&fh);
	dl.handlers.push_back(&ch);

	il.queue_listener.handlers.push_back(&fh);
	il.queue_listener.handlers.push_back(&ch);
	
	il.threaded = false;


	il.Info("Hello officer");

	return 0;
}