#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "Shader.h"
#include <functional>
#include "ResourceMgr.h"

float vertices[] = 
{
	1.0f, 1.0f, 0.0f,	1.0f, 0.0f, 0.0f,	1.0f, 1.0f,
	1.0f, -1.0f, 0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 0.0f,
	-1.0f, -1.0f, 0.0f,	0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
	-1.0f, 1.0f, 0.0f,	1.0f, 1.0f, 0.0f,	0.0f, 1.0f
};

char indices[] = 
{
	0, 1, 3,
	1, 2, 3
};

unsigned int shaderProgram;
unsigned int VBO;
unsigned int EBO;
unsigned int texture1;
unsigned int texture2;
unsigned int VAO;
Shader shader;
ResourceMgr resourceMgr;

void render()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

	shader.Use();
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(shader.GetID(), "ourTexture"), 0);
	texture1 = resourceMgr.GetResourceID("speedometer.png");
	glBindTexture(GL_TEXTURE_2D, texture1);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
	shader.Use();

	glActiveTexture(GL_TEXTURE1);
	glUniform1i(glGetUniformLocation(shader.GetID(), "ourTexture"), 1);
	texture2 = resourceMgr.GetResourceID("arrow.png");
	glBindTexture(GL_TEXTURE_2D, texture2);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
	glFinish();

	glFinish();

}

void ConfigureVertexAttribute(const std::string& attributeName,
		unsigned short numberOfValues, unsigned short offset)
{
	int attributeId = glGetAttribLocation(shader.GetID(), attributeName.c_str());
	glVertexAttribPointer(attributeId, numberOfValues,
			GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(offset*sizeof(float)));
	glEnableVertexAttribArray(attributeId);
}	

int main(int argc, char** argv)
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Speedometer");
	glewInit();

	shader.Init("/home/mario/Workspace/Speedometer/vertex.glsl",
			"/home/mario/Workspace/Speedometer/fragment.glsl");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	ConfigureVertexAttribute("aPos", 3, 0);
	ConfigureVertexAttribute("aColor", 3, 3);
	ConfigureVertexAttribute("aTexCoord", 2, 6);

	resourceMgr.LoadResource("arrow.png");
	resourceMgr.LoadResource("speedometer.png");

	shader.Use();

	glutDisplayFunc(render);
	glutMainLoop();
	return 0;
}

