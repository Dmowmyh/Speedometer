#version 140

in vec3 aPos;
in vec3 aColor;
in vec2 aTexCoord;

uniform mat4 aTransform;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
	gl_Position = aTransform*vec4(aPos, 1.0);
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
