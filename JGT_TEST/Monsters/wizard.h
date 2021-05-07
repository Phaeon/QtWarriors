#ifndef WIZARD_H
#define WIZARD_H

#include "library.h"
#include "Objects/pyramide.h"
#include "Objects/cylindre.h"
#include "Objects/sphere.h"
#include "Objects/cone.h"
#include "Objects/octahedron.h"
#include "Objects/disk.h"

class Wizard
{
public:
    GLvoid displayWizard(GLfloat angle_right_meca_arm, GLfloat angle_left_meca_arm);

private:
    GLvoid dress();
    GLvoid head();
    GLvoid rightMecaArm(GLfloat angle_right_meca_arm);
    GLvoid leftMecaArm(GLfloat angle_left_meca_arm);
};

#endif // WIZARD_H
