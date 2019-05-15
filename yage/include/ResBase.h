#pragma once

// PCH
#include "PCH.h"

// Program

namespace YAGE
{
	/*! @class ResBase
	*	@brief A base class for resources which contains a tag and unique ID
	*
	*	Holds the resource name (which can be changed) and a unqiue ID (which cannot be changed) 
	*/
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