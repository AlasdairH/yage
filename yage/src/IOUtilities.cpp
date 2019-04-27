#include "PCH.h"
#include "IOUtilities.h"

namespace YAGE
{
	std::string IOUtilities::loadText(const std::string &_filepath)
	{
		std::ifstream file;
		file.open(_filepath, std::ofstream::in);
		// error check for successful opening of file
		if (!file.is_open())
		{
			LOG(LOG_ERROR) << "Unable to find file " << _filepath;
			return "NULL";
		}
		else
		{
			std::stringstream text;
			text << file.rdbuf();
			file.close();
			return text.str();
		}
	}
}