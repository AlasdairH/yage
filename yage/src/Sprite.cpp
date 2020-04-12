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

		moMeshVertices.addVertex({ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0), glm::vec2(0, 1), 0 });
		moMeshVertices.addVertex({ glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0), glm::vec2(1, 1), 0 });
		moMeshVertices.addVertex({ glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0), glm::vec2(1, 0), 0 });
		moMeshVertices.addVertex({ glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0), glm::vec2(0, 0), 0 });
	}

	Sprite::Sprite(const int iTextureUnit)
	{
		moMeshVertices.setTag("Sprite" + std::to_string(miSpriteInstance));
		++miSpriteInstance;

		moMeshVertices.addVertex({ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0), glm::vec2(0, 1), iTextureUnit });
		moMeshVertices.addVertex({ glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0), glm::vec2(1, 1), iTextureUnit });
		moMeshVertices.addVertex({ glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0), glm::vec2(1, 0), iTextureUnit });
		moMeshVertices.addVertex({ glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0), glm::vec2(0, 0), iTextureUnit });
	}

	Sprite::~Sprite()
	{

	}

	void Sprite::setPosition(const float fX, const float fY, const float fZ)
	{
		setPosition(glm::vec3(fX, fY, fZ));
	}

	void Sprite::setPosition(const glm::vec3& roPosition)
	{
		moPosition = roPosition;
		mbDirty = true;
		
	}

	void Sprite::translate(const float fX, const float fY, const float fZ)
	{
		translate(glm::vec3(fX, fY, fZ));
	}

	void Sprite::translate(const glm::vec3& roTranslation)
	{
		moPosition += roTranslation;
		mbDirty = true;

		moMeshVertices.translate(roTranslation);
	}

	void Sprite::addToVBO(VertexBuffer& oBuffer)
	{
		muiBufferOffset = moMeshVertices.addToVertexBuffer(oBuffer);
	}

	void Sprite::modifyInVBO(VertexBuffer& oBuffer)
	{
		modifyInVBO(oBuffer, muiBufferOffset);
	}
	
	void Sprite::modifyInVBO(VertexBuffer& oBuffer, unsigned int uiBufferOffset)
	{
		oBuffer.bind();

		std::vector<Vertex>* poVertexData = moMeshVertices.getDataPtr();

		unsigned int uiSize = sizeof(Vertex) * (int)poVertexData->size();
		oBuffer.loadSubData(poVertexData->data(), uiSize, uiBufferOffset);
	}
}

