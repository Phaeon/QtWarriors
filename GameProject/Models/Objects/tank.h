#ifndef TANK_H
#define TANK_H

#include "library.hpp"
#include "Models/Objects/decahedron.h"

class Tank
{
public:
    GLvoid displayTank();

private:
    GLvoid body();
    GLvoid arm();
    GLvoid leg();
};

#endif // TANK_H
