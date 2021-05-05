#ifndef DECAHEDRON_H
#define DECAHEDRON_H

#include "library.hpp"
#include <vector>

class Decahedron
{
private:
    static std::vector<std::vector<GLfloat>> _sommets, _faces;

public:
    Decahedron();
    ~Decahedron()=default;

    GLvoid facesDecahedron();
    GLvoid createDecahedron();
};

#endif // DECAHEDRON_H
