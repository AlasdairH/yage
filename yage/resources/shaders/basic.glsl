[[VERTEX]]
#version 430 core
layout (location = 0) in vec3 buffer_pos;

void main()
{
    gl_Position = vec4(buffer_pos.xyz, 1.0);
}

[[FRAGMENT]]
#version 430 core

uniform vec4 u_colour = vec4(0.97f, 0.16f, 0.58f, 1.0f);

out vec4 fragColour;

void main()
{
    fragColour = u_colour;
}