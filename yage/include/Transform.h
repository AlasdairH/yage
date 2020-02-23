#pragma once

// PCH
#include "PCH.h"

// Program

namespace YAGE
{
	class Transform
	{
	public:
		Transform();

		glm::mat4 getModelMatrix();

		void setPosition(const glm::vec3 &_position);
		void setRotation(const glm::vec3 &_rotation);
		void setScale(const glm::vec3 &_scale);

	protected:
		glm::mat4 m_position_mat4 = glm::mat4(1);
		glm::vec3 m_position_vec3 = glm::vec3(0);
		glm::mat4 m_rotation_mat4 = glm::mat4(1);
		glm::vec3 m_rotation_vec3 = glm::vec3(0);
		glm::mat4 m_scale_mat4 = glm::mat4(1);
		glm::vec3 m_scale_vec3 = glm::vec3(1);

		glm::mat4 m_modelMatrix;

		bool m_modified = false;
	};
}