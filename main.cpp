#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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
unsigned int texture;
unsigned int VAO;

void render()
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(VAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);
	glFinish();
}

int main(int argc, char** argv)
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Speedometer");
	glewInit();

	Shader shader("/home/mario/Workspace/Speedometer/vertex.glsl",
			"/home/mario/Workspace/Speedometer/fragment.glsl");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	int pos = glGetAttribLocation(shader.GetID(), "aPos");
	glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)0);
	glEnableVertexAttribArray(pos);

	int color = glGetAttribLocation(shader.GetID(), "aColor");
	glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(color);

	int texCoord = glGetAttribLocation(shader.GetID(), "aTexCoord");
	glVertexAttribPointer(texCoord, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(texCoord);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)*/;
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("/home/mario/Desktop/NE567.png", &width, &height, &nrChannels, STBI_rgb_alpha);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	shader.Use();
	std::cout << texture << std::endl;
	glUniform1i(glGetUniformLocation(shader.GetID(), "ourTexture"), 0);

	glutDisplayFunc(render);
	glutMainLoop();
	return 0;
}

