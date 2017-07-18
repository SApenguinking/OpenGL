#include<stdlib.h>
#include<stdio.h>
#include<gl/glut.h>
#include<math.h>

int hh = 500, ww = 500;
int xx , yy ;
int clickX, clickY;
int releaseX, releaseY;
int firstPos[3][2] = { 250,250,300,250,250,300 };
int currentPos[3][2] = { 250,250,300,250,250,300 };
int recFirPos[4][2] = { 400,250,450,250,450,300,400,300 };
int recCurPos[4][2] = { 400,250,450,250,450,300,400,300 };
float RGBtri[3] = { 1,1,1 }, RGBrec[3] = { 1,1,1 };
float deltaX;
float deltaY;
int HITS;


void drawObjects(GLenum mode) {
	if (mode == GL_SELECT) glLoadName(1);

	glColor3f(RGBtri[0],RGBtri[1],RGBtri[2]);
	glBegin(GL_TRIANGLES);
	glVertex2i(currentPos[0][0], currentPos[0][1]);
	glVertex2i(currentPos[1][0], currentPos[1][1]);
	glVertex2i(currentPos[2][0], currentPos[2][1]);
	glEnd();

	if (mode == GL_SELECT) glLoadName(2);
	glColor3f(RGBrec[0], RGBrec[1], RGBrec[2]);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++)
	{
		glVertex2f(recCurPos[i][0], recCurPos[i][1]);
	}
	glEnd();
	
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	drawObjects(GL_RENDER);

	glFlush();
}

void myreshape(int width, int height) {
	hh = height;
	ww = width;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,(float)width,0,(float)height);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void processHits(GLint hits, GLuint buffer[]) {
	unsigned int i, j;
	GLint names, *ptr;

	printf("hits = %d\n", hits);
	ptr = (GLint*)buffer;

	for ( i = 0; i < hits; i++)
	{
		names = *ptr;
		ptr += 3;
		for ( j = 0; j < names; j++)
		{
			if (*ptr == 1) {
				printf("triangle\n");
				ptr++;
			}
			else
			{
				printf("rectangle\n");
			}
		}		
	}printf("\n");
}

#define SIZE 512
GLuint selectBuf[SIZE];
void mouseClick(int button, int state, int x, int y) {

		
		GLint hits;
		GLint viewPort[4];	

	if (state==GLUT_DOWN&&button==GLUT_LEFT_BUTTON)
	{	

		clickX = x;
		clickY = hh - y;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 2; j++)
			{
				firstPos[i][j] = currentPos[i][j];
			}
		}
				
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++) {
				recFirPos[i][j] = recCurPos[i][j];
			}
		}

	glGetIntegerv(GL_VIEWPORT, viewPort);

	glSelectBuffer(SIZE, selectBuf);

	glRenderMode(GL_SELECT);//进入选择模式

	glInitNames();
	glPushName(0);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluPickMatrix((double)x, (double)(viewPort[3] - y), 5.0, 5.0, viewPort);
	gluOrtho2D(0, (float)ww, 0, (float)hh);
	
	drawObjects(GL_SELECT);//选择模式绘制

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glFlush();

	hits = glRenderMode(GL_RENDER);

	HITS = hits;

	processHits(hits, selectBuf);
	glutPostRedisplay();
	}
}

void mouseMove(int x, int y) {

	xx = x;
	yy = hh - y;


	if (HITS==1&&selectBuf[3]==1)
	{
		deltaX = xx - clickX;
		deltaY = yy - clickY;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 2; j++)
			{
				if (j == 0)
				{
					currentPos[i][j] = firstPos[i][j] + deltaX;
				}
				else
				{
					currentPos[i][j] = firstPos[i][j] + deltaY;
				}
			}
		}
		
	}
	else if(HITS==1&&selectBuf[3]==2)
	{
		deltaX = xx - clickX;
		deltaY = yy - clickY;

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++) {
				if (j==0)
				{
					recCurPos[i][j] = recFirPos[i][j] + deltaX;
				}
				else
				{
					recCurPos[i][j] = recFirPos[i][j] + deltaY;
				}
			}
		}
	}
	glutPostRedisplay();
}

void init() {

	glClearColor(0.2, 0.2, 0.2, 0);

}

void menuFunc1(int data) {
	switch (data)
	{
	case 1:
		RGBtri[0] = 0.7;
		RGBtri[1] = 0.2;
		RGBtri[2] = 0.3;
		break;
	case 2:
		RGBtri[0] = 0.2;
		RGBtri[1] = 0.6;
		RGBtri[2] = 0.3;
		break;
	case 3:
		RGBtri[0] = 0.2;
		RGBtri[1] = 0.3;
		RGBtri[2] = 0.6;

		break;
	}
	glutPostRedisplay();
}

void menuFunc2(int data) {
	switch (data)
	{
	case 1:
		RGBrec[0] = 0.7;
		RGBrec[1] = 0.2;
		RGBrec[2] = 0.3;
		break;
	case 2:
		RGBrec[0] = 0.2;
		RGBrec[1] = 0.6;
		RGBrec[2] = 0.3;
		break;
	case 3:
		RGBrec[0] = 0.2;
		RGBrec[1] = 0.3;
		RGBrec[2] = 0.6;

		break;
	}
	glutPostRedisplay();
}

void menuFunc(int data) {

}
int Menu1, Menu2,Menu;

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(ww,hh);
	glutCreateWindow("Expriment2");

	Menu1 = glutCreateMenu(menuFunc1);
	glutAddMenuEntry("red", 1);
	glutAddMenuEntry("green", 2);
	glutAddMenuEntry("blue", 3);
	

	Menu2 = glutCreateMenu(menuFunc2);
	glutAddMenuEntry("red", 1);
	glutAddMenuEntry("green", 2);
	glutAddMenuEntry("blue", 3);

	Menu = glutCreateMenu(menuFunc);
	glutAddSubMenu("设置三角形的颜色", Menu1);
	glutAddSubMenu("设置矩形的颜色", Menu2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutReshapeFunc(myreshape);	
	glutDisplayFunc(display);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMove);


	init();

	glutMainLoop();
}
