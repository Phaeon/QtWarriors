#ifndef NORMALE_H
#define NORMALE_H

#include "library.hpp"

struct normale {
    GLfloat x, y, z;
};

using n = normale;

n normale(float s0x, float s0y, float s0z,
               float s1x, float s1y, float s1z,
               float s2x, float s2y, float s2z);


#endif // NORMALE_H
