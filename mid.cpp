#include <GL/glut.h>

#include <iostream>
#include <string>
#include <math.h>
using namespace std;

void display();
float xmin = 30;
float ymin = 40;
float xmax = 100;
float ymax = 100;
float xd1, yd1, xd2, yd2;
int N=150;
float pts[10][2];

string to_string(float val){
	string s="";
	char str[20];
	sprintf(str,"%.2f",val);
	int n=strlen(str);
	for(int i=0;i<n-1;i++)s+=str[i];
	return s;
}

void init(void)
{

    glClearColor(0.0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-50, N, N, -50);
}

int code(float x, float y)
{
    int c = 0;
    if (y > ymax)
        c = 8;
    if (y < ymin)
        c = 4;
    if (x > xmax)
        c = c | 2;
    if (x < xmin)
        c = c | 1;
    return c;
}

void mark_point(float x, float y, string s)
{

	float xoffset=.3,  yoffset=-.3;
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(x + xoffset, y + yoffset);
    for (int i = 0; i < s.size(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, s[i]);
    }
}


void mid_point(float x1, float y1, float x2, float y2)
{
	string s="";s+=" ("+ to_string(x1)+" ,"+to_string(y1)+")";
	string ss="";ss+=" ("+ to_string(x2)+" ,"+to_string(y2)+")";
	int c1 = code(x1, y1);
    int c2 = code(x2, y2);
    if ((c1 & c2) > 0)
    {
//        cout << "Completely outisde\n";
        return;
    }
    else if (c1==0&&c2==0)
    {
//        cout << "Completely Inside\n";
		glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINE_LOOP);
	        glVertex2i(x1, y1);
	        glVertex2i(x2, y2);
        glEnd();
		
        return;
    }
    else {
    	float mx=(x1+x2)/2,my=(y1+y2)/2;

    	if(mx==xmin||mx==xmax||my==ymin||my==ymax){
    		int x1code=code(x1,y1);
    		int x2code=code(x2,y2);
    		if(x1code==0)mid_point(x1,y1,mx,my);
    		else mid_point(x2,y2,mx,my);
    		return;
		}
		
    	
    	mid_point(x1,y1,mx,my);
    	mid_point(x2,y2,mx,my);
	}
	
    
	
}

//void draw_line(float xi, float yi, float xf, float yf)
void draw_line(int i, int j)
{
	float xi=pts[i][0],yi=pts[i][1],xf=pts[j][0],yf=pts[j][1];
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(xi, yi);
        glVertex2i(xf, yf);
    glEnd();
    mid_point(xi, yi,xf,yf);
    
    string s="";s+=(i+'A');s+=" ("+ to_string(xi)+" ,"+to_string(yi)+")";
	string ss="";ss+=(j+'A');ss+=" ("+ to_string(xf)+" ,"+to_string(yf)+")";
	
	mark_point(xi,yi,s);
	mark_point(xf,yf,ss);
	
    
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
	    glVertex2i(xmin, ymin);
	    glVertex2i(xmin, ymax);
	    glVertex2i(xmax, ymax);
	    glVertex2i(xmax, ymin);
    glEnd();

    // Region Codes
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
	    glVertex2i(-N, ymin);
	    glVertex2i(N, ymin);
    glEnd();
    glBegin(GL_LINE_LOOP);
	    glVertex2i(-N, ymax);
	    glVertex2i(N, ymax);
    glEnd();
    glBegin(GL_LINE_LOOP);
	    glVertex2i(xmax, -N);
	    glVertex2i(xmax, N);
    glEnd();
    glBegin(GL_LINE_LOOP);
	    glVertex2i(xmin, -N);
	    glVertex2i(xmin, N);
    glEnd();
    mark_point(-N, N, (char *)"1001");
    mark_point(-N, ymax, (char *)"0001");
    mark_point(-N, ymin, (char *)"0101");
    mark_point(xmin, N, (char *)"1000");
    mark_point(xmin, ymax, (char *)"0000");
    mark_point(xmin, ymin,(char *)"0100");
    mark_point(xmax, N,  (char *)"1010");
    mark_point(xmax, ymax, (char *)"0010");
    mark_point(xmax, ymin,(char *)"0110");


   draw_line(0,1);
   cout << "CD: ";
  draw_line(2,3);
	cout << "CF: ";
   draw_line(4,5);
   draw_line(6,7);
   draw_line(8,9);


glFlush();
   
}

int main(int argc, char **argv)
{
	pts[0][0]=40,  pts[0][1]=40;
	pts[1][0]=80,  pts[1][1]=60;
	pts[2][0]=120,  pts[2][1]=30;
	pts[3][0]=120,  pts[3][1]=100;
	pts[4][0]=40,  pts[4][1]=-20;
	pts[5][0]=60,  pts[5][1]=200;
	pts[6][0]=20,  pts[6][1]=60;
	pts[7][0]=80,  pts[7][1]=40;
	pts[8][0]=-20,  pts[8][1]=30;
	pts[9][0]=50,  pts[9][1]=120;

    cout << "------------------------------" << endl;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Clipping");
    glutDisplayFunc(display);
    init();
    glutMainLoop();
    return 0;
}
