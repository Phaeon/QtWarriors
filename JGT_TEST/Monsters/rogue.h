#ifndef ROGUE_H
#define ROGUE_H

#include "library.h"
#include "Objects/pyramide.h"
#include "Objects/cylindre.h"
#include "Objects/octahedron.h"
#include "Objects/sphere.h"
#include "Objects/tile.h"
#include "Objects/decahedron.h"

class Rogue
{
public:
    GLvoid displayRogue(GLfloat angle_pattes);

private:
    GLvoid body();
    GLvoid head();
    GLvoid frontLeg(GLfloat angle_pattes);
    GLvoid backLeg(GLfloat angle_pattes);
    GLvoid spine();
    GLvoid horn();
};

#endif // ROGUE_H
