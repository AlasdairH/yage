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
#include "GL_ShaderModifier.h"

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

	std::vector<float> verticesVector = {
	-1.0f, -0.5f, 0.0f,
	 0.0f, -0.5f, 0.0f,
	-1.0f,  0.5f, 0.0f
	};
	std::vector<float> verticesVector2 = {
	0.0f, -0.5f, 0.0f,
	1.0f, -0.5f, 0.0f,
	0.0f,  0.5f, 0.0f
	};

	VertexBuffer vbo(BUFFER_ARRAY);
	VertexBufferLayout layout;
	layout.push<float>(3);
	vbo.allocate(sizeof(float) * verticesVector.size() * 2);
	vbo.addData(verticesVector.data(), sizeof(float) * verticesVector.size());
	vbo.addData(verticesVector2.data(), sizeof(float) * verticesVector2.size());
	VertexArray vao;
	vao.addBuffer(vbo, layout);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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

		ShaderModifier::setUniform4f(shader.getAttributeLocation("u_colour"), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		glDrawArrays(GL_TRIANGLES, 0, 3);
		ShaderModifier::setUniform4f(shader.getAttributeLocation("u_colour"), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		glDrawArrays(GL_TRIANGLES, 3, 3);

		context.swapBuffer();
	}
	LOG(LOG_DEBUG) << "Main loop ended";

	LOG(LOG_MESSAGE) << "Debug: " << Log::getLogCount(LOG_DEBUG) << " | Warning: " << Log::getLogCount(LOG_WARNING) << " | Error: " << Log::getLogCount(LOG_ERROR);
	Log::toFile("log.txt");
	return 0;
}