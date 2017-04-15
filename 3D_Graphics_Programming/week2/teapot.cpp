#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

GLint winWidth = 600, winHeight = 600;   //  Initial display-window size.

GLfloat pi = acos(-1.0);
GLfloat R = 0.8, theta = pi / 2, phi = 0;
GLfloat x, y, z;  //  Viewing-coordinate origin.
GLfloat xref = 0.0, yref = 0.0, zref = 0.0;  //  Look-at point.
GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0;          //  View-up vector.

											   /*  Set coordinate limits for the clipping window:  */
GLfloat xwMin = -40.0, ywMin = -60.0, xwMax = 40.0, ywMax = 60.0;

/*  Set positions for near and far clipping planes:  */
GLfloat dnear = 0.0, dfar = 125.0;

void calcXYZ(void)
{
	x = R * sin(theta) * sin(phi);
	y = R * cos(theta);
	z = R * sin(theta) * cos(phi);
	printf("x0 = %f, y0 = %f, z0 = %f\n", x, y, z);
}

void resetView()
{
	calcXYZ();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z, xref, yref, zref, Vx, Vy, Vz);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(xwMin, xwMax, ywMin, ywMax, dnear, dfar);
	gluPerspective(45, 1, 0, 100);

}

void displayFcn(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_DEPTH_TEST);

	/*  Set parameters for a square fill area.  */
	//glColor3f(0.0, 1.0, 0.0);         //  Set fill color to green.

	resetView();

	glMatrixMode(GL_MODELVIEW);
	glTranslatef(xref, yref, zref);
	glutWireTeapot(0.2);

	glFlush();
}

void reshapeFcn(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);

	winWidth = newWidth;
	winHeight = newHeight;
}



void keyA()
{
	phi += 0.05;
	glutPostRedisplay();
}

void keyD()
{
	phi -= 0.05;
	glutPostRedisplay();
}

void keyW()
{
	R += 0.1;
	glutPostRedisplay();
}

void keyS()
{
	if (R > 0.1)
		R -= 0.1;
	glutPostRedisplay();
}

void keyQ()
{
	theta += 0.05;
	glutPostRedisplay();
}

void keyE()
{
	theta -= 0.05;
	glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
	if (key == 'a')
		keyA();
	if (key == 'd')
		keyD();
	if (key == 'w')
		keyW();
	if (key == 's')
		keyS();
	if (key == 'q')
		keyQ();
	if (key == 'e')
		keyE();
}

void init(void)
{
	glClearColor(0.2, 0.2, 0.2, 0.0);

	glShadeModel(GL_SMOOTH);

}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Perspective View of A Teapot");

	init();
	glutDisplayFunc(displayFcn);
	glutReshapeFunc(reshapeFcn);
	glutKeyboardFunc(processNormalKeys);
	glutMainLoop();
}
