#include "PCH.h"
#include "GL_VertexBuffer.h"

namespace YAGE
{
	VertexBuffer::VertexBuffer(const VertexBufferType _type)
	{
		m_vertexBufferType = _type;
		init();
	}

	VertexBuffer::VertexBuffer(const VertexBufferType _type, const void *_data, unsigned int _count, unsigned int _size)
	{
		m_vertexBufferType = _type;
		init();
		loadData(_data, _count, _size);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_glID);
		LOG(LOG_DEBUG) << "Vertex Buffer Object with ID: " << m_glID << " Deleted";
	}

	void VertexBuffer::allocate(unsigned int _size)
	{
		bind();
		glBufferData(m_vertexBufferType, _size, NULL, m_usage);
	}

	void VertexBuffer::loadData(const void *_data, unsigned int _count, unsigned int _size)
	{
		m_count = _count;
		bind();
		glBufferData(m_vertexBufferType, _size, _data, m_usage);
	}
	void VertexBuffer::loadData(const void *_data, unsigned int _size)
	{
		m_count = -1;
		bind();
		glBufferData(m_vertexBufferType, _size, _data, m_usage);
	}	
	void VertexBuffer::loadData(const void *_data)
	{
		m_count = -1;
		bind();
		glBufferData(m_vertexBufferType, sizeof(_data), _data, m_usage);
	}

	void VertexBuffer::loadSubData(const void * _data, unsigned int _count, unsigned int _size, int _offset)
	{
		glBufferSubData(m_vertexBufferType, _offset, _size, _data);
	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(m_vertexBufferType, m_glID);
	}
	void VertexBuffer::bind(VertexBufferType _bindPoint) const
	{
		glBindBuffer(_bindPoint, m_glID);
	}

	void VertexBuffer::unBind() const
	{
		glBindBuffer(m_vertexBufferType, 0);
	}

	void VertexBuffer::bindBase(unsigned int _base, unsigned int _index)
	{
		glBindBufferBase(_base, _index, m_glID);
	}

	void VertexBuffer::init()
	{
		glGenBuffers(1, &m_glID);

		// try to guess what the usage pattern will be, can be set otherwise
		if (m_vertexBufferType == BUFFER_ARRAY || m_vertexBufferType == BUFFER_ELEMENT_ARRAY)
		{
			m_usage = GL_STATIC_DRAW;
		}
		else if (m_vertexBufferType == BUFFER_UNIFORM)
		{
			m_usage = GL_DYNAMIC_DRAW;
		}
		else if (m_vertexBufferType == BUFFER_TRANSFORM_FEEDBACK || m_vertexBufferType == BUFFER_ARRAY_TEXTURE)
		{
			m_usage = GL_DYNAMIC_COPY;
		}
		else if (m_vertexBufferType == BUFFER_SHADER_STORAGE)
		{
			m_usage = GL_STATIC_COPY;
		}

		LOG(LOG_DEBUG) << "Vertex Buffer Object with ID: " << m_glID << " Created";
	}
}