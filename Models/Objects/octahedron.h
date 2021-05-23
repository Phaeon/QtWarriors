#ifndef OCTAHEDRON_H
#define OCTAHEDRON_H

#include "library.hpp"
#include "normale.h"

class Octahedron
{
private:

public:
    Octahedron() = default;
    Octahedron(const Octahedron & O) = default;
    ~Octahedron() = default;

    GLvoid createOctahedron(GLuint texture);

};


#endif // OCTAHEDRON_H
