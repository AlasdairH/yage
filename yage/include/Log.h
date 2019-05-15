#pragma once

// PCH
#include "PCH.h"

// Program
#include "IOUtilities.h"

namespace YAGE
{
#define LOG(level) \
	if(level < Log::reportingLevel); \
	else Log().getBuffer(level) << "(" << __func__ << ":" << __LINE__ << "): " \

	enum LogLevel { LOG_DEBUG = 0, LOG_WARNING = 1, LOG_ERROR = 2, LOG_MESSAGE = 3};

	/*! @class Log
	*	@brief Log class for a single entry
	*
	*	Holds a single entry of a log file. Statically stores the entire log history which can be
	*	written to whatever source given.
	*/
	class Log
	{
	public:
		Log() { }
		~Log();

		std::ostringstream & getBuffer(const LogLevel &_logLevel);
		static void toFile(const std::string  &_filepath);

		static LogLevel reportingLevel;		/**< The level at which to pass logs */

		static unsigned int getLogCount(const LogLevel& _logLevel);

	protected:
		std::ostringstream m_oStream;				/**< The log entry */

		static std::ostringstream m_logHistory;		/**< The history of all previous logs */
		static unsigned int m_numDebug;				/**< The number of debug logs sent */
		static unsigned int m_numWarning;			/**< The number of warning logs sent */
		static unsigned int m_numError;				/**< The number of error logs sent */
		static unsigned int m_numMessage;			/**< The number of message logs sent */

	};
}
