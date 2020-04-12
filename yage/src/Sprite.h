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
		~Sprite();

		inline bool isDirty() { return mbDirty; }
		inline void setClean() { mbDirty = false; }

		void addToVBO(VertexBuffer& oBuffer);
		void modifyInVBO(VertexBuffer& oBuffer);

		const static int iIndicies[6];

	protected:
		Mesh moMeshVertices;

		bool mbDirty = true;
		int muiVBOID = 0;

		unsigned int muiBufferOffset = 0; // The offset from the start of the VBO this sprite sits at

		static int miSpriteInstance;
		
	};

	typedef std::vector<Sprite> SpriteVector;
}