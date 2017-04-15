#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);   //清除颜色并进行设置
	glOrtho(-40, 40, -40, 40, -40, 40); //设置视口
}

int D_top = 10, D_bottom = 20, H = 20;
float PI = 3.14159;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	float angle = 0.0f;
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 64; angle += PI / 32.0f, i++)
	{
		glColor3f(0.9, 0.9, 0.9);
		glVertex3f(D_bottom * cos(angle), D_bottom * sin(angle), 0);
		glVertex3f(D_bottom * cos(angle + PI / 32.0), D_bottom * sin(angle + PI / 32.0), 0);
		glVertex3f(D_top * cos(angle), D_top * sin(angle), H);
		glColor3f(0.1, 0.1, 0.1);
		glVertex3f(D_top * cos(angle), D_top * sin(angle), H);
		glVertex3f(D_top * cos(angle + PI / 32.0), D_top * sin(angle + PI / 32.0), H);
		glVertex3f(D_bottom * cos(angle + PI / 32.0), D_bottom * sin(angle + PI / 32.0), 0);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, 0, 0);
	for (int i = 0; i < 65; angle += PI / 32.0f, i++) //这里多画一条
	{
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(D_bottom * cos(angle), D_bottom * sin(angle), 0);
		glColor3f(0.1, 0.1, 0.1);
		glVertex3f(D_bottom * cos(angle + PI / 64.0), D_bottom * sin(angle + PI / 64.0), 0);
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN); //绘制图形
	glVertex3f(0, 0, H);
	for (int i = 0; i < 64; angle += PI / 32.0f, i++)
	{
		glColor3f(0.9, 0.9, 0.9);
		glVertex3f(D_top * cos(angle), D_top * sin(angle), H);
		glColor3f(0.1, 0.1, 0.1);
		glVertex3f(D_top * cos(angle + PI / 32.0), D_top * sin(angle + PI / 32.0), H);
	}
	glEnd();
	glFlush();
}
void keyboard(unsigned char key, int x, int y)     //设置移动键盘键
{
	switch (key)
	{
	case 'x':
		printf("x");
		glRotatef(10, 1.0, 0.0, 0.0);
		break;
	case 'y':
		printf("y");
		glRotatef(10, 0.0, 1.0, 0.0);
		break;
	case 'z':
		printf("z");
		glRotatef(10, 0.0, 0.0, 1.0);
		break;
	case 'D':
		D_top += 2;
		break;
	case 'd':
		D_top -= 2;
		break;
	case 'R':
		D_bottom += 2;
		break;
	case 'r':
		D_bottom -= 2;
		break;
	case 'H':
		H += 2;
		break;
	case 'h':
		H -= 2;
		break;
	}
	display();

}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100); // 设置窗口位置
	glutInitWindowSize(500, 500);    //设置窗口大小
	glutCreateWindow(argv[0]);
	init();

	glEnable(GL_DEPTH_TEST); //开启深度测试，防止表面覆盖
	glDepthFunc(GL_LEQUAL); //设置深度测试的计算方法,离屏幕远的像素会离屏幕近的像素遮挡

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);   //调用键盘函数
	glutMainLoop();
	return 0;
}
