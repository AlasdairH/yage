#include "PCH.h"
#include "Camera.h"

namespace YAGE
{
	Camera::Camera()
	{
		// create a camera data uniform buffer
		mpoMatrixUniformBuffer = std::make_shared<VertexBuffer>(BUFFER_UNIFORM);
		mpoMatrixUniformBuffer->allocate(sizeof(CameraMatrixData));
		// link the uniform buffer to the binding point
		mpoMatrixUniformBuffer->bindBase(GL_UNIFORM_BUFFER, SHADER_BINDPOINT_CAMERA_VP);

		mfAspect = static_cast<float>(miViewportWidth) / static_cast<float>(miViewportHeight);

		// load the data to the uniform buffer
		mpoMatrixUniformBuffer->loadData(&moUniformData, 0, sizeof(CameraMatrixData));
	}

	Camera::~Camera()
	{

	}

	void Camera::cleanViewMatrix()
	{
		recalculateProjectionMatrix();
	}

	void Camera::recalculateProjectionMatrix()
	{
		if (meProjectionMode == PROJECTION_PERSPECTIVE)
		{
			moMat4ProjectionMatrix = glm::perspective(mfFovRad, mfAspect, 0.1f, 100.0f);
		}
		else if (meProjectionMode == PROJECTION_ORTHOGRAPHIC)
		{
			float fOrthoHeight = glm::degrees(mfFovRad) / 4;
			float fOrthoWidth = fOrthoHeight * mfAspect;
			float fDivisor = 10;
			moMat4ProjectionMatrix = glm::ortho(-(fOrthoWidth / fDivisor), fOrthoWidth / fDivisor, -(fOrthoHeight / fDivisor), fOrthoHeight / fDivisor, 0.0f, 10.0f);
		}
	}

	void Camera::setProjectionMode(ProjectionMode eMode)
	{
		meProjectionMode = eMode;
		recalculateProjectionMatrix();
	}

	Camera::ProjectionMode Camera::getProjectionMode()
	{
		return meProjectionMode;
	}

	glm::mat4 Camera::getProjectionMatrix()
	{
		return moMat4ProjectionMatrix;
	}

	void Camera::updateCameraUniform()
	{
		moUniformData.viewMatrix = glm::lookAt(oTransform.getPosition(), oTransform.getPosition() + moFront, moUp);
		moUniformData.projectionMatrix = moMat4ProjectionMatrix;
		moUniformData.viewProjectionMatrix = moMat4ProjectionMatrix * moUniformData.viewMatrix;

		mpoMatrixUniformBuffer->loadData(&moUniformData, 0, sizeof(CameraMatrixData));
	}
}