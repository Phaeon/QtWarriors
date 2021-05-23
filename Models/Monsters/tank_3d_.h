#ifndef TANK_3D_H
#define TANK_3D_H

#include "library.hpp"
#include "Models/Objects/decahedron.h"
#include "Models/Monsters/pawngl.h"

class Tank_3D_ : public PawnGL
{
public:
    Tank_3D_();
    Tank_3D_(const int &x, const int &y, const int &z,
                             const unsigned int &dir,
                             GLfloat angle_x, GLfloat angle_y, GLfloat angle_z);

    GLvoid create_monster(GLuint textures[50]) override;

    GLvoid attack() override;
    GLvoid s_attack() override;

private:
    GLfloat angle, angle_attaque;
    bool attacking;

    GLvoid body(GLuint);
    GLvoid arm(GLuint);
    GLvoid leg(GLuint);
};

#endif // TANK_3D__H
