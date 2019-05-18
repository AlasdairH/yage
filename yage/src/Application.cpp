// stl

// external

// program
#include "PCH.h"
#include "Window.h"
#include "IOUtilities.h"
#include "GL_Shader.h"
#include "GL_VertexArray.h"
#include "GL_VertexBuffer.h"
#include "GL_VertexBufferLayout.h"

#undef main

using namespace YAGE;

int main()
{
	Window window;
	if (!window.isOpen())
	{
		LOG(LOG_ERROR) << "Something went wrong opening SDL window, program closing";
		return 1;
	}
	OpenGLContext context(std::make_shared<Window>(window));

	Shader shader;
	shader.load("resources/shaders/basic.glsl");
	shader.complete();

	float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
	};
	int numVerticles = sizeof(vertices) / sizeof(float);

	VertexBuffer vbo(BUFFER_ARRAY);
	VertexBufferLayout layout;
	layout.push<float>(3);
	vbo.loadData(vertices, sizeof(vertices));
	VertexArray vao;
	vao.addBuffer(vbo, layout);

	glClearColor(0.97f, 0.16f, 0.58f, 1.0f);

	LOG(LOG_DEBUG) << "Starting main loop";
	bool run = true;
	while (run)
	{
		SDL_Event incomingEvent;
		while (SDL_PollEvent(&incomingEvent))
		{
			if (incomingEvent.type == SDL_QUIT)
			{
				LOG(LOG_DEBUG) << "SDL_QUIT event called";
				run = false;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.bind();
		vao.bind();

		glDrawArrays(GL_TRIANGLES, 0, 3);

		context.swapBuffer();
	}
	LOG(LOG_DEBUG) << "Main loop ended";

	LOG(LOG_MESSAGE) << "Debug: " << Log::getLogCount(LOG_DEBUG) << " | Warning: " << Log::getLogCount(LOG_WARNING) << " | Error: " << Log::getLogCount(LOG_ERROR);
	Log::toFile("log.txt");
	return 0;
}