#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "Shader.h"
#include "stb_image.h"

float vertices[] = 
{
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};

unsigned int shaderProgram;
unsigned int VBO;

void render()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glFinish();
	//glutSwapBuffers();
}

int main(int argc, char** argv)
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Speedometer");
	glewInit();

	glGenBuffers(1, &VBO);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	Shader shader("/home/mario/Workspace/Speedometer/vertex.glsl",
			"/home/mario/Workspace/Speedometer/fragment.glsl");
	int pos = glGetAttribLocation(shader.GetID(), "aPos");
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(pos);
	shader.Use();

	glutDisplayFunc(render);
	glutMainLoop();
	return 0;
}

