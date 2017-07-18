#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<gl\glut.h>

#define DEG_TO_RAD 0.017453

int windowWidth, windowHeight;
float radius = 1.0, height = 1.0;
float theta=0;
float camX=1, camY=1, camZ=0;

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.2, 0.5, 0.7);
	glutWireTeapot(300);

	camX = radius*cos(theta*DEG_TO_RAD);
	camY = height;
	camZ = -radius*sin(theta*DEG_TO_RAD);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camX, camY, camZ, 0, 0, 0, 0, 1, 0);
	glFlush();
}


void reshape(int width, int height) {

	windowWidth = width;
	windowHeight = height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-windowWidth, windowHeight, -windowWidth, windowHeight, -windowWidth, windowHeight);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camX, camY, camZ, 0, 0, 0, 0, 1, 0);
	glViewport(0, 0, windowWidth, windowHeight);

}


void keyboardFunc(unsigned char key,int x,int y) {
	if (key=='d'||key=='D')
	{
		theta+=1;
	}
	else if (key == 'a' || key == 'A')
	{
		theta-=1;
	}
	else if (key == 'w' || key == 'W') {
		height+=0.1;
	}
	else if (key == 's' || key == 'S') {
		height-=0.1;
	}
	glutPostRedisplay();
}


void init() {
	glClearColor(0.2, 0.2, 0.2, 0);
}


void main(int argc,char** argv) {
	glutInit(&argc, argv);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("02");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboardFunc);
	init();

	glutMainLoop();
}
