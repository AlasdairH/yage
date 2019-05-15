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

	unsigned int Log::m_numDebug = 0;
	unsigned int Log::m_numWarning = 0;
	unsigned int Log::m_numError = 0;
	unsigned int Log::m_numMessage = 0;

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
			++m_numDebug;
		}
		else if (_logLevel == LOG_WARNING)
		{
			m_oStream << ":WARNING";
			++m_numWarning;
		}
		else if (_logLevel == LOG_ERROR)
		{
			m_oStream << ":ERROR";
			++m_numError;
		}
		else if (_logLevel == LOG_MESSAGE)
		{
			m_oStream << ":MESSAGE";
			++m_numError;
		}
		else
		{
			m_oStream << ":UNKNOWN";
		}
		return m_oStream;
	}

	void Log::toFile(const std::string &_filepath)
	{
		
		IOUtilities::saveText(_filepath, m_logHistory.str());
		m_logHistory.clear();

		return;
	}
	unsigned int Log::getLogCount(const LogLevel& _logLevel)
	{
		switch (_logLevel)
		{
		case LOG_DEBUG:
			return m_numDebug;
			break;
		case LOG_WARNING:
			return m_numWarning;
			break;
		case LOG_ERROR:
			return m_numError;
			break;
		case LOG_MESSAGE:
			return m_numMessage;
			break;
		default:
			return 0;
		}
	}
}