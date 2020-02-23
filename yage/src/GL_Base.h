#pragma once

// PCH
#include "PCH.h"

// Program
#include "Resource.h"

namespace YAGE
{
	enum GL_BaseType { GL_TYPE_UNKNOWN, GL_TYPE_SHADER, GL_TYPE_VAO, GL_TYPE_VBO, GL_TYPE_TEXTURE };

	/*! @class GL_Base
	*	@brief A base class for all ID'd OpenGL resources
	*
	*	This base class contains a single OpenGL unsigned integar ID which is to be used
	*	as a base class for OpenGL resources. This is so IDs can be retreived when needed
	*	but not modified outside of the class itself.
	*/
	class GL_Base : public Resource
	{
	public:
		inline unsigned int getGlID() { return muiGLID; }

	protected:
		unsigned int	muiGLID = 0;						/**< A unique ID set in the derived constructor */
		GL_BaseType		m_glType = GL_TYPE_UNKNOWN;		/**< The type of OpenGL resource */
	};
}