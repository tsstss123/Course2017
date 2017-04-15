#include <stdio.h>
#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define SIZE 512

int wide = 600, height = 600;
GLint HITS;
int flag; // move out

int Rect1_x1 = -250, Rect1_y1 = -250, Rect1_x2 = 450, Rect1_y2 = 450;
int Rect2_x1 = -500, Rect2_y1 = -500, Rect2_x2 = 250, Rect2_y2 = 250;


int movex1 = 0, movey1 = 0;
int movex2 = 0, movey2 = 0;
int mousex = 0, mousey = 0;

int RGB1[3] = { 1.0,1.0,0.0 };
int RGB2[3] = { 0.0,1.0,1.0 };

void drawObjects(GLenum mode, int flag)
{
	if (mode == GL_SELECT) glLoadName(1);
	glColor3f(RGB1[0], RGB1[1], RGB1[2]);
	glTranslated(4 * movex1, 4 * movey1, 0);
	glRectf(Rect1_x1, Rect1_y1, Rect1_x2, Rect1_y2);
	glTranslated(-4 * movex1, -4 * movey1, 0);

	if (mode == GL_SELECT) glLoadName(2);
	glColor3f(RGB2[0], RGB2[1], RGB2[2]);
	glTranslated(4 * movex2, 4 * movey2, 0);
	glBegin(GL_TRIANGLES);
	glVertex2i(0, 0);
	glVertex2i(300, 300);
	glVertex2i(-200, 300);
	glEnd();
	glTranslated(-4 * movex2, -4 * movey2, 0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawObjects(GL_RENDER, flag);
	glFlush();
}

void processHits(GLint hits, GLuint buffer[])
{
	GLint names, *ptr;

	printf("hits = %d\n", hits);
	ptr = (GLint *)buffer;
	for (int i = 0; i < hits; i++) {
		names = *ptr;
		ptr += 3;
		for (int j = 0; j < names; j++) {
			if (*ptr == 1)
				printf("rectangle\n");
			else
				printf("triangle\n");
			ptr++;
		}
		printf("\n");
	}
}


GLuint selectBuf[SIZE];

void mouse(int button, int state, int x, int y)   //鼠标函数
{

	GLint hits;
	GLint viewport[4];
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mousex = x;
		mousey = y;
		glGetIntegerv(GL_VIEWPORT, viewport);

		glSelectBuffer(SIZE, selectBuf);
		glRenderMode(GL_SELECT);

		glInitNames();
		glPushName(0);

		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluPickMatrix((GLdouble)x, (GLdouble)(viewport[3] - y), 5.0, 5.0, viewport);
		gluOrtho2D(-2.0 * wide, 2.0 * wide, -2.0*height, 2.0*height);
		drawObjects(GL_SELECT, 0);

		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glFlush();

		hits = glRenderMode(GL_RENDER);
		HITS = hits;
		processHits(hits, selectBuf);

		glutPostRedisplay();
	}
}

void reshape(int w, int h)
{
	wide = w;
	height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-2.0*wide, 2.0*wide, -2.0*height, 2.0*height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	}
}

void motion(int x, int y)    //建立移动函数
{
	if (HITS == 1 && selectBuf[3] == 1)
	{
		movex1 = x - mousex + movex1;
		movey1 = mousey - y + movey1;
		flag = 1;
		display();
	}
	else if (HITS == 1 && selectBuf[3] == 2)
	{
		movex2 = x - mousex + movex2;
		movey2 = mousey - y + movey2;
		flag = 2;
		display();
	}
	else if (HITS == 2)
	{
		movex1 = x - mousex + movex1;
		movey1 = mousey - y + movey1;
		movex2 = x - mousex + movex2;
		movey2 = mousey - y + movey2;
		flag = 3;
		display();
	}
	mousex = x;
	mousey = y;
}

void subMenu1Func(int data)      //设置控制键盘键
{
	switch (data)
	{
	case 1:
		RGB1[0] = 1.0;
		RGB1[1] = 0.0;
		RGB1[2] = 0.0;
		break;
	case 2:
		RGB1[0] = 0.0;
		RGB1[1] = 1.0;
		RGB1[2] = 0.0;
		break;
	case 3:
		RGB1[0] = 0.0;
		RGB1[1] = 0.0;
		RGB1[2] = 1.0;
		break;
	}
	flag = 0;
	display();
}

void subMenu2Func(int data)   //设置控制键盘键
{
	switch (data)
	{
	case 1:
		RGB2[0] = 1.0;
		RGB2[1] = 0.0;
		RGB2[2] = 0.0;
		break;
	case 2:
		RGB2[0] = 0.0;
		RGB2[1] = 1.0;
		RGB2[2] = 0.0;
		break;
	case 3:
		RGB2[0] = 0.0;
		RGB2[1] = 0.0;
		RGB2[2] = 1.0;
		break;
	}
	flag = 0;
	display();
}

void MenuFunc(int data)
{
}

int subMenu1, subMenu2, Menu;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(wide, height);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	
	glClearColor(0.2, 0.2, 0.2, 0.0);

	//创建菜单改变颜色
	subMenu1 = glutCreateMenu(subMenu1Func);
	glutAddMenuEntry("红色", 1);
	glutAddMenuEntry("绿色", 2);
	glutAddMenuEntry("蓝色", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	//创建菜单改变颜色
	subMenu2 = glutCreateMenu(subMenu2Func);
	glutAddMenuEntry("红色", 1);
	glutAddMenuEntry("绿色", 2);
	glutAddMenuEntry("蓝色", 3);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	Menu = glutCreateMenu(MenuFunc);
	//为两个菜单设置名字
	glutAddSubMenu("设置方块的颜色", subMenu1);
	glutAddSubMenu("设置三角形的颜色", subMenu2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMotionFunc(motion);
	glutMainLoop();
	return 0;
}
