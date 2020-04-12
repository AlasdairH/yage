#include "PCH.h"
#include "Mesh.h"

namespace YAGE
{
	Mesh::Mesh()
	{

	}

	void Mesh::addVertex(const Vertex &_vertex)
	{
		m_vertices.push_back(std::move(_vertex));
		muiSize = sizeof(Vertex) * (int)m_vertices.size();
	}

	unsigned int Mesh::addToVertexBuffer(VertexBuffer &_buffer)
	{
		muiSize = sizeof(Vertex) * (int)m_vertices.size();
		muiOffset = _buffer.addData(m_vertices.data(), muiSize);

		LOG(LOG_DEBUG) << "Added Mesh " << msTag << " to Vertex Buffer " << _buffer.getTag() << " with size " << muiSize;

		return muiOffset;
	}

	VertexBufferLayout Mesh::getLayout()
	{
		VertexBufferLayout layout;
		layout.push<glm::vec3>(1);
		layout.push<glm::vec3>(1);
		layout.push<glm::vec2>(1);
		return layout;
	}
}