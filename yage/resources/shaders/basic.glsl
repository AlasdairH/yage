[[VERTEX]]
#version 430 core

layout (location = 0) in vec4 in_pos;

void main()
{
	gl_Position = vec4(in_pos.xyz, 1.0);
}

[[FRAGMENT]]
#version 430 core
out vec4 fragColor;
  
uniform vec4 u_outColor;

void main()
{
    fragColor = u_outColor;
}