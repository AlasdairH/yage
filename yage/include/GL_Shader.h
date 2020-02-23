#pragma once

// PCH
#include "PCH.h"

// Program
#include "GL_Base.h"

namespace YAGE
{
	/*! @class Shader
	*	@brief An OpenGL Shader Program
	*
	*	This class contains the methods and data for loading files into a shader source
	*	to then be compiled and linked. Any text file can be loaded and parsed with the following
	*	commands:
	*	[[VERTEX]] - All after this line is a vertex shader
	*	[[FRAGMENT]] - All after this line is a fragment shader
	*/
	class Shader : public GL_Base
	{
	friend class ShaderModifier;

	public:
		Shader();
		~Shader();

		void load(const std::string &_file);
		bool complete();

		void bind() { glUseProgram(m_glID); }
		static void unbind();

		int getUniformLocation(const std::string& _uniform);

		/** @brief Gets a Uniform Block Index
		*	@param _name The name of the block to get
		*
		*	The index of the uniform block on the shader
		*/
		GLuint getUniformBlockIndex(const std::string& _name);

		/** @brief Gets a Uniform Block Index
		*	@param _blockIndex The block index name to bind to the binding point
		*	@param _bindingPoint The binding point to bind the block index to
		*
		*	Binds uniform block to binding point
		*/
		void linkUniformBlock(const std::string& _blockIndex, GLuint _bindingPoint);

	protected:
		enum ShaderSourceType { SHADER_SOURCE_UNKNOWN, 
			SHADER_SOURCE_VERTEX =		GL_VERTEX_SHADER, 
			SHADER_SOURCE_FRAGMENT =	GL_FRAGMENT_SHADER };					/**< enum for representing different source shader types */

		void create();
		void attach(const std::string& _source, const ShaderSourceType &_type);

		bool m_linked = false;													/**< Flag showing the compelte state of the shader */

		std::vector<std::pair<unsigned int, ShaderSourceType>> m_attached;		/**< A vector containing the source shader IDs */

		std::unordered_map<std::string, unsigned int> m_uniformLocationCache;	/**< The cache of uniform names to locations */
	};
}