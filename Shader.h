#ifndef SHADER_H
#define SHADER_H
#include <GL/glew.h>
#include <iostream>

class Shader
{
public:
	Shader() = default;
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void Use();
	void Init(const GLchar* vertexPath, const GLchar* fragmentPath);
	std::string ReadShaderFromFile(const std::string& filePath); 
	void CreateShaderProgram(const std::string& strShaderCode,
			const std::string& strFragmentCode);
	void SetUniformVec3(const std::string& name,
			GLsizei count, const GLfloat* value);
	~Shader() = default;
	unsigned int GetID();
private:
	unsigned int m_unID;
};

#endif /* end of include guard SHADER_H */

