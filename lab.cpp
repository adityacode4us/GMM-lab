
#include <stdio.h>
#include <GL/glut.h>
using namespace std;

GLfloat pivot_X = 100, pivot_Y = 200;
GLfloat X = 150, Y = 250;

GLfloat V1X = 0.0f+pivot_X, V1Y = 100.0f+pivot_Y, V1Z = 0.0f;
GLfloat V2X = 100.0f+pivot_X, V2Y = 100.0f+pivot_Y, V2Z = 0.0f;
GLfloat V3X = 100.0f+pivot_X, V3Y = 0.0f+pivot_Y, V3Z = 0.0f;
GLfloat V4X = 0.0f+pivot_X, V4Y = 0.0f+pivot_Y, V4Z = 0.0f;
GLfloat V5X = 50.0f+pivot_X, V5Y = 125.0f+pivot_Y, V5Z = 0.0f;


void myInit () {
	glClear (GL_COLOR_BUFFER_BIT);
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glColor3f (0.0f, 0.5f, 0.5f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (-500, 500, -500, 500);
    
    glBegin (GL_LINE_LOOP);
    	glVertex3f (-400.0, 0.0, 0.0);
    	glVertex3f (400.0, 0.0, 0.0);
    glEnd ();
    
    glBegin (GL_LINE_LOOP);
    	glVertex3f (0.0, -400.0, 0.0);
    	glVertex3f (0.0, 400.0, 0.0);
    glEnd ();
    
    glFlush ();
}







void drawPentagon () {
    glBegin (GL_LINE_LOOP);
//    	glVertex3f (V1X, V1Y, V1Z);
//    	glVertex3f (V5X, V5Y, V5Z);
//    	glVertex3f (V2X, V2Y, V2Z);
//    	glVertex3f (V3X, V3Y, V3Z);
    	glVertex3f (150, 140, 0);
    	glVertex3f (150, 60, 0);
    	glVertex3f (50, 60, 0);
    	glVertex3f (50, 140, 0);
//    	glVertex3f (V4X, V4Y, V4Z);
    glEnd ();
    glBegin(GL_POLYGON);
    	glVertex3f (100,140,0);
    	glVertex3f (50,100,0);
		glVertex3f (100,60,0);
		glVertex3f (150,100,0);
	glEnd();
	glColor3f (0.0f, 0.5f, 0.5f);
	 glBegin(GL_POLYGON);
    	glVertex3f (75,120,0);
    	glVertex3f (125,120,0);
		glVertex3f (125,80,0);
		glVertex3f (75,80,0);
	glEnd();
    glFlush ();
}




void drawPivot(){
	glBegin (GL_POINTS);
		glColor3f(0.0f,0.0f,1.0f);
		glVertex2d(X, Y);
	glEnd ();
	glFlush();
}

void transformTranslate (float xaxis, float yaxis, float zaxis) {
	glColor3f (0.0f, 1.0f, 0.0f);
	glTranslatef (xaxis, yaxis, zaxis);
	drawPentagon ();
}

void transformRotate (float deg, float xaxis, float yaxis, float zaxis) {
	glColor3f (0.0f, 1.0f, 0.0f);
	glRotatef (deg, xaxis, yaxis, zaxis);
	glColor3f (0.0f, 0.0f, 1.0f);
	drawPentagon ();
}

void transformScale (float xaxis, float yaxis, float zaxis) {
	glColor3f (0.0f, 1.0f, 0.0f);
	glScalef (xaxis, yaxis, zaxis);
	drawPentagon ();
}

void transformReflect (float xaxis, float yaxis, float zaxis) {
	glColor3f (0.0f, 0.5f, 0.2f);
	GLfloat M[16]={
	1.0f,0.0f,0.0f,0.0f,
	0.0f,-1.0f,0.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,0.0f,1.0f,
};
    glMultMatrixf(M);
glColor3f (0.0f, 0.5f, 0.2f);
	drawPentagon ();
} 

void transformShearing(){
	glColor3f (0.0f, 0.5f, 0.2f);
	GLfloat M[16]={
	1.0f,2.0f,0.0f,0.0f,
	2.5f,1.0f,0.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,0.0f,1.0f,
};
    glMultMatrixf(M);
glColor3f (0.0f, 0.5f, 0.2f);
	drawPentagon ();
}
void myDisplay () {
	glColor3f (1.0, 1.0, 1.0);
	drawPentagon();
	drawPivot();
    printf ("Final output: \n");
    int n;
    scanf("%d",&n);
    switch(n){
    	case 1:
    		transformRotate(180.0,0.0,0.0,1.0);
    		break;
    	case 2:
    		transformTranslate(100, 100, 0.0);
    		break;
    	case 3:
    		transformScale(0.5,0.5,0.0);
    		break;
    	case 4:
    		transformReflect(1.0,0.0,0.0);
    		break;
    	case 5:
    		transformShearing();
    		break;
	}
//	transformTranslate (100, 100, 0.0);
//	transformRotate (90.0, 0.0, 0.0, 1.0);
//	transformScale (0.5, 0.5, 0.0);
//	transformTranslate (0.0, 0.0, 0.0);
//	transformTranslate (500, -300.0, 0.0);
}
  
int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (0, 0);
    glutInitWindowSize (900, 900);
    glutCreateWindow ("2D TRANSFORMATION OVER THE Image");
    glutDisplayFunc (myDisplay);
    myInit ();
    glutMainLoop ();
    
    return 0;
}
