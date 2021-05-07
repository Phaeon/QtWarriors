#ifndef CYLINDRE_H
#define CYLINDRE_H

#include "library.h"

class Cylindre
{
private:
    float _radius;
    float _height;
    int   _stacks;

public:
    Cylindre() = default;
    Cylindre(const Cylindre & c) = default;
    ~Cylindre() = default;

    GLvoid createCylindre(float topRadius, float baseRadius, float Height);

};

#endif // CYLINDRE_H
