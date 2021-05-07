#ifndef SPHERE_H
#define SPHERE_H

#include "library.h"

class Sphere
{

public:
    Sphere() = default;
    Sphere(const Sphere & s) = default;
    ~Sphere() = default;

    GLvoid createSphere(int a, int b);

};

#endif // SPHERE_H
