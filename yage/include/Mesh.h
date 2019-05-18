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

	class Mesh : public ResBase
	{
	public:
		Mesh();

		void addVertex(const Vertex &_vertex);

		void addToVertexBuffer(VertexBuffer &_buffer);

		static VertexBufferLayout getLayout();

	protected:
		std::vector<Vertex> m_vertices;

		std::shared_ptr<VertexBuffer> m_graphicsContainer;
		unsigned int m_offset = 0;
		unsigned int m_size = 0;
	};

}