#include "wizard_3d_.h"

Wizard_3D_::Wizard_3D_()
    : PawnGL ()
{}

Wizard_3D_::Wizard_3D_(const int &x, const int &y, const int &z,
                       const unsigned int &dir,
                       GLfloat angle_x, GLfloat angle_y, GLfloat angle_z, const bool &good)
  : PawnGL (x, y, z, dir, angle_x, angle_y, angle_z, good), translation_attaque_rogue(0)
{}

GLvoid Wizard_3D_::create_monster(GLuint textures[50])
{
    glPushMatrix();
    {
        glColor3f(255, 255, 255);

        //Body - dress
        glPushMatrix();
        {
            if(!_good) glColor3b(255.0f, 0.0f, 0.0f);
            else glColor3b(0.0f, 255.0f, 0.0f);
            glScalef(1.2f, 1.0f, 1.0f);
            dress(textures[6]);
        }
        glPopMatrix();

        //Head
        glPushMatrix();
        {
            glTranslatef(0.0f, 1.5f, 0.0f);
            glScalef(0.8f, 0.8f, 0.8f);
            head(textures[3]);
        }
        glPopMatrix();

        //Right mechanical arm
        glPushMatrix();
        {
            glTranslatef(-0.5f, 0.5f, -0.4f);
            glRotatef(180, 0.0, 1.0, 0.0);

            glScalef(0.75, 0.75, 0.75);
            rightMecaArm(angle_right_meca_arm, textures[7], textures[3]);
        }
        glPopMatrix();

        //First left mechanical arm
        glPushMatrix();
        {
            glTranslatef(0.28f, 0.6f, -0.45f);
            glRotatef(180.0, 0.0, 1.0, 0.0);

            glScalef(0.75, 0.75, 0.75);
            leftMecaArm(angle_left_meca_arm, textures[7], textures[3]);
        }
        glPopMatrix();

        //First left mechanical arm
        glPushMatrix();
        {
            glTranslatef(0.8f, 0.1f, -0.2f);
            glRotatef(-30, 1.0, 0.0, 0.0);
            glRotatef(-20, 0.0, 0.0, 1.0);
            glRotatef(180.0, 0.0, 1.0, 0.0);

            glScalef(0.75, 0.75, 0.75);
            leftMecaArm(angle_left_meca_arm, textures[7], textures[3]);
        }
        glPopMatrix();

        glFlush();
    }
    glPopMatrix();
}

GLvoid Wizard_3D_::attack()
{
    if (isAttacking())
    {
        glPushMatrix();
        {
            glTranslatef(0.0f, 0.0f, translation_attaque_rogue);

            glutSolidSphere(0.4, 20, 20);
            translation_attaque_rogue += 0.3f;
        }
        glPopMatrix();

        if (translation_attaque_rogue >= 20.0f) attacking();
    }
}

GLvoid Wizard_3D_::s_attack()
{} // NE FAIT RIEN


GLvoid Wizard_3D_::dress(GLuint textureRobe)
{
    glPushMatrix();
    {
        glScalef(1.0, 1.0, 1.0);
        Sphere s;
        s.createSphere(15, 15, textureRobe);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glRotatef(90, 1.0, 0.0, 0.0);

        Cylindre c;
        c.createCylindre(1.0, 1.0, 3.0, textureRobe);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0.0, -3.0, 0.0);
        glRotatef(-90, 1.0, 0.0, 0.0);
        Cone c;
        c.createCone(1.1f, 1.0);
    }
    glPopMatrix();
}

GLvoid Wizard_3D_::head(GLuint texture)
{
    glPushMatrix();
    {
        glRotatef(90, 1.0, 0.0, 0.0);
        Cylindre c;
        c.createCylindre(0.25, 0.3, 1.0, texture);
    }
    glPopMatrix();

    glTranslatef(0.0f, 0.625f, -1.1f);

    glPushMatrix();
    {
        glScalef(1.0, 1.25, 1.5);
        glRotatef(-90, 1.0, 0.0, 0.0);
        Pyramide p;
        p.createPyramide(texture);
    }
    glPopMatrix();
}

GLvoid Wizard_3D_::rightMecaArm(GLfloat angle_right_meca_arm, GLuint textureSphereBras, GLuint textureBras)
{
    glPushMatrix();
    {
        glScalef(0.55f, 0.55f, 0.55f);

        Sphere s;
        s.createSphere(10, 10, textureSphereBras);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glRotatef(60, -1.0, 0.0, 0.0);
        glRotatef(35, 0.0, 1.0, 0.0);

        glRotatef(angle_right_meca_arm, 1.0, 0.0, 0.0);

        Cylindre c;
        c.createCylindre(0.3, 0.3, 2.5, textureBras);

        glTranslatef(0.0, 0.0, 2.5);

        glPushMatrix();
        {
            glTranslatef(0.0f, 0.7f, 0.0f);
            glScalef(0.65f, 0.65f, 0.65f);

            Octahedron o;
            o.createOctahedron(textureSphereBras);
        }
        glPopMatrix();

        glRotatef(80, -1.0, 0.0, 0.0);

        c.createCylindre(0.3, 0.3, 2.5, textureBras);

        glTranslatef(0.0, 0.0, 2.5);

        glPushMatrix();
        {
            glScalef(0.55f, 0.55f, 0.55f);

            Sphere s;
            s.createSphere(10, 10, textureSphereBras);
        }
        glPopMatrix();
    }
    glPopMatrix();
}

GLvoid Wizard_3D_::leftMecaArm(GLfloat angle_left_meca_arm, GLuint textureSphereBras, GLuint textureBras)
{
    glPushMatrix();
    {
        glScalef(0.55f, 0.55f, 0.55f);

        Sphere s;
        s.createSphere(10, 10, textureSphereBras); // Sphere bras
    }
    glPopMatrix();

    //glRotatef(angle_left_meca_arm, 1.0, 0.0, 0.0);

    glPushMatrix();
    {
        glRotatef(100, -1.0, 0.0, 0.0);
        glRotatef(-25, 0.0, 1.0, 0.0);
        Cylindre c;
        c.createCylindre(0.3, 0.3, 2.5, textureBras);

        glTranslatef(0.0, 0.0, 2.5);

        glPushMatrix();
        {
            glScalef(0.5, 0.5, 0.5);

            Sphere s;
            s.createSphere(10, 10, textureSphereBras);
        }
        glPopMatrix();

        glRotatef(60, -1.0, 0.0, 0.0);
        glRotatef(80.0, 0.0, 0.0, 1.0);

        c.createCylindre(0.3, 0.3, 2.5, textureBras);

        glTranslatef(0.0, 0.0, 2.5);

        glPushMatrix();
        {
            glScalef(0.55f, 0.55f, 0.55f);

            Sphere s;
            s.createSphere(10, 10, textureSphereBras);
        }
        glPopMatrix();
    }
    glPopMatrix();
}
