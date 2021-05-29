#ifndef PYRAMIDE_H
#define PYRAMIDE_H

#include "library.hpp"
#include "normale.h"

class Pyramide
{

public:
    Pyramide() = default;
    Pyramide(const Pyramide & P) = default;
    ~Pyramide() = default;

    GLvoid createPyramide(GLuint texture);
};

#endif // PYRAMIDE_H
