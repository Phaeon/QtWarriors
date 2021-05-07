#ifndef FLECHE_H
#define FLECHE_H

#include "library.h"
#include "tile.h"
#include "sphere.h"

#include <cassert>


class fleche
{
public:
    fleche();
    fleche(GLfloat taille_case, GLfloat x, GLfloat y, GLfloat z);

    void creer_fleche();
};

#endif // FLECHE_
