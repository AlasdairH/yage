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

uniform mat4 u_modelMatrix;

out vec2 v2TexCoord;

void main()
{
    vec4 vertPosition = vec4(u_modelMatrix * (vec4(buffer_position.xyz, 1.0)));

	mat4 VP = projectionMatrix * viewMatrix;

	v2TexCoord = buffer_textureCoordinates;

    gl_Position = VP * vertPosition;
}

[[FRAGMENT]]
#version 430 core

layout (binding = 0) uniform sampler2D tDiffuse;
layout (binding = 1) uniform sampler2D tSpecular;

uniform vec4 u_colour = vec4(0.97f, 0.16f, 0.58f, 1.0f);

in vec2 v2TexCoord;

out vec4 fragColour;

void main()
{
    vec4 diffuseColour = texture(tDiffuse, v2TexCoord);
    vec4 specularColour = texture(tSpecular, v2TexCoord);
	fragColour = mix(diffuseColour, specularColour, 0.5f);
	//fragColour = diffuseColour;
	//fragColour = specularColour;
}