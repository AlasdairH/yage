#include "PCH.h"
#include "Renderer.h"


namespace YAGE
{
	void Renderer::renderBatch(SpriteVector& roSprites, VertexArray& roVAO, VertexBuffer& roVBO, VertexBuffer& roIndexBuffer)
	{
		unsigned int uiIteration = 0;
		std::string ibc;

		for (Sprite& roSprite : roSprites)
		{
			if (roSprite.isDirty())
			{
				LOG(LOG_DEBUG) << "Sending dirty sprite, iteration " << uiIteration;
				roSprite.modifyInVBO(roVBO);

				
				for (int i = 0; i < 6; ++i)
				{
					moIndexBufferMemCache[(uiIteration * 6) + i] = Sprite::iIndicies[i] + (uiIteration * 6);
				}
			}

			roSprite.setClean();

			++uiIteration;
		}

		roIndexBuffer.loadData(moIndexBufferMemCache.data(), uiIteration * 6 * sizeof(unsigned int));

		roVAO.bind();
		roIndexBuffer.bind();

		Transform oTransform;
		oTransform.setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
	}
}