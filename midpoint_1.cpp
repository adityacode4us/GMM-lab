//Let r be the rectangular window, whose upper left hand corner is at L(20,-30) and lower right hand corner is at R(90,-100). The coordinates of some the the points are given below-
//A(20,-60) 
//B(90,-20)
//C(0,0)
//D(30,-20)
//E(50,0) 
//F(50,-200) 
//G(40,20)
//H(140,-160) 
//I(-200,10) 
//J(100,-90)
//Write a program to clip the given below line using mid-point subdivision algorithm. The lines are 
//AB, CD, EF, GH, IJ

#include <iostream>
#include <GL/glut.h> // include the GLUT library

using namespace std;

// function prototypes
void clipLine(int x1, int y1, int x2, int y2);

// window coordinates
int x_min = 20, y_min = -100, x_max = 90, y_max = -30;
const int LEFT = 20;
const int BOTTOM = -100;
const int RIGHT = 90;
const int TOP = -30;

// Define the clipping codes
const int INSIDE = 0;
const int LEFT_BIT = 1;
const int RIGHT_BIT = 2;
const int BOTTOM_BIT = 4;
const int TOP_BIT = 8;

// Function to draw a line using OpenGL
void drawLine(int x1, int y1, int x2, int y2) {
  glColor3f(1.0, 0.0, 0.0); // set color to red
  glBegin(GL_LINES);
  glVertex2i(x1, y1);
  glVertex2i(x2, y2);
  glEnd();
}

void display() {
  // draw the rectangular window
  glColor3f(1.0, 1.0, 1.0); // set color to white
  glBegin(GL_LINE_LOOP);
  glVertex2i(x_min, y_min);
  glVertex2i(x_max, y_min);
  glVertex2i(x_max, y_max);
  glVertex2i(x_min, y_max);
  glEnd();

  // clip the lines and draw the clipped lines
  clipLine(20, -60, 90, -20); // AB
  clipLine(0, 0, 30, -20); // CD
  clipLine(50, 0, 50, -200); // EF
  clipLine(40, 20, 140, -160); // GH
  clipLine(-200, 10, 90, -100); // IJ

  glFlush(); // force all drawing to complete
}

// main function
int main(int argc, char **argv) {
  glutInit(&argc, argv); // initialize the GLUT library
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
  glutInitWindowSize(400, 400); // set window size
  glutInitWindowPosition(100, 100); // set window position
  glutCreateWindow("Line Clipping"); // create the window
  glClearColor(0.0, 0.0, 0.0, 0.0); // set background color to black
  gluOrtho2D(-300, 300, -300, 300); // set the coordinate system
  glutDisplayFunc(display); // register display function
  glutMainLoop(); // enter the event loop
  return 0;
}

// function to clip a line using Mid-Point Subdivision Algorithm
// Define the clipping function using midpoint subdivision algorithm
void clipLine(int x1, int y1, int x2, int y2) {
    // Compute the initial clipping codes for the endpoints
    int code1 = INSIDE;
    int code2 = INSIDE;
    if (x1 < LEFT) code1 |= LEFT_BIT;
    else if (x1 > RIGHT) code1 |= RIGHT_BIT;
    if (y1 < BOTTOM) code1 |= BOTTOM_BIT;
    else if (y1 > TOP) code1 |= TOP_BIT;
    if (x2 < LEFT) code2 |= LEFT_BIT;
    else if (x2 > RIGHT) code2 |= RIGHT_BIT;
    if (y2 < BOTTOM) code2 |= BOTTOM_BIT;
    else if (y2 > TOP) code2 |= TOP_BIT;

    // Loop until the line is completely inside the window
    while ((code1 | code2) != INSIDE) {
        // If the line is completely outside the window, discard it
        if (code1 & code2) {
            return;
        }

        // Determine which endpoint is outside the window
        int codeOut = (code1 != INSIDE) ? code1 : code2;
        int x, y;

        // Compute the intersection point using midpoint subdivision algorithm
        if (codeOut & LEFT_BIT) {
            x = LEFT;
            y = y1 + (y2 - y1) * (LEFT - x1) / (x2 - x1);
        } else if (codeOut & RIGHT_BIT) {
            x = RIGHT;
            y = y1 + (y2 - y1) * (RIGHT - x1) / (x2 - x1);
        } else if (codeOut & BOTTOM_BIT) {
            x = x1 + (x2 - x1) * (BOTTOM - y1) / (y2 - y1);
            y = BOTTOM;
        } else if (codeOut & TOP_BIT) {
            x = x1 + (x2 - x1) * (TOP - y1) / (y2 - y1);
            y = TOP;
        }

        // Update the outside endpoint and its clipping code
        if (codeOut == code1) {
            x1 = x;
            y1 = y;
            code1 = INSIDE;
            if (x1 < LEFT) code1 |= LEFT_BIT;
            else if (x1 > RIGHT) code1 |= RIGHT_BIT;
            if (y1 < BOTTOM) code1 |= BOTTOM_BIT;
            else if (y1 > TOP) code1 |= TOP_BIT;
        } else {
            x2 = x;
            y2 = y;
            code2 = INSIDE;
            if (x2 < LEFT) code2 |= LEFT_BIT;
            else if (x2 > RIGHT) code2 |= RIGHT_BIT;
            if (y2 < BOTTOM) code2 |= BOTTOM_BIT;
            else if (y2 > TOP) code2 |= TOP_BIT;
        }
    }

    // Draw the clipped line
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
}

