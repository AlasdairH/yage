#pragma once

// PCH
#include "PCH.h"

// Program
#include "ResBase.h"

namespace YAGE
{
	enum GL_BaseType { GL_TYPE_UNKNOWN, GL_TYPE_SHADER, GL_TYPE_VAO, GL_TYPE_VBO, GL_TYPE_TEXTURE };

	class GL_Base : public ResBase
	{
	public:
		inline unsigned int getGlID() { return m_glID; }

	protected:
		unsigned int	m_glID = 0;
		GL_BaseType		m_glType = GL_TYPE_UNKNOWN;
	};
}