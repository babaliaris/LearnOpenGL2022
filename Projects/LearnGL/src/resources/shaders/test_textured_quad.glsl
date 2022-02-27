#shader vertex
#version 330

layout(location=0) in vec3 aPos;
layout(location=1) in vec2 aTexCoord;

out vec2 texCoords;

void main()
{
	gl_Position = vec4(aPos, 1);

	texCoords = aTexCoord;
}





#shader fragment
#version 330

in vec2 texCoords;

uniform sampler2D texSlot;

out vec4 Color;

void main()
{
	Color = texture(texSlot, texCoords);
}