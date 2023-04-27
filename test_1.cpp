#include <GL/glut.h>

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.8f);
    glVertex2f(-0.7f, 0.3f);
    glVertex2f(-0.5f, -0.6f);
    glVertex2f(0.5f, -0.6f);
    glVertex2f(0.7f, 0.3f);
    glEnd();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("My Application");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

