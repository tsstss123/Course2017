#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
const double DEG_TO_RAD = 0.017453;

float points[360][2];
float points2[360][2];
float radius = 0.5f;
float radiusA = 0.04f;

void createDial() {
	glColor3f(0.9, 0.9, 0.9);
	glBegin(GL_POLYGON);//绿色Poly
	for (int i = 0; i < 360; i++) {
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
}
void createScale() {
	//开始小四边形
	float smallRecWidth = 0.01;
	float smallRecHeight = 0.05;
	float firstSmallRec[4][2] = { -smallRecWidth,radius - smallRecHeight,smallRecWidth,radius - smallRecHeight,smallRecWidth,radius,-smallRecWidth,radius };
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);//12点
	for (int i = 0; i < 4; i++) {
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

	float firstBigRec1[4][2] = { -smallRecWidth,radius - 2 * smallRecHeight,smallRecWidth,
		radius - 2 * smallRecHeight,smallRecWidth,radius,-smallRecWidth,radius };
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

	glLineWidth(1.0);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
		glVertex2f(-radius, 0);
		glVertex2f(radius, 0);
		glVertex2f(0, radius);
		glVertex2f(0, -radius);
	glEnd();
}
void createHourhand(GLfloat angle) {

	float HourWidth = 0.02, HourHeight = 0.2;
	float HourTimer[4][2] = { -HourWidth,0,HourWidth,0,HourWidth,HourHeight,-HourWidth,HourHeight };
	float HourTimer2[4][2];

	for (int i = 0; i < 4; i++) {
		float a = HourTimer[i][0] * cos(DEG_TO_RAD * angle) - HourTimer[i][1] * sin(DEG_TO_RAD * angle);
		float b = HourTimer[i][0] * sin(DEG_TO_RAD * angle) + HourTimer[i][1] * cos(DEG_TO_RAD * angle);
		HourTimer2[i][0] = a;
		HourTimer2[i][1] = b;
	}

	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++) {
		glVertex2fv(HourTimer2[i]);
	}
	glEnd();
}
void createMinutehand(GLfloat angle) {

	float MinWidth = 0.01, MinHeight = 0.3;
	float MinTimer[4][2] = { -MinWidth,0,MinWidth,0,MinWidth,MinHeight,-MinWidth,MinHeight };
	float MinTimer2[4][2];

	for (int i = 0; i < 4; i++) {
		float a = MinTimer[i][0] * cos(DEG_TO_RAD * angle) - MinTimer[i][1] * sin(DEG_TO_RAD * angle);
		float b = MinTimer[i][0] * sin(DEG_TO_RAD * angle) + MinTimer[i][1] * cos(DEG_TO_RAD * angle);
		MinTimer2[i][0] = a;
		MinTimer2[i][1] = b;
	}

	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++) {
		glVertex2fv(MinTimer2[i]);
	}
	glEnd();

}
void createSecondhand(GLfloat angle) {

	float SecWidth = 0.005, SecHeight = 0.45;
	float SecTimer[4][2] = { -SecWidth,0,SecWidth,0,SecWidth,SecHeight,-SecWidth,SecHeight };
	float SecTimer2[4][2];

	for (int i = 0; i < 4; i++) {
		float a = SecTimer[i][0] * cos(DEG_TO_RAD * angle) - SecTimer[i][1] * sin(DEG_TO_RAD * angle);
		float b = SecTimer[i][0] * sin(DEG_TO_RAD * angle) + SecTimer[i][1] * cos(DEG_TO_RAD * angle);
		SecTimer2[i][0] = a;
		SecTimer2[i][1] = b;
	}

	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < 4; i++) {
		glVertex2fv(SecTimer2[i]);
	}
	glEnd();

}
void processWatch(GLuint hour, GLuint minute, GLuint second)
{
	createDial();
	createScale();

	createHourhand(-(hour / 12.0 * 360 + minute / 60.0 * 30));
	createMinutehand(-(minute / 60.0 * 360));
	createSecondhand(-(second / 60.0 * 360));
}

void timer(int id) {
	glutPostRedisplay();
	glutTimerFunc(100, timer, 1);
}

void displayWatch(void)
{
	struct tm* localTime;
	int hour, minute, second;
	time_t curTime;
	//time()获取从1970年1月1日至今的秒数;
	time(&curTime);
	//localtime()将秒数转化为本地时间；
	localTime = localtime(&curTime);
	hour = localTime->tm_hour;
	minute = localTime->tm_min;
	second = localTime->tm_sec;

	processWatch(hour, minute, second);
}

GLint winWidth = 600, winHeight = 600;

void displayFcn(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	displayWatch();

	glFlush();
}

void reshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);

	winWidth = newWidth;
	winHeight = newHeight;
}

void init(void)
{
	glClearColor(0.2, 0.2, 0.2, 0.0);

	points[0][0] = radius;
	points[0][1] = 0;

	points2[0][0] = radiusA;
	points2[0][1] = 0;
	for (int angle = 1; angle < 360; angle++)
	{
		points[angle][0] = points[angle - 1][0] * cos(DEG_TO_RAD) - points[angle - 1][1] * sin(DEG_TO_RAD);
		points[angle][1] = points[angle - 1][0] * sin(DEG_TO_RAD) + points[angle - 1][1] * cos(DEG_TO_RAD);
	}


	for (int angle = 1; angle < 360; angle++)
	{
		points2[angle][0] = points2[angle - 1][0] * cos(DEG_TO_RAD) - points2[angle - 1][1] * sin(DEG_TO_RAD);
		points2[angle][1] = points2[angle - 1][0] * sin(DEG_TO_RAD) + points2[angle - 1][1] * cos(DEG_TO_RAD);
	}
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Timer ");

	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(reshapeFcn);
	glutTimerFunc(10, timer, 1);
	glutMainLoop();
}
