#include "fleche.h"

fleche::fleche()
{}

fleche::fleche(GLfloat taille_case, GLfloat x, GLfloat y, GLfloat z)
{
    glTranslatef(taille_case/2.0f + x, y, taille_case/2.0f + z);

    creer_fleche();
}

void fleche::creer_fleche()
{
    // Branche centrale
    glPushMatrix();
    {
        Tile T;

        glTranslatef(0.0f, 1.25f, 0.0f);
        glScalef(0.5f, 2.5f, 0.5f);

        T.create_cube();
    }
    glPopMatrix();

    // Branche droite
    glPushMatrix();
    {
        Tile T;

        glRotatef(50, 0, 0, 1);
        glTranslatef(0.75f, 0.0f, 0.0f);
        glScalef(1.5f, 0.5f, 0.5f);

        T.create_cube();
    }
    glPopMatrix();

    // Liaison branches gauche et droite
    glPushMatrix();
    {
        Sphere S;

        glScalef(0.29f, 0.25f, 0.27f);

        S.createSphere(20, 20);
    }
    glPopMatrix();

    // Branche gauche
    glPushMatrix();
    {
        Tile T;

        glRotatef(50, 0, 0, -1);
        glTranslatef(-0.75f, 0.0f, 0.0f);
        glScalef(1.5f, 0.5f, 0.5f);

        T.create_cube();
    }
    glPopMatrix();
}
