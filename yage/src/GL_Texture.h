#pragma once

#include <string>

// PCH
#include "PCH.h"

// External
#include "ext/stbimage.h"

// Program
#include "GL_Base.h"


namespace YAGE
{
	class Texture : public GL_Base
	{
	public:
		Texture();
		~Texture();

		bool fromFile(const std::string& sFilePath);

		void bind() const;
		static void unBind();

		void bindToTextureUnit(const unsigned int uiTextureUnit);

	protected:
		void initialize(unsigned char* mpucData);

		int miWidth		= 0;
		int miHeight	= 0;
	};
}


