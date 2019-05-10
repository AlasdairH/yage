#pragma once

// PCH
#include "PCH.h"

// Program
#include "Window.h"

namespace YAGE
{
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