#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>

float r1 = 5, r2 = 10, h = 10;


void display() {
	float angle;
	bool colorFlag1 = true;
	bool colorFlag2 = true;
	bool colorFlag3 = true;

	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(100, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 100, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 100);
	glEnd();



	glBegin(GL_TRIANGLE_STRIP);	
	for (angle = 0; angle<2 * 3.14; angle += 0.1)
	{
		if (colorFlag1)
		{
			glColor3f(1, 1, 1);
		}
		else
		{
			glColor3f(0, 0, 0);
		}
		glVertex3f(r1*cos(angle), h, -r1*sin(angle));
		glVertex3f(r2*cos(angle), 0, -r2*sin(angle));

		colorFlag1 = !colorFlag1;
	}
	glVertex3f(r1*cos(0), h, -r1*sin(0));
	glVertex3f(r2*cos(0), 0, -r2*sin(0));
	glEnd();


	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, h, 0);
	for (angle = 0; angle<2 * 3.14; angle += 0.1)
	{
		if (colorFlag2)
		{
			glColor3f(1, 1, 1);
		}
		else
		{
			glColor3f(0, 0, 0);
		}
		glVertex3f(r1*cos(angle), h , -r1*sin(angle));
		colorFlag2 = !colorFlag2;
	}
	glVertex3f(r1*cos(0), h, -r1*sin(0));
	glEnd();


	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, 0);
	for (angle = 0; angle<2 * 3.14; angle += 0.1)
	{	
		if (colorFlag3)
		{
			glColor3f(1, 1, 1);
		}
		else
		{
			glColor3f(0, 0, 0);
		}
		glVertex3f(r2*cos(angle), 0, -r2*sin(angle));
		colorFlag3 = !colorFlag3;
	}
	glVertex3f(r2*cos(0), 0, -r2*sin(0));
	glEnd();
	
	glFlush();
}

void init() {
	glClearColor(0.2, 0.2, 0.2, 0);
}

void reshape(int width,int height) {
	glViewport(0, 0, width, height);	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20, 20, -20, 20, -20, 20);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(5, 5, 5, 0, 0, 0, 0, 1, 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LEQUAL);

}

void mykey(unsigned char key,int x,int y) {
	if (key == 'Q' || key == 'q') {
		r1 += 1;	
	}
	else if (key == 'E' || key == 'e') {
		r2 += 1;
	}
	glutPostRedisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("1");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(mykey);
	init();

	glutMainLoop();
}