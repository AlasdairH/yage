#pragma once

#include "PCH.h"

namespace YAGE
{
	class Window
	{
	public:
		Window();
		~Window();

	protected:
		glm::vec2		m_size;
		glm::vec2		m_position;
	};
}
