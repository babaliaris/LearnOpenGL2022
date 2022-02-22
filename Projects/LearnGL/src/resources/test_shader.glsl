#shader vertex
#version 330

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec4 fragColor;

void main()
{
	fragColor = vec4(aColor, 1);
	gl_Position = vec4(aPos, 1);
}


#shader fragment
#version 330

in vec4 fragColor;
out vec4 oColor;

void main()
{
	oColor = fragColor;
}