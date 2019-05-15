#pragma once

// PCH
#include "PCH.h"

// Program

namespace YAGE
{
	class ResBase
	{
	public:
		ResBase();
		std::string getTag() { return m_tag; }
		void setTag(const std::string &_newTag) { m_tag = _newTag; }

	protected:
		std::string m_tag;

		unsigned int m_uID;
		static unsigned int m_nextUID;
	};
}