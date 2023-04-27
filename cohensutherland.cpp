#include <bits/stdc++.h>
#include <GL/glut.h>


GLfloat xMn=-30 , xMx=20, yMn = 10 , yMx= 60;
int left = 1 , right =2 , bot = 4 , top = 8;


void mark(int x, int y ,int xoffset,int yoffset, char str[])
{
  	int w= glutBitmapLength(GLUT_BITMAP_HELVETICA_12, (unsigned char*)str);
   	glRasterPos2f(x+xoffset,y+yoffset);
   	int len = strlen(str);
   	for (int i = 0; i < len; i++) {
   	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i]);
}
}
void lines(int x1, int y1 ,int x2, int y2)
{
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_LINES);
	glVertex2f(x1,y1);
	glVertex2f(x2,y2);
	glEnd();
	glFlush();
}

int get_code(GLfloat x , GLfloat y )
{
	int code = 0;
	if(x< xMn)
	code |= left;
	if(x>xMx)
	code |= right;
	if(y>yMx)
	code|= top;
	if(y< yMn)
	code |= bot;
	return code;
}
void drawRegion()
{

	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_LINES);
	glVertex3f(xMn,-600.0,1.0f);
	glVertex3f(xMn ,600.0, 1.0f);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(xMx,-600.0,1.0f);
	glVertex3f(xMx ,600.0, 1.0f);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(-600.0,yMn,1.0f);
	glVertex3f(600.0,yMn, 1.0f);
	glEnd();
	glBegin(GL_LINES);

	glVertex3f(-600.0,yMx,1.0f);
	glVertex3f(600.0,yMx, 1.0f);
	glEnd();
	glFlush();
}
void clip(GLfloat x1, GLfloat y1, GLfloat x2 , GLfloat y2)
{
	int c1 = get_code(x1,y1);
	int c2 = get_code(x2,y2);
	int c ;
	GLfloat x, y;
	bool flag = false;
	while(true)
	{
	if((c1|c2)==0)
	{
		//line inside window already so accepted
		flag = true;
		break;
	}
	else if((c1&c2)!=0)
	{
		//line rejected
		break;
	}
	else
	{
	if(c1)
	c = c1;
	else
	c = c2;
	if(c & left)
	{
		x = xMn;
		y = y1 + (y2-y1)*(xMn-x1)/(x2-x1);
	}
	if(c & right)
	{
		x = xMx;
		y = y1 + (y2-y1)* (xMx-x1)/(x2-x1);
	}
	if(c & bot)
	{
		y =yMn;
		x = x1 +(x2-x1)*(yMn-y1)/(y2-y1);
	}
	if(c& top)
	{
		y = yMx;
		x = x1 + (x2-x1)*(yMx-y1)/(y2-y1);
	}
	if(c==c1)
	{
		x1 = x;
		y1 = y;
		c1 = get_code(x1,y1);
	}
	else
	{
		x2= x;
		y2= y;
		c2 = get_code(x2,y2);
	}
	}
	}
	if(flag)
	{
		glBegin(GL_LINES);
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
		glEnd();
		glFlush();
		
	}	
}


void mydisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	mark(0,40,0,0,(char*)"0000");
	mark(-60,40,0,0,(char*)"0001");
	mark(60,40,0,0,(char*)"0010");
	mark(60,100,0,0,(char*)"1010");
	mark(-60,100,0,0,(char*)"1001");
	mark(0,100,0,0,(char*)"10-0");
	mark(60,-20,0,0,(char*)"0110");
	mark(-60,-20,0,0,(char*)"011");
	mark(0,-20,0,0,(char*)"0100");
	
    drawRegion();
    //AB
    lines(-40,20,-10,70);
    glColor3f(1.0f,0.0f,1.0f);
    clip(-40,20,-10,70);//AB
    //CD
    lines(-10,50,30,80);
    glColor3f(1.0f,0.0f,0.0f);
    clip(-10,50,30,80);//CD
    //BH
    lines(-10,70,30,30);
    glColor3f(1.0f,1.0f,0.0f);
    clip(-10,70,30,30);//BH
    //EF
    lines(-20,30,10,20);
    glColor3f(1.0f,0.0f,1.0f);
    clip(-20,30,10,20);
    //IJ
    lines(-40,70,-20,100);
    glColor3f(0.0f,0.0f,1.0f);
    clip(-40,70,-20,100);//IJ
    //DF
    lines(30,80,10,20);
    glColor3f(0.0f,1.0f,1.0f);
    clip(30,80,10,20);//DF
    //EH
    lines(-20,30,30,30);
    glColor3f(0.0f,1.0f,0.0f);
    clip(-20,30,30,30);//EH
    //DJ
    lines(30,80,-20,100);
    glColor3f(1.0f,0.0f,1.0f);
    clip(30,80,-20,100);//DJ
    //EG
    lines(-20,30,10,-20);
    glColor3f(1.0f,0.0f,1.0f);
    clip(-20,30,10,-20);//EG
    //FH
    lines(10,20,30,30);
    glColor3f(1.0f,0.0f,1.0f);
    clip(10,20,30,30);
}

void myInit () {
	glClear (GL_COLOR_BUFFER_BIT);
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glColor3f (0.0f, 0.5f, 0.5f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (-100, 100, -200, 200);
    glFlush ();
}

int main( int argC , char ** argV)
{
	glutInit(&argC, argV);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(600,600);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutCreateWindow("Cohen-Sundelander-Algorithm");
	glutDisplayFunc(mydisplay);
	myInit ();
	glutMainLoop();
	
	return 0;
}
