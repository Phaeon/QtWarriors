#include "octahedron.h"

GLvoid Octahedron::createOctahedron()
{
    glBegin(GL_TRIANGLES);

    //triangle superieur avant gauche
            glVertex3f( 0.0,  0.0,  0.0);
            glVertex3f( 0.0, -1.0,  1.0);
            glVertex3f( 1.0, -1.0,  0.0);

    //triangle superieur avant droit
            glVertex3f( 0.0,  0.0,  0.0);
            glVertex3f(-1.0, -1.0,  0.0);
            glVertex3f( 0.0, -1.0,  1.0);

    //triangle superieur arriere droit
            glVertex3f( 0.0,  0.0,  0.0);
            glVertex3f(-1.0, -1.0,  0.0);
            glVertex3f( 0.0, -1.0, -1.0);

    //triangle superieur arriere gauche
            glVertex3f( 0.0,  0.0,  0.0);
            glVertex3f( 0.0, -1.0, -1.0);
            glVertex3f( 1.0, -1.0,  0.0);

                    //	//

    //triangle inferieur avant gauche
        glVertex3f( 0.0, -2.0,  0.0);
            glVertex3f( 0.0, -1.0,  1.0);
            glVertex3f( 1.0, -1.0,  0.0);

    //triangle inferieur avant droit
            glVertex3f( 0.0, -2.0,  0.0);
            glVertex3f(-1.0, -1.0,  0.0);
            glVertex3f( 0.0, -1.0,  1.0);

    //triangle inferieur arriere droit
            glVertex3f( 0.0, -2.0,  0.0);
            glVertex3f(-1.0, -1.0,  0.0);
            glVertex3f( 0.0, -1.0, -1.0);

    //triangle inferieur arriere gauche
            glVertex3f( 0.0, -2.0,  0.0);
            glVertex3f( 0.0, -1.0, -1.0);
            glVertex3f( 1.0, -1.0,  0.0);

        glEnd();
}
