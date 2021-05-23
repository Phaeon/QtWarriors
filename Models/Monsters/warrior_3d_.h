#ifndef WARRIOR_3D_H
#define WARRIOR_3D_H

#include "Models/Monsters/pawngl.h"

#include "Models/Objects/tile.h"
#include "Models/Objects/sphere.h"
#include "Models/Objects/octahedron.h"
#include "Models/Objects/pyramide.h"
#include "Models/Objects/decahedron.h"

class Warrior_3D_ : public PawnGL
{
public:
    Warrior_3D_();
    Warrior_3D_(const int &x, const int &y, const int &z, const unsigned int &dir,
                GLfloat angle_x, GLfloat angle_y, GLfloat angle_z);

    GLvoid create_monster(GLuint textures[50]) override;

    GLvoid attack() override;
    GLvoid s_attack() override;

private:
    GLfloat rotation_queue;

    GLvoid body(GLuint);
    GLvoid head(GLuint);
    GLvoid corne(GLfloat angle);
    GLvoid bras(GLuint, GLuint);
    GLvoid jambe(GLuint, GLuint);
    GLvoid queue(GLfloat angle, GLuint);
};

#endif // WARRIOR_3D__H
