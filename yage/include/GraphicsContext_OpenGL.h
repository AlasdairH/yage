#pragma once

// PCH
#include "PCH.h"

// Program
#include "GraphicsContext.h"
#include "Window.h"

namespace YAGE
{
	class Window;
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(std::shared_ptr<Window> _window);
		~OpenGLContext();

		void swapBuffer() override;

	protected:
		SDL_GLContext	 m_openGLContext;		/**< The GL Context for OpenGL Rendering */
	};
}