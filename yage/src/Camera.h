#pragma once

// cstdlib
#include <memory>

// external libs

// program
#include "PCH.h"
#include "GL_VertexBuffer.h"
#include "Transform.h"


namespace YAGE
{

	struct CameraMatrixData
	{
		glm::mat4 viewMatrix;			/**< Camera View Matrix data */
		glm::mat4 projectionMatrix;		/**< Camera Projection Matrix data */
		glm::mat4 viewProjectionMatrix;	/**< Combined view and projection matrix */
	};


	class Camera
	{
	public:
		Camera();
		~Camera();

		Transform oTransform;		/**< The transform attribute of the Camera, used for moving it around the world */

		enum ProjectionMode { PROJECTION_PERSPECTIVE, PROJECTION_ORTHOGRAPHIC };

		/** @brief Sets the Field of View
		*	@param _fov The desired Field of View in Radians
		*
		*	Sets the FoV and cleans the projection matrix
		*/
		inline void setFOV(const float _fov) { mfFovRad = _fov; }

		void setProjectionMode(const ProjectionMode eMode);
		Camera::ProjectionMode getProjectionMode();

		/** @brief Return the Projection Matrix
		*	@return The Projection Matrix
		*
		*	Returns the Projection Matrix
		*/
		glm::mat4 getProjectionMatrix();

		/** @brief Update the camera data on the GPU
		*
		*	Takes any modifications on the CPU side and transfers them over to the GPU buffer
		*/
		void update();

	protected:
		void updateCameraUniform();
		void calculateProjectionMatrix();

		ProjectionMode			meProjectionMode	= PROJECTION_PERSPECTIVE;	/**< The current projection matrix */

		float					mfFovRad			=   1.5708f;			/**< The current FoV in radians */
		float					mfAspect			=	0;					/**< The current Aspect Ratio */
		int						miViewportWidth		=	1280;				/**< Width of the viewport in pixels */
		int						miViewportHeight	=	720;				/**< Height of the viewport in pixels */

		glm::vec3				moUp				= glm::vec3(0, 1, 0);	/**< The camera up vector */
		glm::vec3				moFront				= glm::vec3(0, 0, -1);	/**< The vector which points forward */

		glm::mat4				moMat4ProjectionMatrix;						/**< The Perspective Matrix */

		CameraMatrixData		moUniformData;								/**< The struct containing the matrices for the uniform buffer to use */

		std::shared_ptr<VertexBuffer> mpoMatrixUniformBuffer;
	};
}