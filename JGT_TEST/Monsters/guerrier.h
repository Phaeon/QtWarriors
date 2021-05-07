#ifndef GUERRIER_H
#define GUERRIER_H

#include "library.h"
#include "Objects/pyramide.h"
#include "Objects/cylindre.h"
#include "Objects/octahedron.h"
#include "Objects/sphere.h"
#include "Objects/tile.h"
#include "Objects/decahedron.h"
#include "Objects/disk.h"

class Guerrier
{
public:
    GLvoid displayGuerrier(GLfloat angle_queue);

private:
    GLvoid body();
    GLvoid head();
    GLvoid horn(GLfloat angle);
    GLvoid arm();
    GLvoid leg();
    GLvoid tail(GLfloat angle);
};

#endif // GUERRIER_H
