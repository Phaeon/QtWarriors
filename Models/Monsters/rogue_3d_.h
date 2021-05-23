#ifndef ROGUE_3D_H
#define ROGUE_3D_H

#include "Models/Monsters/pawngl.h"

#include "Models/Objects/cone.h"
#include "Models/Objects/tile.h"
#include "Models/Objects/sphere.h"
#include "Models/Objects/cylindre.h"
#include "Models/Objects/pyramide.h"
#include "Models/Objects/octahedron.h"

class Rogue_3D_ : public PawnGL
{
public:
    Rogue_3D_();
    Rogue_3D_(const int &x, const int &y, const int &z,
                             const unsigned int &dir,
                             GLfloat angle_x, GLfloat angle_y, GLfloat angle_z);

    GLvoid create_monster(GLuint textures[50]) override;

    GLvoid attack() override;
    GLvoid s_attack() override;

private:
    GLfloat angle_pattes;

    GLvoid body(GLuint, GLuint);
    GLvoid head(GLuint, GLuint, GLuint);
    GLvoid frontLeg(GLuint, GLuint, GLuint, GLuint);
    GLvoid backLeg(GLuint, GLuint, GLuint, GLuint);
    GLvoid spine(GLuint);
    GLvoid horn(GLuint);
};

#endif // ROGUE_3D__H
