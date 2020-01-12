#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include "Shader.h"
#include <functional>
#include "ResourceMgr.h"
#include "PictureDef.h"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "Acceleration.h"

const unsigned int SCREEN_WIDTH = 600;
const unsigned int SCREEN_HEIGHT = 600;

char indices[] = 
{
	0, 1, 3,
	2, 1, 3
};

unsigned int VBO;
unsigned int EBO;
unsigned int VAO;
Shader shader;
ResourceMgr resourceMgr;
Acceleration acceleration;

void ConfigureVertexAttribute(const std::string& attributeName,
		unsigned short numberOfValues, unsigned short offset)
{
	int attributeId = glGetAttribLocation(shader.GetID(), attributeName.c_str());
	glVertexAttribPointer(attributeId, numberOfValues,
			GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(offset*sizeof(float)));
	glEnableVertexAttribArray(attributeId);
}	

void DrawPicture(PictureDef picDef, int x, int y, float degrees)
{
	float topLeftX = (x*2.0f/SCREEN_WIDTH)-1.0f;
	float topLeftY = 1.0f-(y*2.0f/SCREEN_HEIGHT);
	float fWidth = (picDef.Width*2.0f)/SCREEN_WIDTH;
	float fHeight = (picDef.Height*2.0f)/SCREEN_HEIGHT;

	glm::vec2 topLeft {topLeftX, topLeftY};
	glm::vec2 topRight {topLeftX+fWidth, topLeftY};
	glm::vec2 bottomRight {topLeftX+fWidth, topLeftY-fHeight};
	glm::vec2 bottomLeft {topLeftX, topLeftY-fHeight};

	float vertices[] = 
	{
 	        topLeft.x,       topLeft.y,          0.0f,      1.0f, 0.0f, 0.0f, 	0.0f, 1.0f,	
		topRight.x, 	 topRight.y,         0.0f,	0.0f, 1.0f, 0.0f,	1.0f, 1.0f,	
		bottomRight.x, 	 bottomRight.y,      0.0f,	0.0f, 0.0f, 1.0f,	1.0f, 0.0f,	
		bottomLeft.x,    bottomLeft.y,       0.0f,	1.0f, 1.0f, 0.0f,	0.0f, 0.0f,
	};	

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(degrees), glm::vec3(0.0, 0.0, 1.0));

	glUniformMatrix4fv(glGetUniformLocation(shader.GetID(), "aTransform"), 1, GL_FALSE, &trans[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	ConfigureVertexAttribute("aPos", 3, 0);
	ConfigureVertexAttribute("aColor", 3, 3);
	ConfigureVertexAttribute("aTexCoord", 2, 6);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, picDef.ID);

	glUniform1i(glGetUniformLocation(shader.GetID(), "ourTexture"), 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0);

}

void Render()
{
	//glBindVertexArray(VAO);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

	shader.Use();
	//glBindVertexArray(VAO);
	PictureDef speedometer = resourceMgr.GetPicDef("speedometer.png");
	DrawPicture(speedometer, (SCREEN_WIDTH/2)-(speedometer.Width/2), (SCREEN_HEIGHT/2)-(speedometer.Height/2), 0);
	DrawPicture(resourceMgr.GetPicDef("arrow.png"), (SCREEN_WIDTH/2)-(resourceMgr.GetPicDef("arrow.png").Width/2),
			SCREEN_HEIGHT/2-(resourceMgr.GetPicDef("arrow.png").Height/2), acceleration.GetVelocity());
	glutSwapBuffers();
}

void HandleKeydown(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':
			acceleration.HandleKeydown(key, x, y);
			break;
	}
	glutPostRedisplay();
}

void HandleKeyup(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':
			acceleration.HandleKeyup(key, x, y);
			break;
	}
}

int main(int argc, char** argv)
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Speedometer");
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
	glewInit();

	shader.Init("vertex.glsl", "fragment.glsl");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &EBO);
	glGenBuffers(1, &VBO);

	resourceMgr.LoadResource("arrow.png");
	resourceMgr.LoadResource("speedometer.png");

	shader.Use();

	glutKeyboardFunc(HandleKeydown);
	glutKeyboardUpFunc(HandleKeyup);
	glutDisplayFunc(Render);
	glutIdleFunc(Render);
	glutMainLoop();
	return 0;
}

