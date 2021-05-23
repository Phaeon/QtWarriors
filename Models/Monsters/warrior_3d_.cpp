#include "warrior_3d_.h"

Warrior_3D_::Warrior_3D_()
    : PawnGL ()
{}

Warrior_3D_::Warrior_3D_(const int &x, const int &y, const int &z,
                         const unsigned int &dir,
                         GLfloat angle_x, GLfloat angle_y, GLfloat angle_z)
    : PawnGL (x, y, z, dir, angle_x, angle_y, angle_z), rotation_queue(0)
{}

GLvoid Warrior_3D_::create_monster(GLuint textures[50])
{


    //Body
    glPushMatrix();
    {
        glColor3f(1, 1, 1);
        glTranslatef(0.0, 1.0, 0.0);
        glScalef(0.85f, 1.0f, 0.85f);
        body(textures[0]);
    }
    glPopMatrix();

    //Head
    glPushMatrix();
    {
        glColor3f(1, 1, 1);
        glTranslatef(0.0f, 1.5f, 0.05f);
        head(textures[1]);
    }
    glPopMatrix();

    //Right arm
    glPushMatrix();
    {
        glColor3f(1, 1, 1);
        glTranslatef(0.6f, 0.7f, 0.2f);
        glScalef(0.4f, 0.4f, 0.4f);
        bras(textures[6], textures[7]);
    }
    glPopMatrix();

    //Left arm
    glPushMatrix();
    {
        glTranslatef(-0.6f, 0.7f, 0.2f);
        glColor3f(1, 1, 1);
        glRotatef(180, 0.0, 1.0, 0.0);
        glScalef(0.4f, 0.4f, 0.4f);
        bras(textures[6], textures[7]);
    }
    glPopMatrix();

    //Right Leg
    glPushMatrix();
    {
        glTranslatef(-0.8f, -2.0, 0.0);
        glColor3f(1, 1, 1);
        glRotatef(180, 0.0, 1.0, 0.0);
        glScalef(0.4f, 0.4f, 0.4f);
        jambe(textures[7], textures[7]);
    }
    glPopMatrix();

    //Right Leg
    glPushMatrix();
    {
        glColor3f(1, 1, 1);
        glTranslatef(0.8f, -2.0f, 0.0f);
        glScalef(0.4f, 0.4f, 0.4f);
        jambe(textures[7], textures[7]);
    }
    glPopMatrix();

    //Tail
    glPushMatrix();
    {
        glTranslatef(0.0f, -1.5f, -0.7f);
        glRotatef(90, 0.0, 1.0, 0.0);
        glRotatef(33, 1.0, 0.0, 0.0);
        glColor3f(1, 0.5, 0);
        queue(rotation_queue, textures[0]);
    }
    glPopMatrix();

    //Armor
    glPushMatrix();
    {

        glTranslatef(0.0f, -1.25f, 0.0f);
        //glScalef(1.0, 1.0, 1.0);
        glRotatef(90, 0.0, 1.0, 0.0);
        glColor3f(1, 1, 1);

        Decahedron d;
        d.createDecahedron(textures[2]);
    }
    glPopMatrix();

    glFlush();
}

GLvoid Warrior_3D_::attack()
{
    if (rotate_angle_y <= 360.f)
        rotate_angle_y += 3.0f;
    else {
        if (rotation_queue >= 0) {
            rotation_queue -= 0.4f;
        }
        rotate_angle_y = 0.0f;
    }

    if (rotate_angle_y <= 180.0f)
        rotation_queue += 0.4f;

}

GLvoid Warrior_3D_::s_attack()
{

}

GLvoid Warrior_3D_::body(GLuint texture)
{
    Octahedron o;
    glPushMatrix();
    {

        glScalef(1.9f, 2.5f, 2.0f);
        o.createOctahedron(texture);
    }
    glPopMatrix();
}

GLvoid Warrior_3D_::head(GLuint texture)
{
    glPushMatrix();
    {

        glScalef(1.0f, 1.0f, 1.2f);
        Sphere s;
        s.createSphere(6.0, 6.0, texture);

        glPushMatrix();
        {

            glTranslatef(0.5f, 0.5f, -0.3f);
            glScalef(0.6f, 0.6f, 0.6f);
            corne(0.0);
        }
        glPopMatrix();

        glPushMatrix();
        {

            glRotatef(180, 0.0, 1.0, 0.0);
            glTranslatef(0.5f, 0.5f, 0.3f);
            glScalef(0.6f, 0.6f, 0.6f);
            corne(0.0);
        }
        glPopMatrix();
    }
    glPopMatrix();
}

GLvoid Warrior_3D_::corne(GLfloat angle) // ! - Remplacer les glut ! - //
{
    glPushMatrix();
    {
        glColor3f(1, 0.5, 0);
        glRotatef(-angle, 0, 0, -1);
        glRotatef(100, 0, 0, 1);

        for (size_t i = 0; i < 3; i++)
        {
            glRotatef(20 - angle, 0, 0, 1);

            glTranslatef(0.0f, -0.45f, 0.0f);

            glPushMatrix();
            {
                glTranslatef(0.0f, 0.45f, 0.0f);

                glPushMatrix();
                {
                    glRotatef(90, 1, 0, 0);
                    GLUquadricObj* quadObj = gluNewQuadric();
                    gluCylinder(quadObj, 0.5, 0.45, 0.5, 6, 6);
                }
                glPopMatrix();

            }
            glPopMatrix();
        }

        glPushMatrix();
        {
            glRotatef(90, 1, 0, 0);
            GLUquadricObj* quadObj = gluNewQuadric();
            gluCylinder(quadObj, 0.5, 0.05, 0.75, 6, 6);
        }
        glPopMatrix();
    }
    glPopMatrix();
}

GLvoid Warrior_3D_::bras(GLuint textureCube, GLuint textureOcta)
{
    glPushMatrix();
    {

        glScalef(1.3f, 1.3f, 1.3f);
        Octahedron o;
        o.createOctahedron(textureOcta);
    }
    glPopMatrix();

    glTranslatef(0.7f, -0.25f, -0.0f);

    glPushMatrix();
    {

        glScalef(1.3f, 1.3f, 0.7f);
        Octahedron o;
        o.createOctahedron(textureOcta);
    }
    glPopMatrix();

    glTranslatef(1.5f, -1.2f, 0.0f);
    glRotatef(90, 0.0, 0.0, 1.0);

    glPushMatrix();
    {

        glRotatef(45, 0.0, 1.0, 0.0);
        glScalef(0.8f, 5.0f, 0.8f);
        Tile t;
        t.create_cube(textureCube);
    }
    glPopMatrix();

    glPushMatrix();
    {

        glTranslatef(0.0f, -1.8f, 0.0f);
        glScalef(0.9f, 0.9f, 0.9f);
        Octahedron o;
        o.createOctahedron(textureOcta);
    }
    glPopMatrix();

            // ! - Essayer idee ! - //

    /*
    glTranslatef(0.0, -2.0, 0.0);

    glPushMatrix();
    {
        glRotatef(45, 0.0, 1.0, 0.0);
        glScalef(1.0, 5.0, 1.0);
        Tile t;
        t.create_cube();
    }
    glPopMatrix();
    */

    glTranslatef(0.0, -4.0, 0.0);

    glPushMatrix();
    {

        glRotatef(45, 0.0, 1.0, 0.0);
        glScalef(0.8f, 5.0f, 0.8f);
        Tile t;
        t.create_cube(textureCube);
    }
    glPopMatrix();

    glPushMatrix();
    {

        glTranslatef(0.0f, -1.8f, 0.0f);
        glScalef(0.9f, 0.9f, 0.9f);
        Octahedron o;
        o.createOctahedron(textureOcta);
    }
    glPopMatrix();
}

GLvoid Warrior_3D_::jambe(GLuint texture, GLuint textureOcta)
{
    glPushMatrix();
        {

            glPushMatrix();
            {

                glScalef(1.1f, 1.1f, 1.1f);
                Octahedron o;
                o.createOctahedron(textureOcta);
            }
            glPopMatrix();

            glTranslatef(0.0f, -3.0f, 0.0f);

            glPushMatrix();
            {

                glRotatef(45, 0.0f, 1.0f, 0.0f);
                glScalef(0.8f, 4.0, 0.8f);

                Tile t;
                t.create_cube(texture);
            }
            glPopMatrix();

            glPushMatrix();
            {

                glTranslatef(0.0f, -1.25f, 0.0f);
                glScalef(0.9f, 0.9f, 0.9f);

                Octahedron o;
                o.createOctahedron(textureOcta);
            }
            glPopMatrix();

            glTranslatef(0.0f, -4.0f, 0.0f);

            glPushMatrix();
            {

                glRotatef(45, 0.0, 1.0, 0.0);
                glScalef(0.8f, 4.0f, 0.8f);

                Tile t;
                t.create_cube(texture);
            }
            glPopMatrix();

            glTranslatef(0.0, -1.0, 0.0);

            // ! - Fermer Pied - ! //

            Pyramide p;
            p.createPyramide(texture);

        }
        glPopMatrix();
}

GLvoid Warrior_3D_::queue(GLfloat angle, GLuint texture) // ! - Remplacer les glut ! - //
{
    glRotatef(-angle, 0, 0, -1);
    glRotatef(100, 0, 0, 1);


    for (size_t i = 0; i < 5; i++)
    {
        glRotatef(15 - angle, 0, 0, 1);

        glTranslatef(0.0f, -0.40f, 0.0f);

        glPushMatrix();
        {
            glTranslatef(0.0f, 0.40f, 0.0f);

            glPushMatrix();
            {
                glRotatef(90, 1, 0, 0);
                GLUquadricObj* quadObj = gluNewQuadric();
                gluCylinder(quadObj, 0.5, 0.45, 0.5, 6, 6);
            }
            glPopMatrix();

        }
        glPopMatrix();
    }


    for (size_t i = 0; i < 10; i++)
    {
        glRotatef(5 - angle, 0, 0, -1);
        glTranslatef(0.0f, -0.40f, 0.0f);
        glPushMatrix();
        {
            glTranslatef(0.0, 0.40f, 0.0);

            glPushMatrix();
            {
                glRotatef(90, 1, 0, 0);
                GLUquadricObj* quadObj = gluNewQuadric();
                gluCylinder(quadObj, 0.5, 0.45, 0.5, 6, 6);

            }
            glPopMatrix();

        }
        glPopMatrix();
    }

    glPushMatrix();
    {

        Sphere s;
        glScalef(0.8f, 0.8f, 0.8f);
        s.createSphere(10, 10, texture);
    }
    glPopMatrix();
}
