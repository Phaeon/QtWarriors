#include "octahedron.h"

GLvoid Octahedron::createOctahedron(GLuint texture)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_TRIANGLES);
    {
        //triangle superieur avant gauche
        n nor = normale(0.0, 0.0, 0.0, 0.0, -1.0, 1.0, 1.0, -1.0, 0.0);
        glNormal3f(nor.x, nor.y, nor.z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0,  0.0,  0.0);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0, -1.0,  1.0);
        glTexCoord2f(0.5f, 1.0f); glVertex3f( 1.0, -1.0,  0.0);

        //triangle superieur avant droit
        nor = normale(0.0, 0.0, 0.0, -1.0, -1.0,  0.0, 0.0, -1.0, 1.0);
        glNormal3f(nor.x, nor.y, nor.z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0,  0.0,  0.0);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0, -1.0,  0.0);
        glTexCoord2f(0.5f, 1.0f); glVertex3f( 0.0, -1.0,  1.0);

        //triangle superieur arriere droit
        nor = normale(0.0, 0.0, 0.0, -1.0, -1.0,  0.0, 0.0, -1.0, -1.0);
        glNormal3f(nor.x, nor.y, nor.z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0,  0.0,  0.0);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0, -1.0,  0.0);
        glTexCoord2f(0.5f, 1.0f); glVertex3f( 0.0, -1.0, -1.0);

        //triangle superieur arriere gauche
        nor = normale(0.0, 0.0, 0.0, 0.0, -1.0, -1.0, 1.0, -1.0,  0.0);
        glNormal3f(nor.x, nor.y, nor.z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0,  0.0,  0.0);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0, -1.0, -1.0);
        glTexCoord2f(0.5f, 1.0f); glVertex3f( 1.0, -1.0,  0.0);

        //triangle inferieur avant gauche
        nor = normale(0.0, -2.0,  0.0, 0.0, -1.0,  1.0, 1.0, -1.0,  0.0);
        glNormal3f(nor.x, nor.y, nor.z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0, -2.0,  0.0);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0, -1.0,  1.0);
        glTexCoord2f(0.5f, 1.0f); glVertex3f( 1.0, -1.0,  0.0);

        //triangle inferieur avant droit
        nor = normale(0.0, -2.0,  0.0, -1.0, -1.0,  0.0, 0.0, -1.0,  1.0);
        glNormal3f(nor.x, nor.y, nor.z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0, -2.0,  0.0);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0, -1.0,  0.0);
        glTexCoord2f(0.5f, 1.0f); glVertex3f( 0.0, -1.0,  1.0);

        //triangle inferieur arriere droit
        nor = normale(0.0, -2.0,  0.0, -1.0, -1.0,  0.0, 0.0, -1.0,  -1.0);
        glNormal3f(nor.x, nor.y, nor.z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0, -2.0,  0.0);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0, -1.0,  0.0);
        glTexCoord2f(0.5f, 1.0f); glVertex3f( 0.0, -1.0, -1.0);

        //triangle inferieur arriere gauche
        nor = normale(0.0, -2.0,  0.0, 0.0, -1.0, -1.0, 1.0, -1.0,  0.0);
        glNormal3f(nor.x, nor.y, nor.z);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( 0.0, -2.0,  0.0);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.0, -1.0, -1.0);
        glTexCoord2f(0.5f, 1.0f); glVertex3f( 1.0, -1.0,  0.0);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);

}
