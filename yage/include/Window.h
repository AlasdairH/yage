#pragma once

// PCH
#include "PCH.h"

// Program


namespace YAGE
{
	class Window
	{
	public:
		/** @brief Initialises SDL and OpenGL if required and creates a window
		*	@param _title The Window Title that will be displayed in the OS
		*
		*	The constructor takes default arguments for a standard window but title, width and height can be set
		*	by overwriting these provided values.
		*	The constructor creates an SDL Window, SDL Renderer and an accompanying GL Context.
		*/
		Window(const std::string &_title = "YAGE");
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
