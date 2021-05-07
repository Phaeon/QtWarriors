#include "cylindre.h"

void Cylindre::createCylindre(float topRadius, float baseRadius, float Height)
{
    GLUquadricObj* quadObj = gluNewQuadric();
    gluCylinder(quadObj, topRadius, baseRadius, Height, 10, 10);
}
