#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	std::string vertexCode = ReadShaderFromFile(vertexPath);
	std::string fragmentCode = ReadShaderFromFile(fragmentPath);
	CreateShaderProgram(vertexCode, fragmentCode);
}	

void Shader::Init(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	std::string vertexCode = ReadShaderFromFile(vertexPath);
	std::string fragmentCode = ReadShaderFromFile(fragmentPath);
	CreateShaderProgram(vertexCode, fragmentCode);
}	

std::string Shader::ReadShaderFromFile(const std::string& filePath)
{
	std::string shaderCode;
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		file.open(filePath);
		std::stringstream fileStream;
		fileStream << file.rdbuf();
		file.close();
		shaderCode = fileStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << filePath << std::endl;
	}
	return shaderCode; 
}

void Shader::CreateShaderProgram(const std::string& strShaderCode,
		const std::string& strFragmentCode)
{
	const char* vShaderCode = strShaderCode.c_str();
	const char* fShaderCode = strFragmentCode.c_str();
	// 2. compile shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};
 
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};


	m_unID = glCreateProgram();
	glAttachShader(m_unID, vertex);
	glAttachShader(m_unID, fragment);
	glLinkProgram(m_unID);
	glGetProgramiv(m_unID, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(m_unID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// delete the shaders as they're linked into our program now and no longer necessery
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Use()
{
	glUseProgram(m_unID);
}

void Shader::SetUniformVec3(const std::string& name, GLsizei count, const GLfloat* value)
{
	glUniform4fv(glGetUniformLocation(m_unID, name.c_str()), count, value);
}

unsigned int Shader::GetID()
{
	return m_unID;
}
