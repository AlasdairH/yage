#pragma once
// stl

// external

// program
#include "PCH.h"
#include "Mesh.h"
#include "GL_VertexBuffer.h"


namespace YAGE
{
	
	class Sprite
	{
	public:
		Sprite();
		Sprite(const int iTextureUnit);
		~Sprite();

		void setPosition(const float fX, const float fY, const float fZ);
		void setPosition(const glm::vec3& roPosition);
		void translate(const float fX, const float fY, const float fZ);
		void translate(const glm::vec3& roTranslation);

		inline bool isDirty() { return mbDirty; }
		inline void setClean() { mbDirty = false; }

		void addToVBO(VertexBuffer& oBuffer);
		void modifyInVBO(VertexBuffer& oBuffer);
		void modifyInVBO(VertexBuffer& oBuffer, unsigned int uiBufferOffset);

		const static int iIndicies[6];

	protected:
		Mesh moMeshVertices;

		glm::vec3 moPosition;

		bool mbDirty = true;
		int muiVBOID = 0;

		unsigned int muiBufferOffset = 0; // The offset from the start of the VBO this sprite sits at

		static int miSpriteInstance;
	};

	typedef std::vector<Sprite> SpriteVector;
}