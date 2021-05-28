#ifndef DECAHEDRON_H
#define DECAHEDRON_H

#include "library.hpp"
#include "normale.h"
#include <vector>

class Decahedron
{
private:
    static std::vector<std::vector<GLfloat>> _sommets, _faces;

public:
    Decahedron();
    ~Decahedron()=default;

    GLvoid facesDecahedron();
    GLvoid createDecahedron(GLuint texture);
};

#endif // DECAHEDRON_H
