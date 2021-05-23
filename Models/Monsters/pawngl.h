#ifndef PAWNGL_H
#define PAWNGL_H

#include "library.hpp"
#include "QVector"

class PawnGL
{
private:
    int _x, _y, _z;
    unsigned int _dir; // 1 : devant, 2 : derrière, 3 : gauche, 4 : droite

protected:
    GLfloat rotate_angle_x, rotate_angle_y, rotate_angle_z;
    GLfloat trans_x, trans_y, trans_z;

public:
    PawnGL();
    PawnGL(const int &x, const int &y, const int &z, const unsigned int &dir,
           GLfloat angle_x, GLfloat angle_y, GLfloat angle_z);

    virtual GLvoid create_monster(GLuint textures[50]) = 0;

    int getX() const;
    int getY() const;
    int getZ() const;

    unsigned int getDirection() const;

    GLfloat getTransX();
    GLfloat getTransY();
    GLfloat getTransZ();

    GLfloat getRotX();
    GLfloat getRotY();
    GLfloat getRotZ();


    // Attacks (Fonctions à ne pas utiliser dans paintGL : boucles while)
    virtual GLvoid attack() = 0;
    virtual GLvoid s_attack() = 0;
};

#endif // PAWNGL_H
