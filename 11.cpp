// Let r be a rectangular window whose lower-left hand corner is at L(-30,10) and upper right hand corner is at R(20,60).
// the cordinates of some of the points are given below A(-40,20) B(-10,70) C(-10,50) D(30,80) E(-20,30) F(10,20) G(10,-20) H(30,30) I(-40,70) J(-20,100)
// Write a program to clip the given below lines using cohen's sutherland algorithm
//1 AB
//2 CD
//3 BH
//4 EF
//5 IJ
//6 BF
//7 EH
//8 EG
//9 DJ
//10 FH 


#include <windows.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include<iostream>

void display();
using namespace std;
float xmin=-100;
float ymin=-100;
float xmax=100;
float ymax=100;
float xd1,yd1,xd2,yd2;


void init(void)
{

//    glClearColor(0.0,0,0,0);
//    glMatrixMode(GL_PROJECTION);
//    gluOrtho2D(-300,300,-300,300);
	glClear (GL_COLOR_BUFFER_BIT);
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glColor3f (0.0f, 0.0f, 0.0f);
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

int code(float x,float y)
{
    int c=0;
    if(y>ymax)c=8;
    if(y<ymin)c=4;
    if(x>xmax)c=c|2;
    if(x<xmin)c=c|1;
    return c;
}

void cohen_Line(float x1,float y1,float x2,float y2)
{
    int c1=code(x1,y1);
    int c2=code(x2,y2);
    float m=(y2-y1)/(x2-x1);
    while((c1|c2)>0)
    {
        if((c1 & c2)>0)
        {
           exit(0);
        }

    float xi=x1;float yi=y1;
    int c=c1;
    if(c==0)
    {
         c=c2;
         xi=x2;
         yi=y2;
    }
    float x,y;
    if((c & 8)>0)
    {
       y=ymax;
       x=xi+ 1.0/m*(ymax-yi);
    }
    else
      if((c & 4)>0)
      {
          y=ymin;
          x=xi+1.0/m*(ymin-yi);
      }
      else
       if((c & 2)>0)
       {
           x=xmax;
           y=yi+m*(xmax-xi);
       }
       else
       if((c & 1)>0)
       {
           x=xmin;
           y=yi+m*(xmin-xi);
       }

       if(c==c1)
       {
           xd1=x;
           yd1=y;
           c1=code(xd1,yd1);
       }

       if(c==c2)
       {
           xd2=x;
           yd2=y;
           c2=code(xd2,yd2);
       }
}

}

void display1()
{

   glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);
   glBegin(GL_LINES);
   glVertex2i(xmin-100,ymin);
   glVertex2i(xmin-100,ymax);
   glVertex2i(xmax+100,ymin);
   glVertex2i(xmax+100,ymax);
   glVertex2i(xmin,ymax+100);
   glVertex2i(xmin,ymin-100);
   glVertex2i(xmax,ymax+100);
   glVertex2i(xmax,ymin-100);
   glEnd();
   glColor3f(1.0,0.0,0.0);
   cohen_Line(xd1,yd1,xd2,yd2);
   glBegin(GL_LINES);
   glVertex2i(xd1,yd1);
   glVertex2i(xd2,yd2);
   glEnd();
   
   

	//set the position of the text in the window using the x, y and z coordinates
	glRasterPos3f(0,0,0);
	char string[] ="0000";
	//get the length of the string to display
	int len = (int) strlen(string);

	//loop to display character by character
	for (int i = 0; i < len; i++)
	{
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
	}
	glFlush();
}







int main(int argc,char** argv)
{
    printf("Enter line co-ordinates:");
    
    cin>>xd1>>yd1>>xd2>>yd2;
    float ax1=-40;
    
    float ay1=-10;
    
    float bx1=-10;
    
    float by1=70;
    
    float cx1=-10;
    
    float cy1=50;
    
    float dx1=30;
    
    float dy1=80;
    
    float ex1=-20;
    
    float ey1=30;
    
    float fx1=10;
    
    float fy1=20;
    
    float gx1=10;
    
    float gy1=-20;
    
    float hx1=30;
    
    float hy1=30;
    
    float ix1=-40;
    
    int iy1=70;
    
    int jx1=-20;
    
    int jy1=100;
    
//    glutInit(&argc,argv);
//    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
//    glutInitWindowSize(600,600);
//    glutInitWindowPosition(0,0);
//    glutCreateWindow("Clipping");
//    glutDisplayFunc(display);
//    init();
//    glutMainLoop();
 	glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition (0, 0);
    glutInitWindowSize (900, 900);
    glutCreateWindow ("2D TRANSFORMATION OVER THE TRIANGLE");
    glutDisplayFunc (display1);
    init ();
    glutMainLoop ();
    return 0;
}



