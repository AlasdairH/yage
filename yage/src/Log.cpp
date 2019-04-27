#include "PCH.h"
#include "Log.h"

namespace YAGE
{
#ifdef COMPILE_INCLUDE_LOGGING
	LogLevel Log::reportingLevel = LOG_DEBUG;
#else
	LogLevel Log::reportingLevel = LOG_WARNING;
#endif
	std::ostringstream Log::m_logHistory;

	Log::~Log()
	{
		std::string logString = m_oStream.str() + "\n";
		std::cout << logString;
		m_logHistory << logString;
	}

	std::ostringstream & Log::getBuffer(const LogLevel &_logLevel)
	{
		auto now = std::chrono::system_clock::now();
		auto now_timet = std::chrono::system_clock::to_time_t(now);

		std::time_t const now_c = std::time(NULL);
		m_oStream << std::put_time(std::localtime(&now_c), "%F %T");

		if (_logLevel == LOG_DEBUG)
		{
			m_oStream << ":DEBUG";
		}
		else if (_logLevel == LOG_WARNING)
		{
			m_oStream << ":WARNING";
		}
		else if (_logLevel == LOG_ERROR)
		{
			m_oStream << ":ERROR";
		}
		else
		{
			m_oStream << ":UNKNOWN";
		}
		return m_oStream;
	}

	void Log::toFile(const std::string &_file)
	{
		std::ofstream file;
		file.open(_file, std::ofstream::out);
		// check file opened correctly
		if (!file.is_open())
		{
			LOG(LOG_ERROR) << "Failed to open file " << _file;
			return;
		}
		else
		{
			file << m_logHistory.str();
		}
		file.close();

		return;
	}
}