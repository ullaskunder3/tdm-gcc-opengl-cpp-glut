#include <GL/freeglut.h>

// Square position and size
GLfloat xPos = 0.0f;
GLfloat yPos = 0.0f;
GLfloat rsize = 25.0f;

// Step sizes
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

// Window dimensions
GLfloat windowWidth;
GLfloat windowHeight;

void RenderScene(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 0.0f, 0.0f);  // Red square
    glRectf(xPos, yPos, xPos + rsize, yPos - rsize);
    glutSwapBuffers();
}

void TimerFunction(int value) {
    if (xPos > windowWidth - rsize || xPos < -windowWidth)
        xstep = -xstep;
    if (yPos > windowHeight || yPos < -windowHeight + rsize)
        ystep = -ystep;

    xPos += xstep;
    yPos += ystep;

    if (xPos > (windowWidth - rsize + xstep))
        xPos = windowWidth - rsize - 1;
    else if (xPos < (-windowWidth + xstep))
        xPos = -windowWidth + 1;

    if (yPos > (windowHeight + ystep))
        yPos = windowHeight - 1;
    else if (yPos < (-windowHeight + rsize + ystep))
        yPos = -windowHeight + rsize - 1;

    glutPostRedisplay();
    glutTimerFunc(33, TimerFunction, 1);
}

void ChangeSize(GLsizei w, GLsizei h) {
    GLfloat aspectRatio;
    if (h == 0) h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    aspectRatio = (GLfloat)w / (GLfloat)h;

    if (w <= h) {
        windowWidth = 100;
        windowHeight = 100 / aspectRatio;
        glOrtho(-100.0, 100.0, -windowHeight, windowHeight, 1.0, -1.0);
    } else {
        windowWidth = 100 * aspectRatio;
        windowHeight = 100;
        glOrtho(-windowWidth, windowWidth, -100.0, 100.0, 1.0, -1.0);
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void SetupRC(void) {
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);  // Blue background
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 400);
    glutCreateWindow("Bouncing Square");

    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(33, TimerFunction, 1);

    SetupRC();
    glutMainLoop();

    return 0;
}
