#include "PCH.h"
#include "GL_ShaderModifier.h"

namespace YAGE
{
	void ShaderModifier::setUniform1i(const int& _location, const int iValue)
	{
		glUniform1i(_location, iValue);
	}

	void ShaderModifier::setUniform1iv(const int& _location, const int iCount, const int iValue[])
	{
		glUniform1iv(_location, iCount, iValue);
	}

	void ShaderModifier::setUniform4f(const int& _location, const glm::vec4& _value)
	{
		glUniform4f(_location, _value.x, _value.y, _value.z, _value.w);
	}

	void ShaderModifier::setUniformMat4(const int& _location, const glm::mat4& _value)
	{
		glUniformMatrix4fv(_location, 1, GL_FALSE, &_value[0][0]);
	}
}