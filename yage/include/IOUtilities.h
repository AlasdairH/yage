#pragma once

// PCH
#include "PCH.h"

// Program

namespace YAGE
{
	class IOUtilities
	{
	public:
		static std::string loadText(const std::string &_filepath);
		static void saveText(const std::string &_filepath, const std::string &_text);

	protected:

	};
}