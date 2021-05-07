#ifndef PYRAMIDE_H
#define PYRAMIDE_H

#include "library.h"

class Pyramide
{

public:
    Pyramide() = default;
    Pyramide(const Pyramide & P) = default;
    ~Pyramide() = default;

    GLvoid createPyramide();
};

#endif // PYRAMIDE_H