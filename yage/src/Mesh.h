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

		unsigned int addToVertexBuffer(VertexBuffer &_buffer);

		std::vector<Vertex>* getDataPtr() { return &m_vertices; }

		static VertexBufferLayout getLayout();

	protected:
		std::vector<Vertex> m_vertices;

		std::shared_ptr<VertexBuffer> poGraphicsContainer;
		unsigned int muiOffset = 0;
		unsigned int muiSize = 0;
	};

}