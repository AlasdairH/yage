#pragma once
// stl

// external

// program
#include "PCH.h"
#include "GL_VertexArray.h"
#include "GL_VertexBuffer.h"
#include "Sprite.h"
#include "Transform.h"

namespace YAGE
{

	class Renderer
	{
	public:
		void renderBatch(SpriteVector& roSprites, VertexArray& roVAO, VertexBuffer& roVBO, VertexBuffer& roIndexBuffer);

	protected:
		std::array<int, 6 * 10000> moIndexBufferMemCache;
	};

}