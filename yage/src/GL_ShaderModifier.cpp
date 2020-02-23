#include "PCH.h"
#include "GL_ShaderModifier.h"

namespace YAGE
{
	void ShaderModifier::setUniform4f(const int& _location, const glm::vec4& _value)
	{
		glUniform4f(_location, _value.x, _value.y, _value.z, _value.w);
	}

	void ShaderModifier::setUniformMat4(const int& _location, const glm::mat4& _value)
	{
		glUniformMatrix4fv(_location, 1, GL_FALSE, &_value[0][0]);
	}
}