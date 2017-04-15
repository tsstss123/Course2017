#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
#endif

#include <math.h>
#include <stdio.h>

#define PI 3.14
#define CONELINE 1
#define CIRCLELINE 2

int lineType = 1;
float a, b, c; //锥形螺旋曲线参数

void draw3DCircleLines()
{
	float t;
	float x, y, z;
	float a = 2, b = 3, c = 18;
	glColor3f(1.0, 0.5, 0.5);
	glBegin(GL_LINE_STRIP);
	for (t = 0.0; t <= 2 * PI; t += 0.0002)
	{
		x = (a * sin(c * t) + b) * cos(t);
		y = (a * sin(c * t) + b) * sin(t);
		z = a * cos(c * t);
		glVertex3f(x, y, z);
	}
	glEnd();
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);  //建立坐标轴
		glVertex3f(0, 0, 0);
		glVertex3f(12, 0, 0);
	glEnd();
	glBegin(GL_LINES);  //建立坐标轴
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 12);
	glEnd();
	glBegin(GL_LINES);  //建立坐标轴
		glVertex3f(0, 0, 0);
		glVertex3f(0, 12, 0);
	glEnd();
}
void draw3DConeLines()
{
	float t;
	float x, y, z;

	glColor3f(1.0, 0.5, 0.5); //颜色
	glBegin(GL_LINE_STRIP);

	for (t = 0.0; t <= 2 * PI; t += 0.0001)
	{
		x = a * t * cos(c * t) + b;
		y = a * t * sin(c * t) + b;
		z = c * t;
		glVertex3f(x, y, z);
	}
	glEnd();

	glColor3f(1.0, 1.0, 1.0);

	glBegin(GL_LINES);  //建立坐标轴
		glVertex3f(0, 0, 0);
		glVertex3f(12, 0, 0);
	glEnd();

	glBegin(GL_LINES);  //建立坐标轴
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 12);
	glEnd();

	glBegin(GL_LINES);  //建立坐标轴
		glVertex3f(0, 0, 0);
		glVertex3f(0, 12, 0);
	glEnd();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	if (lineType == CONELINE)
		draw3DConeLines();
	else if (lineType == CIRCLELINE)
		draw3DCircleLines();

	glFlush();
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glColor3f(1.0, 1.0, 1.0);

	gluLookAt(1, 1, 1,   //更改视角
		3, 3, 3,
		-1, -1, 1
	);

	glMatrixMode(GL_PROJECTION);  //设置投影模式
	glLoadIdentity();            //设置单位矩形
	glOrtho(-12.0, 12.0, -12.0, 12.0, -12, 12);

}


int main(int argc, char* argv[])
{
	printf("Please input Line type \n1)Cone Line \n2)Circle Line\n");
	scanf("%d", &lineType);
	printf("Please input a,b,c:\n");
	scanf("%f%f%f", &a, &b, &c);
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Simple");

	glutDisplayFunc(display);

	init();

	glutMainLoop();


	return 0;
}