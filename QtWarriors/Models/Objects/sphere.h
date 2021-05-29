#ifndef SPHERE_H
#define SPHERE_H

#include "library.hpp"

class Sphere
{

public:
    Sphere() = default;
    Sphere(const Sphere & s) = default;
    ~Sphere() = default;

    GLvoid createSphere(int a, int b, GLuint texture);

};

#endif // SPHERE_H
