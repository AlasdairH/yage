#include "PCH.h"
#include "Transform.h"

namespace YAGE
{
	Transform::Transform()
	{
		setPosition(glm::vec3(0));
		setRotation(glm::vec3(0));
		setScale(glm::vec3(1));
	}

	glm::mat4 Transform::getModelMatrix()
	{
		if (!m_modified)
		{
			return m_modelMatrix;
		}
		else
		{
			m_modelMatrix = m_position_mat4 * m_rotation_mat4 * m_scale_mat4;
			m_modified = false;
			return m_modelMatrix;
		}
	}

	void Transform::setPosition(const glm::vec3& _position)
	{
		m_position_vec3 = _position;
		m_position_mat4 = glm::translate(glm::mat4(1), m_position_vec3);

		m_modified = true;
	}
	void Transform::setPosition(const float fX, const float fY, const float fZ)
	{
		setPosition(glm::vec3(fX, fY, fZ));
	}

	void Transform::setRotation(const glm::vec3& _rotation)
	{
		//m_rotation_vec3 = _rotation;
		//m_rotation_mat4 = glm::rotate();
	}

	void Transform::setScale(const glm::vec3& _scale)
	{
		m_scale_vec3 = _scale;
		m_position_mat4 = glm::scale(glm::mat4(1), m_scale_vec3);

		m_modified = true;
	}

	void Transform::translate(const glm::vec3& oTranslation)
	{
		setPosition(getPosition() + oTranslation);
	}

	void Transform::translate(const float fX, const float fY, const float fZ)
	{
		translate(glm::vec3(fX, fY, fZ));
	}
}