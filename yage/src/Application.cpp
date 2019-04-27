// stl

// external

// program
#include "PCH.h"
#include "Window.h"
#include "IOUtilities.h"

#undef main

using namespace YAGE;

int main()
{
	Window window;

	LOG(LOG_DEBUG) << "Starting main loop";
	bool run = true;
	while (run)
	{
		SDL_Event incomingEvent;
		while (SDL_PollEvent(&incomingEvent))
		{
			if (incomingEvent.type == SDL_QUIT)
			{
				LOG(LOG_DEBUG) << "SDL_QUIT event called";
				run = false;
			}
		}
	}
	LOG(LOG_DEBUG) << "Main loop ended";

	Log::toFile("log.txt");
	std::string log = IOUtilities::loadText("log.txt");
	LOG(LOG_DEBUG) << log;
	return 0;
}