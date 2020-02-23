#pragma once

// cstdlib
#include <chrono>
#include <thread>
#include <string>

// external libs

// program
#include "PCH.h"
#include "Window.h"
#include "TraceEvents.h"
#include "Profiler.h"



namespace c3p
{

	class Timer
	{
	public:
		Timer(const std::string &sName = "default", const std::string& sCatagory = "function");
		~Timer();

		CompleteEvent stop();

	private:
		std::string msName;
		std::string msCatagory;
		std::chrono::time_point<std::chrono::steady_clock> moStartTimepoint;
		bool mbStopped;
	};

}
