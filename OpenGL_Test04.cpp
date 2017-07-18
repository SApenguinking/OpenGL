#include<stdlib.h>
#include<gl/glut.h>
#include<math.h>
float t;
float a = 0.5;
float b = 0;
float c = 0.5;

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);
	for (t = 0; t < 2 * 3.14;t+=0.0001) {
		float x = a*t*cos(50*c*t) + b;
		float y = a*t*sin(50*c*t) + b;
		float z = c*t;

		glVertex3f(x, y, z);
	}
	glEnd();

	glBegin(GL_LINES); 
		glVertex3f(0, 0, 0);
		glVertex3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 1);
		glEnd();
	

	glFlush();
}

void myreshape(int width, int height) {
	glViewport(0, 0, 500, 500);
	gluLookAt(0.5, 0.5, 0.5, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

void init() {
	glClearColor(0, 0, 0, 0);

	glColor3f(1.0, 1.0, 1.0);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Expriment1");
	
	glutDisplayFunc(display);
	glutReshapeFunc(myreshape);

	
	init();

	glutMainLoop();
}
