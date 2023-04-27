#include <bits/stdc++.h>
#include <GL/glut.h> 

#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

using namespace std;


float x_min = -30, y_min = 10, x_max = 20, y_max = 60; 
void drawWindow () {
	cout << "Cordinate of rectangle are x_min = -30, x_max = 20, Y_min = 10, y_max = 60\n";
	glBegin (GL_LINES); 
		glVertex2f(x_min, -600.0f);
		glVertex2f(x_min, 600.0f);
	glEnd();
	glBegin (GL_LINES);
		glVertex2f(x_max, -600.0f);
		glVertex2f(x_max, 600.0f);
	glEnd();
	glBegin (GL_LINES);
		glVertex2f(-600.0f, y_min);
		glVertex2f(600.0f, y_min);
	glEnd();
	glBegin (GL_LINES);
		glVertex2f(-600.0f, y_max);
		glVertex2f(600.0f, y_max);
	glEnd();
    glFlush ();
}
void mark_point(int x,int y,int xoffset, int yoffset, char str[]){
   	int w= glutBitmapLength(GLUT_BITMAP_HELVETICA_12, (unsigned char*)str);
   	glRasterPos2f(x+xoffset,y+yoffset);
   	int len = strlen(str);
   	for (int i = 0; i < len; i++) {
   	glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i]);
	}
}
void drawOriginal(float x0, float y0, float x1, float y1){
	glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    glVertex2f(x0, y0);
    glVertex2f(x1, y1);
    glEnd();
    glFlush();
}
int get_code(float x, float y) {
    int code = INSIDE;
    if (x < x_min) code |= LEFT;
    else if (x > x_max) code |= RIGHT;
    if (y < y_min) code |= BOTTOM;
    else if (y > y_max) code |= TOP;
    return code;
}

void cohen_sutherland_clip(float x0, float y0, float x1, float y1, string name) {
	cout << "For line " << name << '\n';
    int code0 = get_code(x0, y0);
    int code1 = get_code(x1, y1);
    //cout << "Code of (" << x0 << ", " << y0 <<") is " << code0 << '\n';
   // cout << "Code of (" << x1 << ", " << y1 <<") is " << code1 << '\n';
    bool accept = false;
	if (code0 & code1) {
    	//cout << "Line (" << x0 << ", " << y0 << "), (" << x1 << ", " << y1 << ") is rejected\n";
    	return;
    }
    while (true) {
        if ((code0 == 0) && (code1 == 0)) {
            accept = true;
            break;
        }  
		else { 
            int code = (code0 != 0) ? code0 : code1;
            float x, y;
            if (code & LEFT) {
                x = x_min;
                y = y0 + (y1 - y0) * (x - x0) / (x1 - x0);
                // if(x < x_min || x > x_max || y < y_min || y > y_max)continue;
                 //cout << "Intersecting point: " << x << ", " << y << '\n';
            } 
			else if (code & RIGHT) {
                x = x_max;
                y = y0 + (y1 - y0) * (x - x0) / (x1 - x0);
                //if(x < x_min || x > x_max || y < y_min || y > y_max)continue;
                //cout << "Intersecting point: " << x << ", " << y << '\n';
            } 
			else if (code & BOTTOM) {
                y = y_min;
                x = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
                // if(x < x_min || x > x_max || y < y_min || y > y_max)continue;
                //cout << "Intersecting point: " << x << ", " << y << '\n';
            } 
			else { 
                y = y_max;
                x = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
                // if(x < x_min || x > x_max || y < y_min || y > y_max)continue;
                //  cout << "Intersecting point: " << x << ", " << y << '\n';
            }
            if (code == code0) {
                x0 = x;
                y0 = y;
                code0 = get_code(x0, y0);
            } 
			else {
                x1 = x;
                y1 = y;
                code1 = get_code(x1, y1);
            }
        }
    }
    if (accept) {
        glBegin(GL_LINES);
        glVertex2f(x0, y0);
        glVertex2f(x1, y1);
        glEnd();
        glFlush();
    }
}
