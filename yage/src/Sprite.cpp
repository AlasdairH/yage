#include "PCH.h"
#include "Sprite.h"

namespace YAGE
{
	int Sprite::miSpriteInstance = 0;
	const int Sprite::iIndicies[6] = { 0, 1, 2, 2, 3, 0 };

	Sprite::Sprite()
	{
		moMeshVertices.setTag("Sprite" + std::to_string(miSpriteInstance));
		++miSpriteInstance;

		moMeshVertices.addVertex({ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0), glm::vec2(0, 1) });
		moMeshVertices.addVertex({ glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0), glm::vec2(1, 1) });
		moMeshVertices.addVertex({ glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0), glm::vec2(1, 0) });
		moMeshVertices.addVertex({ glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0), glm::vec2(0, 0) });
	}

	Sprite::~Sprite()
	{

	}

	void Sprite::addToVBO(VertexBuffer& oBuffer)
	{
		muiBufferOffset = moMeshVertices.addToVertexBuffer(oBuffer);
	}

	void Sprite::modifyInVBO(VertexBuffer& oBuffer)
	{
		oBuffer.bind();

		std::vector<Vertex>* poVertexData = moMeshVertices.getDataPtr();

		unsigned int uiSize = sizeof(Vertex) * (int)poVertexData->size();
		oBuffer.loadSubData(poVertexData->data(), uiSize, muiBufferOffset);

		LOG(LOG_DEBUG) << muiBufferOffset << ", " << uiSize;
	}
}

