#pragma once

// PCH
#include "PCH.h"

// Program

namespace YAGE
{
	/*! @class IOUtilities
	*	@brief Common and basic Input/Output functionality
	*
	*	Provides basic and common functions for loading and saving files
	*/
	class IOUtilities
	{
	public:
		static std::string loadText(const std::string &_filepath);
		static void saveText(const std::string &_filepath, const std::string &_text);

		// TODO: Move
		static std::vector<std::string> split(const std::string& _s, char _delimiter)
		{
			std::vector<std::string> tokens;
			std::string token;
			std::istringstream tokenStream(_s);
			while (std::getline(tokenStream, token, _delimiter))
			{
				tokens.push_back(token);
			}
			return tokens;
		}
	protected:

	};
}