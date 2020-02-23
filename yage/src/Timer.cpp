#include "PCH.h"
#include "Timer.h"

namespace c3p
{

	Timer::Timer(const std::string& sName, const std::string& sCatagory) : msName(sName), msCatagory(sCatagory), mbStopped(false)
	{
		moStartTimepoint = std::chrono::high_resolution_clock::now();
	}

	Timer::~Timer()
	{
		if (!mbStopped)
			auto event = stop();
	}

	CompleteEvent Timer::stop()
	{
		auto endTimepoint = std::chrono::high_resolution_clock::now();

		long long start = std::chrono::time_point_cast<std::chrono::microseconds>(moStartTimepoint).time_since_epoch().count();
		long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

		uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());

		mbStopped = true;

		Profiler::get().writeToSession({ msName, msCatagory, "X", start, end - start, 0, threadID });
		return CompleteEvent({ msName, msCatagory, "X", start, end - start, 0, threadID });
	}

}