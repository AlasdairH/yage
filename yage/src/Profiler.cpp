#include "PCH.h"
#include "Profiler.h"

namespace c3p
{

	Profiler::Profiler()
	{

	}

	Profiler::~Profiler()
	{
		if (mbStarted)
			endSession();
	}

	void Profiler::startSession(const std::string& sFilepath)
	{
		if (mbStarted)
		{
			std::cout << "Unable to start profiling session, session already started" << std::endl;
			return;
		}

		moOutputStream.open(sFilepath);

		mbStarted = true;
		std::cout << "Started profiling session" << std::endl;

		moOutputStream << "{\"otherData\": {},\"traceEvents\":[";
		moOutputStream.flush();
	}

	void Profiler::writeToSession(const CompleteEvent& oEvent)
	{
		if (!mbStarted)
			return;

		if (miEventCount++ > 0)
			moOutputStream << ",";

		oEvent.writeToStream(moOutputStream);

		moOutputStream.flush();
	}

	void Profiler::endSession()
	{
		mbStarted = false;

		moOutputStream << "]}";
		moOutputStream.flush();
		moOutputStream.close();
	}

}

