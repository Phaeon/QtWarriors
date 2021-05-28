#ifndef WIZARD_3D_H
#define WIZARD_3D_H

#include "Models/Monsters/pawngl.h"

#include "Models/Objects/cone.h"
#include "Models/Objects/sphere.h"
#include "Models/Objects/cylindre.h"
#include "Models/Objects/pyramide.h"
#include "Models/Objects/octahedron.h"

class Wizard_3D_ : public PawnGL
{
public:
    Wizard_3D_();
    Wizard_3D_(const int &x, const int &y, const int &z,
               const unsigned int &dir,
               GLfloat angle_x, GLfloat angle_y, GLfloat angle_z,
               const bool &good);

    GLvoid create_monster(GLuint textures[50]) override;

    GLvoid attack() override;
    GLvoid s_attack() override;

private:
    GLfloat angle_right_meca_arm, angle_left_meca_arm, translation_attaque_rogue;


    GLvoid dress(GLuint);
    GLvoid head(GLuint);
    GLvoid rightMecaArm(GLfloat, GLuint, GLuint);
    GLvoid leftMecaArm(GLfloat, GLuint, GLuint);

};

#endif // WIZARD_3D__H
