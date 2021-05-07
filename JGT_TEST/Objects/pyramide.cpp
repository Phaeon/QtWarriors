#include "pyramide.h"

GLvoid Pyramide::createPyramide()
{
    glBegin(GL_TRIANGLES);
    {
    //triangle avant gauche
            glVertex3f( 0.0,  0.0,  0.0);
            glVertex3f( 0.0, -1.0,  1.0);
            glVertex3f( 1.0, -1.0,  0.0);

    //triangle avant droit
            glVertex3f( 0.0,  0.0,  0.0);
            glVertex3f(-1.0, -1.0,  0.0);
            glVertex3f( 0.0, -1.0,  1.0);

    //triangle arriere droit
            glVertex3f( 0.0,  0.0,  0.0);
            glVertex3f(-1.0, -1.0,  0.0);
            glVertex3f( 0.0, -1.0, -1.0);

    //triangle arriere gauche
            glVertex3f( 0.0,  0.0,  0.0);
            glVertex3f( 0.0, -1.0, -1.0);
            glVertex3f( 1.0, -1.0,  0.0);
    }
    glEnd();

    glBegin(GL_QUADS);
    {
            glVertex3f(-1.0, -1.0,  0.0);
            glVertex3f( 0.0, -1.0, -1.0);
            glVertex3f( 1.0, -1.0,  0.0);
            glVertex3f( 0.0, -1.0,  1.0);
    }
    glEnd();


}
