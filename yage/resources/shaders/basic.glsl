[[VERTEX]]
#version 430 core

layout (std140) uniform uCameraData
{ 
	mat4 viewMatrix;
	mat4 projectionMatrix;
	mat4 viewProjectionMatrix;
};

layout (location = 0) in vec3 buffer_position;
layout (location = 1) in vec3 buffer_normal;
layout (location = 2) in vec2 buffer_textureCoordinates;
layout (location = 3) in float buffer_textureUnit;

uniform mat4 u_modelMatrix;

out vec2 v2TexCoord;
out float fTextureUnit;

void main()
{
    vec4 vertPosition = vec4(u_modelMatrix * (vec4(buffer_position.xyz, 1.0)));

	mat4 VP = projectionMatrix * viewMatrix;

	v2TexCoord = buffer_textureCoordinates;
	fTextureUnit = buffer_textureUnit;

    gl_Position = VP * vertPosition;
}

[[FRAGMENT]]
#version 430 core

layout (binding = 0) uniform sampler2D tTextures[2];

in vec2 v2TexCoord;
in float fTextureUnit;

out vec4 fragColour;

void main()
{
	int iTexIndex = int(fTextureUnit);
    vec4 diffuseColour = texture(tTextures[iTexIndex], v2TexCoord);
	
	fragColour = diffuseColour;
	
	//fragColour = vec4(v2TexCoord, 0.0f, 1.0f);
}