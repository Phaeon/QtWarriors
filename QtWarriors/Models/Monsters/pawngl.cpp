#include "Models/Monsters/pawngl.h"

PawnGL::PawnGL()
{}

PawnGL::PawnGL(const int &x, const int &y, const int &z, const unsigned int &dir,
               GLfloat angle_x, GLfloat angle_y, GLfloat angle_z, const bool &good)
    : _x(x), _y(y), _z(z),
      _dir(dir),
      rotate_angle_x(angle_x), rotate_angle_y(angle_y), rotate_angle_z(angle_z),
      trans_x(0), trans_y(0), trans_z(0), _good(good)
{}

int PawnGL::getX() const
{
    return _x;
}

int PawnGL::getY() const
{
    return _y;
}

int PawnGL::getZ() const
{
    return _z;
}

unsigned int PawnGL::getDirection() const
{
    return _dir;
}

GLfloat PawnGL::getTransX()
{
    return trans_x;
}

GLfloat PawnGL::getTransY()
{
    return trans_y;
}

GLfloat PawnGL::getTransZ()
{
    return trans_z;
}

GLfloat PawnGL::getRotX()
{
    return rotate_angle_x;
}

GLfloat PawnGL::getRotY()
{
    return rotate_angle_y;
}

GLfloat PawnGL::getRotZ()
{
    return rotate_angle_z;
}

bool PawnGL::isAttacking() const
{
    return _isAttacking;
}

void PawnGL::attacking()
{
    _isAttacking = (_isAttacking) ? false : true;
}


