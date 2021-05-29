#ifndef CYLINDRE_H
#define CYLINDRE_H

#include "library.hpp"

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

    GLvoid createCylindre(GLdouble topRadius, GLdouble baseRadius, GLdouble height, GLuint texture);

};

#endif // CYLINDRE_H
