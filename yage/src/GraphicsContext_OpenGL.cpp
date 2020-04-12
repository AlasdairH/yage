#include "PCH.h"
#include "GraphicsContext_OpenGL.h"

namespace YAGE
{
	OpenGLContext::OpenGLContext(std::shared_ptr<Window> _window)
	{
		m_targetWindow = _window;

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		// set OpenGL 4.3
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

		// set attributes
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 1);

		LOG(LOG_DEBUG) << "Set SDL_GL settings";

		m_openGLContext = SDL_GL_CreateContext(m_targetWindow->getSDLWindow());

		GLenum err = glewInit();
		if (GLEW_OK != err)
		{
			LOG(LOG_ERROR) << "GLEW failed to initialise";
			assert(false);
		}
	}

	OpenGLContext::~OpenGLContext()
	{

	}

	void OpenGLContext::swapBuffer()
	{
		SDL_GL_SwapWindow(m_targetWindow->getSDLWindow());
	}
}