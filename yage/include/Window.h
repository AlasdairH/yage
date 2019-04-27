#pragma once

// PCH
#include "PCH.h"

// Program


namespace YAGE
{
	class Window
	{
	public:
		Window();
		~Window();

	protected:
		SDL_Window		*m_window;				/**< A pointer to the SDL_Window. */
		SDL_Renderer	*m_renderer;			/**< A pointer to the SDL_Renderer. */
		SDL_GLContext	 m_openGLContext;		/**< The GL Context for OpenGL Rendering. */

		glm::vec2		m_size;
		glm::vec2		m_position;

		static bool m_initialisedSDL;
		static bool m_initialisedOpenGL;
	};
}
