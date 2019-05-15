#include "PCH.h"
#include "ResBase.h"

namespace YAGE
{
	unsigned int ResBase::m_nextUID = 0;

	ResBase::ResBase()
	{
		m_uID = m_nextUID; 
		++m_nextUID;

		LOG(LOG_DEBUG) << "Created resource with uID " << m_uID;
	}
}