#include "PCH.h"
#include "Mesh.h"

namespace YAGE
{
	Mesh::Mesh()
	{

	}

	void Mesh::addVertex(const Vertex &_vertex)
	{
		moVertices.push_back(std::move(_vertex));
		muiSize = sizeof(Vertex) * (int)moVertices.size();
	}
	
	// Translates all vertices by a given vec3
	void Mesh::translate(const glm::vec3& roTranslation)
	{
		for (Vertex& roVertex : moVertices)
		{
			roVertex.position += roTranslation;
		}
	}

	// Translates a single vertex by a given vec3
	void Mesh::setVertexPosition(const int ciIndex, const glm::vec3& roPosition)
	{
		if (ciIndex >= moVertices.size() || ciIndex < 0)
		{
			LOG(LOG_WARNING) << "Index out of range, no vertex will be altered";
		}
		else
		{
			moVertices[ciIndex].position = roPosition;
		}
	}

	unsigned int Mesh::addToVertexBuffer(VertexBuffer& roBuffer)
	{
		muiSize = sizeof(Vertex) * (int)moVertices.size();
		muiOffset = roBuffer.addData(moVertices.data(), muiSize);

		LOG(LOG_DEBUG) << "Added Mesh " << msTag << " to Vertex Buffer " << roBuffer.getTag() << " with size " << muiSize;

		return muiOffset;
	}

	VertexBufferLayout Mesh::getLayout()
	{
		VertexBufferLayout layout;
		layout.push<glm::vec3>(1);
		layout.push<glm::vec3>(1);
		layout.push<glm::vec2>(1);
		layout.push<int>(1);
		return layout;
	}
}