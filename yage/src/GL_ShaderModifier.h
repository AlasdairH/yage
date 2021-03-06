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
		static void setUniform1i(const int &_location, const int iValue);
		static void setUniform1iv(const int &_location, const int iCount, const int iValue[]);

		static void setUniform4f(const int &_location, const glm::vec4 &_value);

		static void setUniformMat4(const int &_location, const glm::mat4 &_value);

	protected:
		static int getAttributeLocation(Shader &_shader, const std::string &_attribute);
	};
}
