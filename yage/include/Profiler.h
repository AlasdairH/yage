#pragma once

// cstdlib
#include <unordered_map>
#include <fstream>
#include <iostream>

// external libs

// program
#include "TraceEvents.h"

namespace c3p
{

	class Profiler
	{
	public:
		/** @brief Gets the static instance of the Profiler
		*
		*	Gets the static instance of the Profiler.
		*/
		static Profiler& get()
		{
			static Profiler instance;	// guaranteed to be destroyed
										// instantiated on first use
			return instance;
		}

		void startSession(const std::string& sFilepath = "results.json");
		void writeToSession(const CompleteEvent& _event);
		void endSession();

		// ------------------------------------------------
		Profiler(Profiler const&) = delete;
		void operator=(Profiler const&) = delete;

		~Profiler();

	protected:
		Profiler();

		bool mbStarted = false;
		int miEventCount = 0;
		std::ofstream moOutputStream;
	};

}