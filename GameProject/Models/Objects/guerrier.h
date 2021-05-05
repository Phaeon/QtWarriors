#ifndef GUERRIER_H
#define GUERRIER_H

#include "library.hpp"
#include "Models/Objects/pyramide.h"
#include "Models/Objects/cylindre.h"
#include "Models/Objects/octahedron.h"
#include "Models/Objects/sphere.h"
#include "Models/Objects/tile.h"
#include "Models/Objects/decahedron.h"

class Guerrier
{
public:
    GLvoid displayGuerrier();

    GLvoid body();
    GLvoid head();
    GLvoid corne(GLfloat angle);
    GLvoid bras();
    GLvoid jambe();
    GLvoid queue(GLfloat angle);
};

#endif // GUERRIER_H
