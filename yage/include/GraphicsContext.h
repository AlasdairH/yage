#pragma once

// PCH
#include "PCH.h"

// Program
#include "Window.h"

namespace YAGE
{
	/*! @class GraphicsContext
	*	@brief A base class for a graphics context (OpenGL, D3D, etc.)
	*
	*	This class provides the base functionality of a graphics context which must be overridden
	*	with functionality from that context.
	*/
	class GraphicsContext
	{
	public:
		GraphicsContext() { }
		~GraphicsContext() { }

		virtual void swapBuffer() { }

	protected:
		std::shared_ptr<Window>		m_targetWindow;
		bool						m_valid;
	};
}