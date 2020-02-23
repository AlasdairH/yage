#pragma once

// cstdlib
#include <string>
#include <fstream>
#include <string>

// external libs

// program
#include "PCH.h"

namespace c3p
{
	struct TraceEvent
	{
		std::string sName = "Unknown";
		std::string sCat = "function";
		std::string sPh = "X";
		long long	llTs = 0;
		int			sPid = 0;
		uint32_t	uiTid = 0;

		virtual void writeToStream(std::ofstream& oStream) const = 0;
	};

	struct CompleteEvent : public TraceEvent
	{
		CompleteEvent(std::string sName, std::string sCatagory, std::string sPh, long long llStart, long long llDur, int sPid, uint32_t uiThreadID)
		{
			this->sName		= sName;
			      sCat		= sCatagory;
			this->sPh		= sPh;
			      llTs		= llStart;
			this->llDur		= llDur;
			this->sPid		= sPid;
			      uiTid		= uiThreadID;
		}

		long long llDur = 0;

		void writeToStream(std::ofstream& oStream) const override
		{
			oStream << "{";
			oStream << "\"cat\":\"" << sCat << "\",";
			oStream << "\"dur\":" << llDur << ",";
			oStream << "\"name\":\"" << sName << "\",";
			oStream << "\"ph\":\"" << sPh << "\",";
			oStream << "\"pid\":" << sPid << ",";
			oStream << "\"tid\":" << uiTid << ",";
			oStream << "\"ts\":" << llTs;
			oStream << "}";
		}
	};

}