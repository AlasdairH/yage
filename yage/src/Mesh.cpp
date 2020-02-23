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
		m_size = sizeof(Vertex) * (int)m_vertices.size();
	}

	void Mesh::addToVertexBuffer(VertexBuffer &_buffer)
	{
		m_size = sizeof(Vertex) * (int)m_vertices.size();
		m_graphicsContainer = std::make_shared<VertexBuffer>(_buffer);
		m_offset = _buffer.addData(m_vertices.data(), m_size);

		LOG(LOG_DEBUG) << "Added Mesh " << m_tag << " to Vertex Buffer " << _buffer.getTag() << " with size " << m_size;
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