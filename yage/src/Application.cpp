// stl
#include <vector>

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
#include "GL_Texture.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Transform.h"
#include "Camera.h"
#include "Sprite.h"
#include "Renderer.h"

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
	
	SpriteVector sprites;
	sprites.push_back(Sprite(0));
	sprites.push_back(Sprite(1));

	sprites[0].translate(-3, -0.5f, 0);
	sprites[1].translate( 2, -0.5f, 0);

	VertexBuffer oIndexBuffer(BUFFER_ELEMENT_ARRAY);
	oIndexBuffer.allocate(sizeof(unsigned int) * 12);

	Transform transform;

	Shader shader;
	shader.setTag("Test Shader");
	shader.load("resources/shaders/basic.glsl");
	shader.complete();

	VertexBuffer vbo(BUFFER_ARRAY);
	vbo.setTag("Batch VBO 1");
	vbo.allocate(sizeof(Vertex) * 12);
	for (Sprite& oSprite : sprites)
	{
		oSprite.addToVBO(vbo);
	}
	
	VertexArray vao;
	vao.addBuffer(vbo, Mesh::getLayout());

	Texture oTextureDiffuse;
	oTextureDiffuse.fromFile("1.jpg");
	oTextureDiffuse.setTag("Texture_Diffse");
	Texture oTextureSpecular;
	oTextureSpecular.fromFile("2.jpg");
	oTextureSpecular.setTag("Texture_Specular");

	Camera oMainCamera;
	oMainCamera.setProjectionMode(Camera::ProjectionMode::PROJECTION_ORTHOGRAPHIC);
	oMainCamera.oTransform.setPosition(0, 0, 2);
	oMainCamera.update();

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

		SDL_Event oIncomingEvent;
		while (SDL_PollEvent(&oIncomingEvent))
		{
			if (oIncomingEvent.type == SDL_QUIT)
			{
				LOG(LOG_DEBUG) << "SDL_QUIT event called";
				run = false;
			}

			switch (oIncomingEvent.type)
			{
				case SDL_KEYDOWN:
					switch (oIncomingEvent.key.keysym.sym)
					{
					case SDLK_SPACE:
						if (oMainCamera.getProjectionMode() == Camera::ProjectionMode::PROJECTION_ORTHOGRAPHIC)
						{
							oMainCamera.setProjectionMode(Camera::ProjectionMode::PROJECTION_PERSPECTIVE);
						}
						else
						{
							oMainCamera.setProjectionMode(Camera::ProjectionMode::PROJECTION_ORTHOGRAPHIC);
						}
						oMainCamera.update();
						LOG(LOG_DEBUG) << "Switching camera projection mode";
						break;

					case SDLK_w:
						oMainCamera.oTransform.translate(0.0f, 0.25f, 0.0f);
						oMainCamera.update();
						break;

					case SDLK_s:
						oMainCamera.oTransform.translate(0.0f, -0.25f, 0.0f);
						oMainCamera.update();
						break;

					case SDLK_a:
						oMainCamera.oTransform.translate(-0.25f, 0.0f, 0.0f);
						oMainCamera.update();
						break;

					case SDLK_d:
						oMainCamera.oTransform.translate(0.25f, 0.0f, 0.0f);
						oMainCamera.update();
						break;

					case SDLK_t:
						sprites[0].translate(0.25f, 0, 0);

					default:
						LOG(LOG_DEBUG) << "Unmapped key pressed";
					}
					break;
			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		oTextureDiffuse.bindToTextureUnit(0);
		oTextureSpecular.bindToTextureUnit(1);
		int iTextures[2] = { 0, 1 };

		shader.bind();
		ShaderModifier::setUniformMat4(shader.getUniformLocation("u_modelMatrix"), transform.getModelMatrix());
		ShaderModifier::setUniform1iv(shader.getUniformLocation("tTextures"), 2, iTextures);
		
		Renderer batchRenderer;
		batchRenderer.renderSpriteBatch(sprites, vao, vbo, oIndexBuffer);

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