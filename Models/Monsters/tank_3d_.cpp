#include "tank_3d_.h"

Tank_3D_::Tank_3D_()
    : PawnGL ()
{}

Tank_3D_::Tank_3D_(const int &x, const int &y, const int &z,
                         const unsigned int &dir,
                         GLfloat angle_x, GLfloat angle_y, GLfloat angle_z)
    : PawnGL (x, y, z, dir, angle_x, angle_y, angle_z), angle(0), angle_attaque(0), attacking(false)
{}

GLvoid Tank_3D_::create_monster(GLuint textures[50])
{
    glPushMatrix();
    {
        glColor3f(255, 255, 255);

        glScalef(0.5, 0.5, 0.5);

        //Body
        glPushMatrix();
        {
            glTranslatef(0.0, 1.1f, 0.0);
            body(textures[1]);
        }
        glPopMatrix();

        //Left arm
        glPushMatrix();
        {
            glTranslatef(10.0f, 4.0f, 0.0f);
            glRotatef(55, 0, 0, 1);
            glRotatef(180, 0, 0, 1);
            glRotatef(angle_attaque, 1, 0, 0);

            arm(textures[1]);
        }
        glPopMatrix();

        //Right arm
        glPushMatrix();
        {

            glTranslatef(-9.0f, 4.0f, -0.0f);
            glRotatef(-50, 0.0, 0.0, 1.0);
            glRotatef(180, 0, 0, 1);
            glRotatef(angle_attaque, 1, 0, 0);
            arm(textures[1]);
        }
        glPopMatrix();

        //Left leg
        glPushMatrix();
        {
            glRotatef(angle, 1, 0, 0); // Rotation lors du mouvement
            glTranslatef(4.7f, -0.5f, 0.0);
            leg(textures[0]);
        }
        glPopMatrix();

        //Right leg
        glPushMatrix();
        {
            glRotatef(angle, -1, 0, 0); // Rotation inverse lors du mouvement
            glTranslatef(-3.8f, -0.5f, 0.0f);
            leg(textures[0]);
        }
        glPopMatrix();

        glFlush();
    }
    glPopMatrix();
}

GLvoid Tank_3D_::attack()
{

    if (attacking)
    {
        if (angle_attaque >= 120.0f)
            angle_attaque -= 0.3f;
    }
    else
    {
        if (angle_attaque <= 150.0f)
            angle_attaque += 0.3f;
        else attacking = true;
    }

}

GLvoid Tank_3D_::s_attack()
{

}

GLvoid Tank_3D_::body(GLuint textureCorps)
{
    //Lower Body
    glPushMatrix();
    {
      glTranslatef(0.0f, 1.5f, 0.0f);
      glScalef(4.3f, 1.4f, 2.4f);
      glRotatef(30, 1, 1, 0);

      Decahedron d;
      d.createDecahedron(textureCorps);
    }
    glPopMatrix();

    glTranslatef(0.0f, 4.2f, 0.0f);

    //Main body
    glPushMatrix();
    {
      glScalef(6.5f, 2.5f, 3.0f);
      glRotatef(45, 1, 1, 0);

      Decahedron d;
      d.createDecahedron(textureCorps);
    }
    glPopMatrix();
}

GLvoid Tank_3D_::arm(GLuint texture)
{
    glPushMatrix();
    {
        glRotatef(15, 1, 1, 0);

        glRotatef(180, 0, 1, 0);

        //Arm-Body link
        glPushMatrix();
        {
            glScalef(1.2f, 0.4f, 1.2f);

            Decahedron d;
            d.createDecahedron(texture);
        }
        glPopMatrix();

        glTranslatef(0.0, 2.0, 0.0);

        //Arm
        glPushMatrix();
        {
            glScalef(1.2f, 1.2f, 1.2f);

            Decahedron d;
            d.createDecahedron(texture);
        }
        glPopMatrix();

        glTranslatef(0.0, 3.5, 0.0);

        //Arm
        glPushMatrix();
        {
            glRotatef(10, 0, 0, 1);
            glScalef(1.5f, 2.1f, 1.5f);

            Decahedron d;
            d.createDecahedron(texture);
        }
        glPopMatrix();
    }
    glPopMatrix();
}

GLvoid Tank_3D_::leg(GLuint texture)
{
    glPushMatrix();
    {
        glRotatef(15, 1, 1, 0);
        glScalef(1.2f, 0.4f, 1.2f);

        Decahedron d;
        d.createDecahedron(texture);
    }
    glPopMatrix();

    glTranslatef(0.0f, 1.2f, 0.0f);

    glPushMatrix();
    {
        glScalef(1.5f, 0.6f, 1.5f);

        Decahedron d;
        d.createDecahedron(texture);
    }
    glPopMatrix();
}
