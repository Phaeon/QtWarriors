#include "sphere.h"

GLvoid Sphere::createSphere(int slices, int stacks, GLuint texture)
{
    glEnable(GL_TEXTURE_2D);
    {
        glBindTexture(GL_TEXTURE_2D, texture);

        GLUquadricObj * quadObj = gluNewQuadric();
        gluSphere(quadObj, 1.0, slices, stacks);
        gluQuadricTexture(quadObj, GL_TRUE);

    }
    glDisable(GL_TEXTURE_2D);
}
