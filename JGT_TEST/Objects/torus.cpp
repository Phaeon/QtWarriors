#include "torus.h"
#include "axes.h"

GLuint theTorus;

static void torus(int numc, int numt)
{
    glColor3f(1.0, 1.0, 1.0);
    double PiTimesTwo = 2 * (double)M_PI;
    for (int i = 0; i < numc; ++i)
    {
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= numt; ++j)
        {
            for (int k = 1; k >= 0; k--)
            {
                double s = (i + k) % numc + 0.5;
                double t = j % numt;

                double x = (1 + 1 * cos(s * PiTimesTwo / numc)) * cos(t * PiTimesTwo / numt);
                double y = (1 + 1 * cos(s * PiTimesTwo / numc)) * sin(t * PiTimesTwo / numt);
                double z = 1 * sin(s * PiTimesTwo / numc);
                glVertex3f(x, y, z);
            }
        }
        glEnd();
    }
}


void initListTorus()
{
    theTorus = glGenLists(1);
    glNewList(1, GL_COMPILE);
    glScalef(0.01, 0.01, 0.01);
    torus(8, 25);
    glScalef(10, 10, 10);
    glEndList();

    glShadeModel(GL_FLAT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

