#include "disk.h"

GLvoid Disk::createDisk(float innerRadius, float outerRadius)
{
    GLUquadricObj* quadObj = gluNewQuadric();
    gluDisk(quadObj, innerRadius, outerRadius, 10, 10);
}
