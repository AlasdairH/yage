#pragma once

// PCH
#include "PCH.h"

// Program

namespace YAGE
{
	struct Vertex
	{
		glm::vec3	position;
		glm::vec3	normal;
		glm::vec2	textureCoordinates;
		int			iTextureUnit;
	};
}