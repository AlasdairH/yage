#include "PCH.h"
#include "Window.h"

namespace YAGE
{
	bool Window::m_initialisedSDL = false;
	bool Window::m_initialisedOpenGL = false;

	Window::Window()
	{
		if (!m_initialisedSDL)
		{
			//CONSOLE_MESSAGE("Initialising SDL");
			// attempt to initialise openGL
			if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0)
			{
				// something went wrong, exit program
				//CONSOLE_ERROR("Unable to Initialise SDL");
			}

			// set OpenGL 4.3
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

			// set attributes
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
			SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 1);

			//CONSOLE_MESSAGE("SDL Initialised");
		}
	}

	Window::~Window()
	{

	}
}