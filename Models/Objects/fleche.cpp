#include "fleche.h"

fleche::fleche()
{}

fleche::fleche(GLfloat taille_case, int x, int y, int z) : _x(x), _y(y), _z(z)
{
    //glTranslatef(taille_case/2.0f + x, y, taille_case/2.0f + z);

    //creer_fleche();
}

void fleche::creer_fleche(GLuint textures[50])
{
    // Branche centrale
    glPushMatrix();
    {
        Tile T;

        glTranslatef(0.0f, 0.8f, 0.0f);
        glScalef(0.2f, 1.5f, 0.1f);

        T.create_cube(textures[1]);
    }
    glPopMatrix();

    // Branche droite
    glPushMatrix();
    {
        Tile T;

        glRotatef(50, 0, 0, 1);
        glTranslatef(0.5f, 0.0f, 0.0f);
        glScalef(1.0f, 0.1f, 0.1f);

        T.create_cube(textures[1]);
    }
    glPopMatrix();

    // Liaison branches gauche et droite
    glPushMatrix();
    {
        Sphere S;

        glScalef(0.07f, 0.07f, 0.07f);

        S.createSphere(20, 20, textures[1]);
    }
    glPopMatrix();

    // Branche gauche
    glPushMatrix();
    {
        Tile T;

        glRotatef(50, 0, 0, -1);
        glTranslatef(-0.5f, 0.0f, 0.0f);
        glScalef(1.0f, 0.1f, 0.1f);

        T.create_cube(textures[1]);
    }
    glPopMatrix();
}

int fleche::getX() const
{
    return _x;
}

int fleche::getY() const
{
    return _y;
}

int fleche::getZ() const
{
    return _z;
}
