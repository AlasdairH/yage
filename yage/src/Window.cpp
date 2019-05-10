#include "PCH.h"
#include "Window.h"

namespace YAGE
{
	bool Window::m_initialisedSDL = false;
	bool Window::m_initialisedOpenGL = false;

	Window::Window(const std::string &_title)
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

			LOG(LOG_DEBUG) << "SDL successfully initialised";
		}

		LOG(LOG_DEBUG) << "Creating window";

		m_window = SDL_CreateWindow("YAGE",
			50, 50,
			1280, 720,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

		m_renderer = SDL_CreateRenderer(m_window, -1, 0);

		LOG(LOG_DEBUG) << "Window created successfully";

		m_open = true;
	}

	Window::~Window()
	{

	}
}