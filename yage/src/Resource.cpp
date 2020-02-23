#include "PCH.h"
#include "Resource.h"

namespace YAGE
{
	unsigned int Resource::m_nextUID = 0;

	Resource::Resource()
	{
		m_uID = m_nextUID; 
		++m_nextUID;

		LOG(LOG_DEBUG) << "Created resource with uID " << m_uID;
	}
}