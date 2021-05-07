#ifndef DECAHEDRON_H
#define DECAHEDRON_H

#include "library.h"
#include <vector>

class Decahedron
{
private:
    static std::vector<std::vector<GLfloat>> _sommets, _faces;

    GLvoid facesDecahedron();

public:
    Decahedron();
    ~Decahedron()=default;

    GLvoid createDecahedron();
};

#endif // DECAHEDRON_H
