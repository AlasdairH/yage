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
layout (location = 2) in vec3 buffer_textureCoordinates;

uniform mat4 u_modelMatrix;

void main()
{
    vec4 vertPosition = vec4(u_modelMatrix * (vec4(buffer_position.xyz, 1.0)));

	mat4 VP = projectionMatrix * viewMatrix;

    gl_Position = VP * vertPosition;
    //gl_Position = vertPosition;
}

[[FRAGMENT]]
#version 430 core

uniform vec4 u_colour = vec4(0.97f, 0.16f, 0.58f, 1.0f);

out vec4 fragColour;

void main()
{
    fragColour = u_colour;
}