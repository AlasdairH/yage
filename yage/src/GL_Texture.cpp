#include "PCH.h"
#include "GL_Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "ext/stbimage.h"

namespace YAGE
{

	Texture::Texture()
	{

	}


	Texture::~Texture()
	{

	}

	bool Texture::fromFile(const std::string& sFilePath)
	{
		int iChannels;
		unsigned char* ucData = stbi_load(sFilePath.c_str(), &miWidth, &miHeight, &iChannels, 0);

		initialize(ucData);
		stbi_image_free(ucData);
		return true;
	}

	void Texture::initialize(unsigned char* mpucData)
	{
		glGenTextures(1, &muiGLID);
		bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (mpucData != nullptr)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, miWidth, miHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, mpucData);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, miWidth, miHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)0);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	void Texture::bind() const
	{
		glBindBuffer(GL_TEXTURE_2D, muiGLID);
	}

	void Texture::unBind()
	{
		glBindBuffer(GL_TEXTURE_2D, 0);
	}

}
