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
		glDeleteBuffers(1, &muiGLID);
		LOG(LOG_DEBUG) << "Vertex Buffer Object with ID: " << muiGLID << " Deleted";
	}

	void VertexBuffer::allocate(unsigned int _size)
	{
		bind();
		glBufferData(m_vertexBufferType, _size, NULL, m_usage);
		m_bufferSize = _size;
		LOG(LOG_DEBUG) << "Allocated " << _size << " bytes to vertex buffer " << msTag;
	}

	void VertexBuffer::loadData(const void *_data, unsigned int _count, unsigned int _size)
	{
		m_count = _count;
		bind();
		glBufferData(m_vertexBufferType, _size, _data, m_usage);
		m_bufferSize = _size;
		m_dataEndPoint = _size;
	}
	void VertexBuffer::loadData(const void *_data, unsigned int _size)
	{
		m_count = -1;
		bind();
		glBufferData(m_vertexBufferType, _size, _data, m_usage);
		m_bufferSize = _size;
		m_dataEndPoint = _size;
	}

	void VertexBuffer::loadSubData(const void * _data, unsigned int _size, int _offset)
	{
		// make sure the sub data fits inside the buffer
		if (_offset + _size > m_bufferSize)
		{
			LOG(LOG_ERROR) << "Unable to load sub data as the size of the data extends over the size of the buffer. Consider allocating more space to the buffer";
			return;
		}

		glBufferSubData(m_vertexBufferType, _offset, _size, _data);
		if (_offset + _size > m_dataEndPoint)
			m_dataEndPoint = _offset + _size;
	}

	unsigned int VertexBuffer::addData(const void *_data, unsigned int _size)
	{
		unsigned int dataOffset = m_dataEndPoint;
		loadSubData(_data, _size, m_dataEndPoint);
		return dataOffset;
	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(m_vertexBufferType, muiGLID);
	}
	void VertexBuffer::bind(VertexBufferType _bindPoint) const
	{
		glBindBuffer(_bindPoint, muiGLID);
	}

	void VertexBuffer::unBind() const
	{
		glBindBuffer(m_vertexBufferType, 0);
	}

	void VertexBuffer::bindBase(unsigned int _base, unsigned int _index)
	{
		glBindBufferBase(_base, _index, muiGLID);
	}

	void VertexBuffer::init()
	{
		glGenBuffers(1, &muiGLID);

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

		LOG(LOG_DEBUG) << "Vertex Buffer Object with ID: " << muiGLID << " Created";
	}
}