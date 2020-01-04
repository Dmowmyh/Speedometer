#version 140

in vec3 aPos;
in vec3 aColor;
in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	ourColor = aColor;
	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
