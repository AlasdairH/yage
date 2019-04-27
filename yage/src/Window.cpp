#include "PCH.h"
#include "Window.h"

namespace YAGE
{
	bool Window::m_initialisedSDL = false;
	bool Window::m_initialisedOpenGL = false;

	Window::Window(const std::string &_title = "YAGE")
	{
		if (!m_initialisedSDL)
		{
			LOG(LOG_DEBUG) << "Starting SDL initilisation";
			// attempt to initialise openGL
			if (SDL_Init(SDL_INIT_VIDEO) < 0)
			{
				LOG(LOG_ERROR) << "Unable to initialise SDL";
				return;
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

			m_initialisedSDL = true;
			LOG(LOG_DEBUG) << "SDL successfully initialised";
		}

		LOG(LOG_DEBUG) << "Creating window";

		m_window = SDL_CreateWindow("YAGE",
			50, 50,
			1280, 720,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

		m_renderer = SDL_CreateRenderer(m_window, -1, 0);
		m_openGLContext = SDL_GL_CreateContext(m_window);

		LOG(LOG_DEBUG) << "Window created successfully";
	}

	Window::~Window()
	{

	}
}