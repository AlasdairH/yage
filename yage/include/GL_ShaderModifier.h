#pragma once

// PCH
#include "PCH.h"

// Program
#include "GL_Shader.h"

namespace YAGE
{
	class ShaderModifier
	{
	public:
		static void setUniform4f(const int &_location, const glm::vec4 &_value);

	protected:
		static int getAttributeLocation(Shader &_shader, const std::string &_attribute);
	};
}
