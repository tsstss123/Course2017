#include <OpenGL/gl.h> 
#include <OpenGL/glu.h> 
#include <GLUT/glut.h> 
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>
double rd(){
	return 1.0 * rand() / RAND_MAX;
}
void dfs(float arr[],int l,int r,float det){
	printf("%d , %d\n",l,r);
	if(r - l <= 1)return ;
	int mid = (l + r) / 2;
	if(mid != l && mid != r){
		arr[mid] = (arr[l] + arr[r]) / 2;
		arr[mid] += (rd() - 0.5) * det;
	}
	if(mid > l)dfs(arr,l,mid,det);
	if(mid < r)dfs(arr,mid,r,det);
}
void calcHillPoint(float h[],int lenght,float det){
	int mid = lenght / 2;
	h[mid] = rd() * det;
	h[1] = h[lenght] = 0;
	dfs(h,1,mid,det);
	dfs(h,mid,lenght,det);
}

//-----OpenGL------
#define LEN 20 + 5
float height[LEN];
int len;
void MyDisplay()
{
    float start = -0.7, end = 0.7; //x axis
    float off = (end - start) / (len - 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    for(int i = 1; i <= len; ++i){
   		if(height[i] < 0)height[i] = 0.001;
		glVertex2f(start + off * (i - 1), height[i]);
		printf("%f,%f\n",start + off * (i - 1),height[i]);
	}   
	glEnd(); 
    glFlush();
}
 
int main(int argc,char *argv[])
{
	srand(time(NULL));
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(400,400);
    glutCreateWindow("opengl程序");
    glutDisplayFunc(&MyDisplay);
    //
    len = 20;
    calcHillPoint(height,len,0.4);
    //
    glutMainLoop();
    return 0;
}