#include "PCH.h"
#include "Camera.h"

namespace YAGE
{
	Camera::Camera()
	{
		// create a camera data uniform buffer
		std::shared_ptr<VertexBuffer> cameraDataUniformBuffer = std::make_shared<VertexBuffer>(BUFFER_UNIFORM);
		// link the uniform buffer to the binding point
		mpoMatrixUniformBuffer->bindBase(GL_UNIFORM_BUFFER, SHADER_BINDPOINT_CAMERA_VP);
		// load the data to the uniform buffer
		//mpoMatrixUniformBuffer->loadData(&camera.getCameraUniformData(), 0, sizeof(CameraMatrixData));
	}

	Camera::~Camera()
	{

	}

	void Camera::cleanViewMatrix()
	{

	}

	glm::mat4 Camera::getProjectionMatrix()
	{
		if (m_projectionMode == PROJECTION_PERSPECTIVE)
		{
			return mmat4PerspectiveProjectionMatrix;
		}
		else if (m_projectionMode == PROJECTION_ORTHOGRAPHIC)
		{
			return mmat4OrthographicProjectionMatrix;
		}
		return mmat4PerspectiveProjectionMatrix;
	}

	void Camera::updateCameraUniform()
	{
		cleanViewMatrix();
		// grab the new matrices
		moUniformData.viewMatrix = glm::mat4(0);
		moUniformData.projectionMatrix = getProjectionMatrix();
		moUniformData.viewProjectionMatrix = getProjectionMatrix() * moUniformData.viewMatrix;
	}
}