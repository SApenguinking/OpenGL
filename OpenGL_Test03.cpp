#include<gl\glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define WallDepth 8
#define WallWidth 4
#define WallHeight 4
#define BMP_Header_Length 54

GLuint texture1, texture2, texture3, texture4;

float mouseDeltaX, mouseDeltaY;
float materialDeltaR = 0, materialDeltaG = 0, materialDeltaB = 0;

float light0_x = 1.5, light0_y = 1.5, light0_z = -3;
float windowW = 500, windowH = 500;
float eyez = 6;

float light0_position[4] = { light0_x,light0_y,light0_z,1 };
float light0_mirror_position[4] = { light0_x,-light0_y,light0_z,1 };
float light0_ambient[4] = { 1,1,1,1 };
float light0_diffuse[4] = { 1,1,1,1 };
float light0_specular[4] = { 1,1,1,1 };

float light1_position[4] = { -4,4,-4,0 };
float light1_direction[3] = { 1,-1,1 };
float light1_ambient[4] = { 1,1,1,1 };
float light1_diffuse[4] = { 1,1,1,1 };
float light1_specular[4] = { 1,1,1,1 };

float WallMaterial_ambient[4] = { 0.2, 0.25, 0.45, 1.0 };float WallMaterial_diffuse[4] = { 0.2, 0.2, 0.2, 1.0 };float WallMaterial_specular[4] = { 0.2, 0.2, 0.2, 1.0 };float WallMaterial_shiness = 64.0;float FloorMaterial_ambient[4] = { 0.2, 0.2, 0.2, 0.5 };float FloorMaterial_diffuse[4] = { 0.2, 0.2, 0.2, 0.5 };float FloorMaterial_specular[4] = { 0.2, 0.2, 0.2, 0.5 };float FloorMaterial_shiness = 64.0;
float LightballShiness[4] = { 1,1,1,1 };

void creatZandQ() {
	float TMaterial_ambient[4] = { 0.2 + materialDeltaR, 0.3 + materialDeltaG, 0.3 + materialDeltaB, 1.0 };	float TMaterial_diffuse[4] = { 0.1, 0.5, 0.3, 1.0 };	float TMaterial_specular[4] = { 0.8, 0.8, 0.8, 1.0 };	float TMaterial_shiness = 70.0;
	float SMaterial_ambient[4] = { 0.5 + materialDeltaR, 0.2 + materialDeltaG, 0.35 + materialDeltaB, 1.0 };	float SMaterial_diffuse[4] = { 0.5, 0.2, 0.35, 1.0 };	float SMaterial_specular[4] = { 0.8, 0.8, 0.8, 1.0 };	float SMaterial_shiness = 70.0;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, TMaterial_ambient);	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, TMaterial_diffuse);	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, TMaterial_specular);	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, TMaterial_shiness);

	glPushMatrix();
	glTranslated(-2, -3, -7);
	glutSolidSphere(1, 100, 100);
	glPopMatrix();

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, SMaterial_ambient);	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, SMaterial_diffuse);	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, SMaterial_specular);	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, SMaterial_shiness);
	glPushMatrix();
	glTranslated(2, -4, -7);
	glRotatef(-90, 1, 0, 0);
	glutSolidCone(1, 4, 100, 100);
	glPopMatrix();
}

void creatWalls() {
	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, WallMaterial_ambient);	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, WallMaterial_diffuse);	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, WallMaterial_specular);	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, WallMaterial_shiness);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture1);
	glBegin(GL_QUADS);
	glNormal3f(0, 0, 1);
	glTexCoord2f(0.0f, 0);
	glVertex3f(WallWidth, -WallHeight, -WallDepth);
	glTexCoord2f(0.0f, 1);
	glVertex3f(WallWidth, WallHeight, -WallDepth);
	glTexCoord2f(1, 1);
	glVertex3f(-WallWidth, WallHeight, -WallDepth);
	glTexCoord2f(1, 0.0f);
	glVertex3f(-WallWidth, -WallHeight, -WallDepth);
	glEnd();


	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glTexCoord2f(0.0f, 0);
	glVertex3f(-WallWidth, -WallHeight, WallDepth);
	glTexCoord2f(0.0f, 1);
	glVertex3f(-WallWidth, WallHeight, WallDepth);
	glTexCoord2f(1, 1);
	glVertex3f(-WallWidth, WallHeight, -WallDepth);
	glTexCoord2f(1, 0.0f);
	glVertex3f(-WallWidth, -WallHeight, -WallDepth);
	glEnd();


	glBegin(GL_QUADS);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0.0f, 0);
	glVertex3f(WallWidth, -WallHeight, -WallDepth);
	glTexCoord2f(0.0f, 1);
	glVertex3f(WallWidth, -WallHeight, WallDepth);
	glTexCoord2f(1, 1);
	glVertex3f(WallWidth, WallHeight, WallDepth);
	glTexCoord2f(1, 0.0f);
	glVertex3f(WallWidth, WallHeight, -WallDepth);
	glEnd();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void creatGround() {	glEnable(GL_TEXTURE_2D);	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	glBegin(GL_QUADS);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexCoord2f(0.0f, 0);
	glVertex3f(WallWidth, -WallHeight, -WallDepth);
	glTexCoord2f(0.0f, 1);
	glVertex3f(-WallWidth, -WallHeight, -WallDepth);
	glTexCoord2f(0.0f, 1);
	glVertex3f(-WallWidth, -WallHeight, WallDepth);
	glTexCoord2f(1, 0.0f);
	glVertex3f(WallWidth, -WallHeight, WallDepth);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void lightBall() {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, LightballShiness);
	glPushMatrix();
	glTranslated(mouseDeltaX / 10, mouseDeltaY / 10, 0);
	glTranslated(light0_x, light0_y, light0_z);
	glutSolidSphere(0.2, 100, 100);
	glPopMatrix();
}

void RenderScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 15);
	gluLookAt(0, -3, eyez, 0, -3, 0, 0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();	glPushMatrix();	glTranslated(mouseDeltaX / 10, -mouseDeltaY / 10, 0);	glLightfv(GL_LIGHT0, GL_POSITION, light0_mirror_position);	glPopMatrix();	glPushMatrix();	glFrontFace(GL_CW);	glTranslated(0, -8, 0);	glScalef(1.0f, -1.0f, 1.0f);	creatWalls();	creatZandQ();	glFrontFace(GL_CCW);	glPopMatrix();	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	creatGround();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);

	glPushMatrix();
	glTranslated(mouseDeltaX / 10, mouseDeltaY / 10, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);	glPopMatrix();	creatWalls();	creatZandQ();	lightBall();	glPopMatrix();
	glutSwapBuffers();
}

int powerOfTwo(int n) {
	if (n <= 0)
		return 0;

	return (n & (n - 1)) == 0;
}

GLuint loadTexture(const char* fileName) {
	GLint texWidth, texHeight, totalBytes;
	GLubyte* pixels = 0;
	GLint lastTextureID;
	GLuint textureID = 0;

	FILE* pFile = fopen(fileName, "rb");
	if (pFile == 0)
		return 0;

	fseek(pFile, 0x0012, SEEK_SET);

	fread(&texWidth, 4, 1, pFile);
	fread(&texHeight, 4, 1, pFile);

	fseek(pFile, BMP_Header_Length, SEEK_SET);

	{
		GLint lineBytes = texWidth * 3;
		while (lineBytes % 4 != 0)
			++lineBytes;
		totalBytes = lineBytes * texHeight;
	}

	pixels = (GLubyte*)malloc(totalBytes);
	if (pixels == 0) {
		fclose(pFile);
		return 0;
	}

	if (fread(pixels, totalBytes, 1, pFile) <= 0) {
		free(pixels);
		fclose(pFile);
		return 0;
	}

	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if (!powerOfTwo(texWidth) || !powerOfTwo(texHeight)
			|| texWidth > max || texHeight > max) {
			const GLint newTexWidth = 256;
			const GLint newTexHeight = 256;
			GLint newLineBytes, newTotalBytes;
			GLubyte* newPixels = 0;

			newLineBytes = newTexWidth * 3;
			while (newLineBytes % 4 != 0)
				++newLineBytes;
			newTotalBytes = newLineBytes * newTexHeight;

			newPixels = (GLubyte*)malloc(newTotalBytes);
			if (newPixels == 0) {
				free(pixels);
				fclose(pFile);

				return 0;
			}

			gluScaleImage(GL_RGB, texWidth, texHeight, GL_UNSIGNED_BYTE, pixels,
				newTexWidth, newTexHeight, GL_UNSIGNED_BYTE, newPixels);

			free(pixels);

			pixels = newPixels;
			texWidth = newTexWidth;
			texHeight = newTexHeight;
		}
	}

	glGenTextures(1, &textureID);
	if (textureID == 0) {
		free(pixels);
		fclose(pFile);

		return 0;
	}

	glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, lastTextureID);

	free(pixels);

	return textureID;
}



float mouseDownX, mouseDownY;
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON&&state == GLUT_DOWN)
	{
		mouseDownX = x;
		mouseDownY = windowH - y;
	}
}

void motion(int x, int y) {
	float mouseX = x;
	float mouseY = windowH - y;

	mouseDeltaX = mouseX - mouseDownX;
	mouseDeltaY = mouseY - mouseDownY;

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case 'q':
	case 'Q':
		materialDeltaR += 0.1;
		break;
	case 'W':
	case 'w':
		materialDeltaG += 0.1;
		break;
	case 'e':
	case 'E':
		materialDeltaB += 0.1;
	case 'a':
	case 'A':
		materialDeltaR -= 0.1;
		break;
	case 's':
	case 'S':
		materialDeltaG -= 0.1;
		break;
	case 'd':
	case 'D':
		materialDeltaB -= 0.1;
	default:
		break;
	}

	glutPostRedisplay();
}

void init() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);

	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_direction);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 60);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

}

void reshape(int w, int h) {
	windowW = w;
	windowH = h;

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();



	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


bool pointOpen = true, spotOpen = true;
void menuFunc(int data) {
	switch (data)
	{
	case 1:
		if (pointOpen)
		{
			glDisable(GL_LIGHT0);
		}
		else
		{
			glEnable(GL_LIGHT0);
		}
		pointOpen = !pointOpen;
		break;
	case 2:
		if (spotOpen)
		{
			glDisable(GL_LIGHT1);
		}
		else
		{
			glEnable(GL_LIGHT1);
		}
		spotOpen = !spotOpen;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

int menu1;
int	menu2;
void main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(windowW, windowH);
	glutCreateWindow("1");

	glutDisplayFunc(RenderScene);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);


	menu1 = glutCreateMenu(menuFunc);
	glutAddMenuEntry("开/关点光源", 1);
	glutAddMenuEntry("开/关聚光灯", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	texture1 = loadTexture("1.bmp");


	init();

	glutMainLoop();
}