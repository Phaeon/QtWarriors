#include "cylindre.h"

void Cylindre::createCylindre(GLdouble topRadius, GLdouble baseRadius, GLdouble height, GLuint texture)
{
    glEnable(GL_TEXTURE_2D);
    {
        glBindTexture(GL_TEXTURE_2D, texture);

        GLUquadricObj* quadObj = gluNewQuadric();
        gluCylinder(quadObj, topRadius, baseRadius, height, 10, 10);
        gluQuadricTexture(quadObj, GL_TRUE);
    }
    glDisable(GL_TEXTURE_2D);
}
