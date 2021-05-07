#include "sphere.h"

GLvoid Sphere::createSphere(int slices, int stacks)
{
    float da = ( M_PI / slices );
        float db = ( 2.0f * M_PI / stacks );
        glBegin(GL_QUADS);

        glNormal3f(0,0,1);
        for( int i = 0; i < slices + 1 ; i++ )
        {
             float r0 = sin ( i * da );
             float y0 = cos ( i * da );
             float r1 = sin ( (i+1) * da );
             float y1 = cos ( (i+1) * da );

             for( int j = 0; j < stacks + 1 ; j++ )
             {
                  float x0 = r0 * sin( j * db );
                  float z0 = r0 * cos( j * db );
                  float x1 = r0 * sin( (j+1) * db );
                  float z1 = r0 * cos( (j+1) * db );

                  float x2 = r1 * sin( j * db );
                  float z2 = r1 * cos( j * db );
                  float x3 = r1 * sin( (j+1) * db );
                  float z3 = r1 * cos( (j+1) * db );

                  glVertex3f(x0,y0,z0);
                  glVertex3f(x1,y0,z1);
                  glVertex3f(x3,y1,z3);
                  glVertex3f(x2,y1,z2);
             }
        }

        glEnd();
}
