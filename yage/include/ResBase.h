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
		std::string m_tag = "Default Tag";	/**< The name of the resource */

		unsigned int m_uID;					/**< The Unique ID for the resource */
		static unsigned int m_nextUID;		/**< A static number for the next resource ID to be allocated. This is incremented with each new resource */
	};
}