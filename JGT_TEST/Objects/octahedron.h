#ifndef OCTAHEDRON_H
#define OCTAHEDRON_H

#include "library.h"

class Octahedron
{
private:

public:
    Octahedron() = default;
    Octahedron(const Octahedron & O) = default;
    ~Octahedron() = default;

    GLvoid createOctahedron();

};


#endif // OCTAHEDRON_H
