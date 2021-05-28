#include "cone.h"

GLvoid Cone::createCone(GLfloat radius, GLfloat height)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, height);
    for (int angle = 0; angle < 360; angle++) {
        glVertex3f(sin(angle) * radius, cos(angle) * radius, 0);
    }
    glEnd();

    // draw the base of the cone
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, 0);
    for (int angle = 0; angle < 360; angle++) {
        // normal is just pointing down
        glNormal3f(0, -1, 0);
        glVertex3f(sin(angle) * radius, cos(angle) * radius, 0);
    }
    glEnd();
}
