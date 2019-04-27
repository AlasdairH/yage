#pragma once

// PCH
#include "PCH.h"

// Program


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

		static bool m_initialisedSDL;
		static bool m_initialisedOpenGL;
	};
}
