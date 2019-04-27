#pragma once

// PCH
#include "PCH.h"

// Program


namespace YAGE
{
	/*! @class Window
	*	@brief An abstraction of the SDL Window class which can be used to create a window for OpenGL rendering
	*
	*	This class uses the SDL Window class to create a window in the constructor. By use of default parameters,
	*	a default window can be created by passing no arguments to the constructor or various settings can be applied.
	*	An OpenGL Context is created with the window for rendering.
	*/
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
		SDL_Window		*m_window;				/**< A pointer to the SDL_Window */
		SDL_Renderer	*m_renderer;			/**< A pointer to the SDL_Renderer */
		SDL_GLContext	 m_openGLContext;		/**< The GL Context for OpenGL Rendering */

		glm::vec2		m_size;					/**< The size of the window in pixels */
		glm::vec2		m_position;				/**< The position in screen space of the window */

		static bool m_initialisedSDL;
		static bool m_initialisedOpenGL;
	};
}
