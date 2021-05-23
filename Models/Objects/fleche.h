#ifndef FLECHE_H
#define FLECHE_H

#include "library.hpp"
#include "tile.h"
#include "sphere.h"

#include <cassert>


class fleche
{
private:
     int _x;
     int _y;
     int _z;

public:
    fleche();
    fleche(GLfloat taille_case, int x, int y, int z);

    void creer_fleche(GLuint textures[50]);
    int getX() const;
    int getY() const;
    int getZ() const;
};

#endif // FLECHE_H
