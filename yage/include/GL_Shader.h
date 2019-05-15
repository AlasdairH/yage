#pragma once

// PCH
#include "PCH.h"

// Program
#include "GL_Base.h"

namespace YAGE
{
	class Shader : public GL_Base
	{
	public:
		Shader();
		~Shader();

		void load(const std::string &_file);
		bool complete();

	protected:
		enum ShaderSourceType { SHADER_SOURCE_UNKNOWN, 
			SHADER_SOURCE_VERTEX =		GL_VERTEX_SHADER, 
			SHADER_SOURCE_FRAGMENT =	GL_FRAGMENT_SHADER };

		void create();
		void attach(const std::string& _source, const ShaderSourceType &_type);

		bool m_linked = false;

		std::vector<std::pair<unsigned int, ShaderSourceType>> m_attached;
	};
}