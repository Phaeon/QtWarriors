#ifndef TANK_H
#define TANK_H

#include "library.h"
#include "Objects/decahedron.h"

class Tank
{
public:
    GLvoid displayTank(GLfloat angle, GLfloat angle_attaque);

private:
    GLvoid body();
    GLvoid arm();
    GLvoid leg();
};

#endif // TANK_H
