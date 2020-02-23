#pragma once

// program
#include "PCH.h"
#include "GL_Base.h"


namespace YAGE
{
	enum VertexBufferType {
		BUFFER_ARRAY				= GL_ARRAY_BUFFER, 
		BUFFER_ELEMENT_ARRAY		= GL_ELEMENT_ARRAY_BUFFER,
		BUFFER_UNIFORM				= GL_UNIFORM_BUFFER, 
		BUFFER_TRANSFORM_FEEDBACK	= GL_TRANSFORM_FEEDBACK_BUFFER,
		BUFFER_ARRAY_TEXTURE		= GL_TEXTURE_BUFFER, 
		BUFFER_SHADER_STORAGE		= GL_SHADER_STORAGE_BUFFER,
		BUFFER_UNKNOWN				= -1
	};

	/*! @class VertexBuffer
	*	@brief An abstraction of an OpenGL Vertex Bufer Object (VBO).
	*
	*	An anstraction of the OpenGL Vertex Buffer Object (VBO). This is used by the VertexArray class along with a VertexBufferLayout for drawing objects.
	*/
	class VertexBuffer : public GL_Base
	{
	public:
		/** @brief Vertex Buffer Ctor
		*	@param _type The VBO type to create
		*
		*	Generates a Vertex Buffer Object (VBO) for use by OpenGL of the specified type.
		*/
		VertexBuffer(const VertexBufferType _type);
		/** @brief Vertex Buffer Ctor
		*	@param _type The VBO type to create
		*	@param _data The data to send to the VBO
		*	@param _count The number of items of data
		*	@param _size The size of the data in bytes
		*
		*	Generates a Vertex Buffer Object (VBO) through the init() method for use by OpenGL of the specified type. Also sends the specified data to the VBO with the size provided.
		*/
		VertexBuffer(const VertexBufferType _type, const void *_data, unsigned int _count, unsigned int _size);
		/** @brief Vertex Buffer Dtor
		*
		*	Deletes the Vertex Buffer
		*/
		~VertexBuffer();

		/** @brief Allocates a chunk of data on the GPU for this buffer
		*	@param _size The size of the chunk to allocate in bytes
		*
		*	Allocates a chunk of data on the GPU
		*/
		void allocate(unsigned int _size);

		/** @brief Loads data to the VBO.
		*	@param _data he data to send to the VBO
		*	@param _count The number of items of data
		*	@param _size The size of the data in bytes
		*
		*	Loads data to the VBO.
		*/
		void loadData(const void *_data, unsigned int _count, unsigned int _size);
		/** @brief Loads data to the VBO.
		*	@param _data he data to send to the VBO
		*	@param _size The size of the data in bytes
		*
		*	Loads data to the VBO.
		*/
		void loadData(const void *_data, unsigned int _size);

		/** @brief Loads data to the VBO.
		*	@param _data he data to send to the VBO
		*	@param _size The size of the data in bytes
		*	@param _offset The offset of where to start writing form
		*
		*	Loads data to the VBO at a set point and for a set size
		*/
		void loadSubData(const void * _data, unsigned int _size, int _offset);

		/** @brief Adds data to the VBO
		*	@param _data he data to add to the VBO
		*	@param _size The size of the data in bytes
		*	@return The offset at which the data was written to
		*
		*	Adds data to the VBO from the point of the last item of data. The loadSubData method will check to make sure
		*	the data does not go over the bounds of the buffer.
		*/
		unsigned int addData(const void *_data, unsigned int _size);

		/** @brief Returns the count of the number of items contained within the buffer.
		*	@return The count
		*
		*	Returns the count of the number of items contained within the buffer.
		*/
		inline unsigned int getCount() const { return m_count; }

		/** @brief Binds the VBO.
		*
		*	Binds the VBO.
		*/
		void bind() const;
		/** @brief Binds the VBO.
		*	@param _bindPoint The custom bind point to bind the VBO to
		*
		*	Binds the VBO to a specified point
		*/
		void bind(VertexBufferType _bindPoint) const;

		/** @brief Unbinds the VBO.
		*
		* Unbinds the VBO.
		*/
		void unBind() const;

		/** @brief Bind the buffer to an indexed buffer target
		*	@param _base The target of the bind operation
		*	@param _index The index of the binding point
		*
		*	Binds the buffer object buffer to the binding point at index index of the array of targets specified by target. (Copied from Kkronos.org)
		*/
		void bindBase(unsigned int _base, unsigned int _index);

	protected:
		/** @brief
		*
		*	Generates the VBO. This is done through this method to avoid issues of using OpenGL calls in constructors.
		*/
		void init();

		VertexBufferType	m_vertexBufferType = BUFFER_UNKNOWN;	/**< The type of Vertex Buffer (BUFFER_ARRAY, BUFFER_ELEMENT_ARRAY, etc)  */
		unsigned int		m_count = 0;							/**< The number of items of data there is in the buffer */

		unsigned int		m_usage = GL_STATIC_DRAW;				/**< The usage pattern for the buffer */

		unsigned int		m_bufferSize = 0;
		unsigned int		m_dataEndPoint = 0;
	};
}
