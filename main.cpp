#include <GL/freeglut_std.h>
#include <iostream>
#include <GL/glut.h>

int main(int argc, char** argv)
{	
	glutInit(&argc, argv);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Speedometer");
	glutMainLoop();
	return 0;
}

