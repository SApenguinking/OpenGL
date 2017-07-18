#include<stdlib.h>
#include<stdio.h>
#include<Windows.h>
#include<time.h>
#include<GL/glut.h>
#include<math.h>
#define DEG_TO_RAD 0.017453


int hour , minute , second ;
float angle1, angle2, angle3;
//float hour, minute, second;
void drawcircle() {	

	float i=1;
	float points[360][2];
	float points2[360][2];
	int angle;
	float radius = 0.5f;
	float radiusA = 0.04f;
	points[0][0] = radius;
	points[0][1] = 0;

	points2[0][0] = radiusA;
	points2[0][1] = 0;

	for (angle=1; angle < 360; angle++)
	{
		points[angle][0] = points[angle - 1][0] * cos(DEG_TO_RAD*i) - points[angle - 1][1] * sin(DEG_TO_RAD*i);
		points[angle][1] = points[angle - 1][0] * sin(DEG_TO_RAD*i) + points[angle - 1][1] * cos(DEG_TO_RAD*i);
	}


	for (angle = 1; angle < 360; angle++)
	{
		points2[angle][0] = points2[angle - 1][0] * cos(DEG_TO_RAD*i) - points2[angle - 1][1] * sin(DEG_TO_RAD*i);
		points2[angle][1] = points2[angle - 1][0] * sin(DEG_TO_RAD*i) + points2[angle - 1][1] * cos(DEG_TO_RAD*i);
	}
	glColor3f(0.3, 0.7, 0.4);
	glBegin(GL_POLYGON);//绿色Poly
	for (int i = 0; i < 360;i++) {
		glVertex2fv(points[i]);
	}
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);//黑色Poly
	for (int i = 0; i < 360; i++) {
		glVertex2fv(points2[i]);
	}
	glEnd();



	glLineWidth(3.0);
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP);//黑色边线
	for (int i = 0; i < 360; i++)
	{
		glVertex2fv(points[i]);
	}
	glEnd();

	//开始小四边形
	float smallRecWidth = 0.01;
	float smallRecHeight = 0.05;
	float firstSmallRec[4][2] = {-smallRecWidth,radius-smallRecHeight,smallRecWidth,radius-smallRecHeight,smallRecWidth,radius,-smallRecWidth,radius};
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);//12点
	for (int i=0; i < 4; i++) {
		glVertex2fv(firstSmallRec[i]);
	}
	glEnd();


	for (int j = 0; j < 3; j++) {//3、6、9点
		for (int i = 0; i < 4; i++) {
			float a = firstSmallRec[i][0] * cos(DEG_TO_RAD * 90) - firstSmallRec[i][1] * sin(DEG_TO_RAD * 90);
			float b = firstSmallRec[i][0] * sin(DEG_TO_RAD * 90) + firstSmallRec[i][1] * cos(DEG_TO_RAD * 90);
			firstSmallRec[i][0] = a;
			firstSmallRec[i][1] = b;
		}
		glBegin(GL_POLYGON);
		for (int i = 0; i < 4; i++) {
			glVertex2fv(firstSmallRec[i]);
		}
		glEnd();
	}

	//开始大四边形

	float firstBigRec1[4][2] = { -smallRecWidth,radius - 2*smallRecHeight,smallRecWidth,
		radius - 2*smallRecHeight,smallRecWidth,radius,-smallRecWidth,radius };
	float firstBigRec2[4][2] = { -smallRecWidth,radius - 2 * smallRecHeight,smallRecWidth,
		radius - 2 * smallRecHeight,smallRecWidth,radius,-smallRecWidth,radius };

	
	for (int i = 0; i < 4; i++) {
		float a = firstBigRec1[i][0] * cos(DEG_TO_RAD * 30) - firstBigRec1[i][1] * sin(DEG_TO_RAD * 30);
		float b = firstBigRec1[i][0] * sin(DEG_TO_RAD * 30) + firstBigRec1[i][1] * cos(DEG_TO_RAD * 30);
		firstBigRec1[i][0] = a;
		firstBigRec1[i][1] = b;
	}
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);//11点
	for (int i = 0; i < 4; i++) {
		glVertex2fv(firstBigRec1[i]);
	}
	glEnd();

	for (int i = 0; i < 4; i++) {
		float a = firstBigRec1[i][0] * cos(DEG_TO_RAD * 30) - firstBigRec1[i][1] * sin(DEG_TO_RAD * 30);
		float b = firstBigRec1[i][0] * sin(DEG_TO_RAD * 30) + firstBigRec1[i][1] * cos(DEG_TO_RAD * 30);
		firstBigRec2[i][0] = a;
		firstBigRec2[i][1] = b;
	}
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);//10点
	for (int i = 0; i < 4; i++) {
		glVertex2fv(firstBigRec2[i]);
	}
	glEnd();

	for (int i = 0; i < 3; i++) {//8.7.5.4.2.1点
		for (int i = 0; i < 4; i++) {
			float a = firstBigRec1[i][0] * cos(DEG_TO_RAD * 90) - firstBigRec1[i][1] * sin(DEG_TO_RAD * 90);
			float b = firstBigRec1[i][0] * sin(DEG_TO_RAD * 90) + firstBigRec1[i][1] * cos(DEG_TO_RAD * 90);
			firstBigRec1[i][0] = a;
			firstBigRec1[i][1] = b;
		}
		for (int i = 0; i < 4; i++) {
			float a = firstBigRec2[i][0] * cos(DEG_TO_RAD * 90) - firstBigRec2[i][1] * sin(DEG_TO_RAD * 90);
			float b = firstBigRec2[i][0] * sin(DEG_TO_RAD * 90) + firstBigRec2[i][1] * cos(DEG_TO_RAD * 90);
			firstBigRec2[i][0] = a;
			firstBigRec2[i][1] = b;
		}
		glColor3f(0, 0, 0);
		glBegin(GL_POLYGON);
		for (int i = 0; i < 4; i++) {
			glVertex2fv(firstBigRec1[i]);
		}
		glEnd();

		glBegin(GL_POLYGON);
		for (int i = 0; i < 4; i++) {
			glVertex2fv(firstBigRec2[i]);
		}
		glEnd();
	}


	//两条直线
	glLineWidth(1.0);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(-radius, 0);
	glVertex2f(radius, 0);
	glVertex2f(0, radius);
	glVertex2f(0, -radius);
	glEnd();
}

void timerDisplay(float angle1, float angle2, float angle3) {


	float HourWidth = 0.02, HourHeight = 0.2;
	float MinWidth = 0.01, MinHeight = 0.3;
	float SecWidth = 0.005, SecHeight = 0.45;

	float HourTimer[4][2] = { -HourWidth,0,HourWidth,0,HourWidth,HourHeight,-HourWidth,HourHeight };
	float MinTimer[4][2] = { -MinWidth,0,MinWidth,0,MinWidth,MinHeight,-MinWidth,MinHeight };
	float SecTimer[4][2] = { -SecWidth,0,SecWidth,0,SecWidth,SecHeight,-SecWidth,SecHeight };

	float HourTimer2[4][2];
	float MinTimer2[4][2];
	float SecTimer2[4][2];

	for (int i = 0; i < 4; i++) {
		float a = SecTimer[i][0] * cos(DEG_TO_RAD * angle3) - SecTimer[i][1] * sin(DEG_TO_RAD * angle3);
		float b = SecTimer[i][0] * sin(DEG_TO_RAD * angle3) + SecTimer[i][1] * cos(DEG_TO_RAD * angle3);
		SecTimer2[i][0] = a;
		SecTimer2[i][1] = b;
	}
	for (int i = 0; i < 4; i++) {
		float a = MinTimer[i][0] * cos(DEG_TO_RAD * angle2) - MinTimer[i][1] * sin(DEG_TO_RAD * angle2);
		float b = MinTimer[i][0] * sin(DEG_TO_RAD * angle2) + MinTimer[i][1] * cos(DEG_TO_RAD * angle2);
		MinTimer2[i][0] = a;
		MinTimer2[i][1] = b;
	}
	for (int i = 0; i < 4; i++) {
		float a = HourTimer[i][0] * cos(DEG_TO_RAD * angle1) - HourTimer[i][1] * sin(DEG_TO_RAD * angle1);
		float b = HourTimer[i][0] * sin(DEG_TO_RAD * angle1) + HourTimer[i][1] * cos(DEG_TO_RAD * angle1);
		HourTimer2[i][0] = a;
		HourTimer2[i][1] = b;
	}
	
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++) {
		glVertex2fv(SecTimer2[i]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++) {
		glVertex2fv(MinTimer2[i]);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++) {
		glVertex2fv(HourTimer2[i]);
	}
	glEnd();
}



void reshape(int width,int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1, 1, -1, 1);
	glViewport(0, 0, 500, 500);
}


void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	drawcircle();
	timerDisplay(angle1, angle2, angle3);

	glFlush();
}


void init() {
	glClearColor(0.2, 0.2, 0.2,0);
}


void timer(int id) {
	
	
		time_t timep;
		struct tm *p;
	    time(&timep);
		p = localtime(&timep);		hour = p->tm_hour;
		minute = p->tm_min;
		second = p->tm_sec;
	
	angle1 = -(hour / 12.0 * 360 + minute / 60.0 * 30);	angle2 = -(minute / 60.0 * 360);	angle3 = -(second / 60.0 * 360);

	
	glutPostRedisplay();
	glutTimerFunc(1000, timer, 1);
}


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	glutCreateWindow("1");

	glutTimerFunc(1000, timer, 1);
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	
	
	init();

	glutMainLoop();

}
//#include<time.h>
//#include<stdlib.h>
//#include<stdio.h>
//#include <stdio.h>  
//#include <time.h>  
//int main()
//{
//	time_t timep;
//	struct tm *p;
//	time(&timep);
//	p = localtime(&timep); //此函数获得的tm结构体的时间，是已经进行过时区转化为本地时间  
//							//p = gmtime(&timep); //把日期和时间转换为格林威治(GMT)时间的函数  
//
//	printf("Year:  %d\n", 1900 + p->tm_year);
//	printf("Month:  %d\n", 1 + p->tm_mon);
//	printf("Day:  %d\n", p->tm_mday);
//	printf("Hour:  %d\n", p->tm_hour);
//	printf("Minute:  %d\n", p->tm_min);
//	printf("Second:  %d\n", p->tm_sec);
//	printf("Weekday:  %d\n", p->tm_wday);
//	printf("Days:  %d\n", p->tm_yday);
//	printf("Isdst:  %d\n", p->tm_isdst);
//
//	system("pause");
//}