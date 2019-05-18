[[VERTEX]]
#version 430 core
layout (location = 0) in vec3 buffer_pos;

void main()
{
    gl_Position = vec4(buffer_pos.xyz, 1.0);
}

[[FRAGMENT]]
#version 430 core
out vec4 fragColour;

void main()
{
    fragColour = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}