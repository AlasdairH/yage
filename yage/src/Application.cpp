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
#include "Vertex.h"
#include "Mesh.h"
#include "Transform.h"
#include "Camera.h"

#undef main

using namespace YAGE;

int main()
{
#ifdef COMPILE_CONFIG_DEBUG
	c3p::Profiler::get().startSession("yage_startup.json");
#endif

	Window window;
	if (!window.isOpen())
	{
		LOG(LOG_ERROR) << "Something went wrong opening SDL window, program closing";
		return 1;
	}
	OpenGLContext context(std::make_shared<Window>(window));

	Camera oMainCamera;

	Mesh meshLeft;
	meshLeft.setTag("Test Mesh Left");
	meshLeft.addVertex({ glm::vec3(-1.0f, -0.5f, 0.0f), glm::vec3(0), glm::vec3(0) });
	meshLeft.addVertex({ glm::vec3( 0.0f, -0.5f, 0.0f), glm::vec3(0), glm::vec3(0) });
	meshLeft.addVertex({ glm::vec3(-1.0f,  0.5f, 0.0f), glm::vec3(0), glm::vec3(0) });
	Mesh meshRight;
	meshRight.setTag("Test Mesh Right");
	meshRight.addVertex({ glm::vec3(0.0f, -0.5f, 1.0f), glm::vec3(0), glm::vec3(0) });
	meshRight.addVertex({ glm::vec3(1.0f, -0.5f, 1.0f), glm::vec3(0), glm::vec3(0) });
	meshRight.addVertex({ glm::vec3(0.0f,  0.5f, 1.0f), glm::vec3(0), glm::vec3(0) });

	Transform transform;
	

	Shader shader;
	shader.setTag("Test Shader");
	shader.load("resources/shaders/basic.glsl");
	shader.complete();

	VertexBuffer vbo(BUFFER_ARRAY);
	vbo.setTag("Test VBO");
	vbo.allocate(sizeof(Vertex) * 6);
	meshLeft.addToVertexBuffer(vbo);
	meshRight.addToVertexBuffer(vbo);
	
	VertexArray vao;
	vao.addBuffer(vbo, Mesh::getLayout());

	oMainCamera.oTransform.setPosition(0, 0, 2);
	oMainCamera.recalculateProjectionMatrix();
	oMainCamera.updateCameraUniform();

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

#ifdef COMPILE_CONFIG_DEBUG
	c3p::Profiler::get().endSession();
	c3p::Profiler::get().startSession("yage_run.json");
#endif

	LOG(LOG_DEBUG) << "Starting main loop";
	bool run = true;
	while (run)
	{
		c3p::Timer frameTimer("Frame", "scope");

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

		// draw triangle 1
		ShaderModifier::setUniform4f(shader.getUniformLocation("u_colour"), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
		transform.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		ShaderModifier::setUniformMat4(shader.getUniformLocation("u_modelMatrix"), transform.getModelMatrix());
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		// draw triangle 2
		ShaderModifier::setUniform4f(shader.getUniformLocation("u_colour"), glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		transform.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		ShaderModifier::setUniformMat4(shader.getUniformLocation("u_modelMatrix"), transform.getModelMatrix());
		glDrawArrays(GL_TRIANGLES, 3, 3);

		context.swapBuffer();
	}
	LOG(LOG_DEBUG) << "Main loop ended";

#ifdef COMPILE_CONFIG_DEBUG
	c3p::Profiler::get().endSession();
#endif

	LOG(LOG_MESSAGE) << "Debugs: " << Log::getLogCount(LOG_DEBUG) << " | Warnings: " << Log::getLogCount(LOG_WARNING) << " | Errors: " << Log::getLogCount(LOG_ERROR);
	Log::toFile("log.txt");
	return 0;
}