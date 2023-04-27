#include <GL/glut.h>
using namespace std;
void Start_Line( );
void Set_Graphics( int, int );
//void Line_Algo( int, int, int, int );

int main( int argc, char** argv  )
{
   
    glutInit( &argc, argv );
    glutInitWindowSize( 640,480);
    glutInitWindowPosition( 100, 150 );
    glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutCreateWindow( " Elipse Drawing" );
    glutDisplayFunc( Start_Line );
    Set_Graphics( 100, 100 /*window_width, window_height*/ );
    glutMainLoop( );
    return 0;
}

void drawDot (GLint x, GLint y, GLfloat r, GLfloat g, GLfloat b)
{ glColor3f(r,g,b);
  glBegin (GL_POINTS);
      glVertex2i (x,y);
  glEnd();
}

void symmetricPixels (int x, int y, int xc, int yc, float r, float g, float b)
{ drawDot (xc + x, yc + y, r,g,b);
  drawDot (xc - x, yc + y,r,g,b);
  drawDot (xc + x, yc - y,r,g,b);
  drawDot (xc - x, yc - y,r,g,b);
}

void Ellipse (int a, int b, int xc, int yc, float r, float g, float bl)
{ int aSq,bSq,twoASq,twoBSq,d,dx,dy,x,y;

  aSq = a*a;
  bSq = b*b;
  twoASq = 2*aSq;
  twoBSq = 2*bSq;
  d = bSq - b*aSq + aSq/4;
  dx = 0;
  dy = twoASq*b;
  x = 0;
  y = b;
  symmetricPixels(x,y,xc,yc,r,g,bl);
  while (dx < dy)
  { x++;
    dx += twoBSq;
    if (d >= 0)
    { y--;
      dy -= twoASq;
    }
    if (d < 0)
     d += bSq + dx;
    else
     d += bSq + dx - dy;
    symmetricPixels (x,y,xc,yc,r,g,bl);
  }
  d = (int)(bSq*(x+0.5)*(x+0.5) + aSq*(y-1)*(y-1) -
                 aSq*bSq);
  while (y > 0)
  { y--;
    dy -= twoASq;
    if (d <= 0)
    { x++;
      dx += twoBSq;
    }
    if (d > 0)
         d += aSq - dy;
    else
         d += aSq -dy +dx;
    symmetricPixels(x,y,xc,yc,r,g,bl);
  }
}   
void Set_Graphics( int width, int height )
{
    glClearColor( 1.0, 1.0, 1.0, 0.0 );
    glColor3f( 0.0f, 0.0f, 0.0f );
    glViewport( 0, 0, width, height );
    glMatrixMode( GL_PROJECTION );   
    glLoadIdentity( );
    glEnable( GL_DEPTH_TEST );
    gluPerspective( 45, ( float ) width / height, 1.0, 0 );
    glMatrixMode( GL_MODELVIEW );
    glTranslatef( 0, 0, 5 * ( -height) );
}
void Start_Line( )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//    Line_Algo( 5, 8, 29,32 );
//    Circle (40,0,0,1);
    Ellipse (100,30,20,20,0,1,0);
  // glFlush();
    glutSwapBuffers( );
}
