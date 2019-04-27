// stl

// external

// program
#include "PCH.h"

#undef main

using namespace YAGE;

int main()
{
	LOG(LOG_DEBUG) << "Test Debug";
	LOG(LOG_WARNING) << "Test Warning";
	LOG(LOG_ERROR) << "Test Error";

	Log::toFile("log.txt");

	bool run = true;
	while (run)
	{
		
	}

	return 0;
}