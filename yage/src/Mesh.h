#pragma once

// PCH
#include "PCH.h"

// Program
#include "GL_VertexBuffer.h"
#include "Vertex.h"
#include "GL_VertexBufferLayout.h"

namespace YAGE
{
	/*! @class Mesh
	*	@brief A 3D Mesh
	*
	*	
	*/

	class Mesh : public Resource
	{
	public:
		Mesh();

		void addVertex(const Vertex &_vertex);

		void translate(const glm::vec3& roTranslation);
		void setPosition(const glm::vec3& roPosition);
		void setVertexPosition(const int ciIndex, const glm::vec3& roPosition);

		unsigned int addToVertexBuffer(VertexBuffer &roBuffer);

		std::vector<Vertex>* getDataPtr() { return &moVertices; }

		static VertexBufferLayout getLayout();

	protected:
		std::vector<Vertex> moVertices;

		std::shared_ptr<VertexBuffer> poGraphicsContainer;
		unsigned int muiOffset = 0;
		unsigned int muiSize = 0;
	};

}