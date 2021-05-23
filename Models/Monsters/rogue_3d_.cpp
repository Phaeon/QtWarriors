#include "rogue_3d_.h"


Rogue_3D_::Rogue_3D_()
    : PawnGL ()
{}

Rogue_3D_::Rogue_3D_(const int &x, const int &y, const int &z,
                         const unsigned int &dir,
                         GLfloat angle_x, GLfloat angle_y, GLfloat angle_z)
    : PawnGL (x, y, z, dir, angle_x, angle_y, angle_z), angle_pattes()
{}


GLvoid Rogue_3D_::create_monster(GLuint textures[50])
{
    glPushMatrix();
    {

        //Body
        glPushMatrix();
        {
            body(textures[0], textures[0]);
        }
        glPopMatrix();

        //Head
        glPushMatrix();
        {
            glRotatef(33, 1.0, 0.0, 0.0);
            glTranslatef(0.0, 1.75, 0.0);

            glRotatef(90, 1.0 , 0.0, 0.0);
            glColor3f(1, 1, 1);
            head(textures[0], textures[1], textures[2]);
        }
        glPopMatrix();

        //Left front leg
        glPushMatrix();
        {
            glColor3f(1, 1, 1);
            glTranslatef(1.25f, -0.3f, 0.3f);
            frontLeg(textures[0], textures[1], textures[2], textures[3]);
        }
        glPopMatrix();

        //Right front leg
        glPushMatrix();
        {
            glColor3f(1, 1, 1);
            glTranslatef(-1.25f, -0.3f, 0.3f);
            frontLeg(textures[0], textures[1], textures[2], textures[3]);
        }
        glPopMatrix();

        //Right back leg
        glPushMatrix();
        {
            glColor3f(1, 1, 1);
            glTranslatef(0.65f, -0.8f, -3.5f);
            backLeg(textures[0], textures[1], textures[2], textures[3]);
        }
        glPopMatrix();

        //Left back leg
        glPushMatrix();
        {
            glColor3f(1, 1, 1);
            glTranslatef(-0.65f, -0.8f, -3.5f);
            backLeg(textures[0], textures[1], textures[2], textures[3]);
        }
        glPopMatrix();

        glFlush();
    }
    glPopMatrix();
}

GLvoid Rogue_3D_::attack()
{

}

GLvoid Rogue_3D_::s_attack()
{

}

GLvoid Rogue_3D_::body(GLuint textureSphere, GLuint textureColVert)
{

    //Sphere main body
    glPushMatrix();
    {
        glColor3f(0, 1, 0);
        glScalef(1.35f, 1.35f, 1.35f);

        Sphere s;
        s.createSphere(10, 10, textureSphere);
    }
    glPopMatrix();

    glTranslatef(0.0f, -0.4f, -2.0f);

    //Cylindre/Scaled sphere second body
    glPushMatrix();
    {
        Sphere s;

        glColor3f(0, 1, 0);
        glRotatef(-10, 1.0, 0.0, 0.0);
        glScalef(0.6f, 0.6f, 2.5f);
        s.createSphere(10, 10, textureSphere);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0, 1, 0);
        glTranslatef(0.0, 1.25, 1.5);
        spine(textureColVert);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glColor3f(0, 1, 0);
        glTranslatef(0.0, 0.25, -0.75);
        spine(textureColVert);
    }
    glPopMatrix();
}

GLvoid Rogue_3D_::head(GLuint textureSphere, GLuint textureCyl, GLuint textureCornes)
{
    glPushMatrix();
    {
        Cylindre c;
        c.createCylindre(0.35, 0.35, 0.5, textureCyl);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0.0, 0.0, -0.5);

        glScalef(0.8f, 1.1f, 0.8f);
        Sphere s;
        s.createSphere(10, 10, textureSphere);

    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0.0, 0.5, -1.25);
        horn(textureCornes);
    }
    glPopMatrix();
}

GLvoid Rogue_3D_::frontLeg(GLuint textureSphere, GLuint textureCyl, GLuint textureCube, GLuint texturePattes)
{

    glPushMatrix();
    {
        glScalef(0.5, 0.5, 0.5);
        Sphere s;
        s.createSphere(10, 10, textureSphere);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glRotatef(133, 1.0, 0.0, 0.0);

        glRotatef(-angle_pattes*2, 1, 0, 0); // Rotation lors du saut

        Cylindre c;
        glPushMatrix();
        {
            c.createCylindre(0.5, 0.5, 2.0, textureCyl);
            //gluCylinder(quadObj, 0.5, 0.5, 2.0, 10, 10);
        }
        glPopMatrix();
        //GLUquadricObj* quadObj = gluNewQuadric();
        //gluCylinder(quadObj, 0.5, 0.5, 2.0, 10, 10);

        glTranslatef(0.0, 0.0, 2.0);

        glPushMatrix();
        {
            glScalef(0.5, 0.5, 0.5);
            Sphere s;
            s.createSphere(10, 10, textureSphere);
        }
        glPopMatrix();

        glRotatef(-90, 1.0, 0.0, 0.0);

        glRotatef(-(angle_pattes*2), 1, 0, 0); // Rotation lors du saut

        glPushMatrix();
        {
            c.createCylindre(0.5, 0.5, 2.0, textureCyl);
            //gluCylinder(quadObj, 0.5, 0.5, 2.0, 10, 10);
        }
        glPopMatrix();

        glTranslatef(0.0, 0.0, 2.0);

        glRotatef(-(angle_pattes*2), 1, 0, 0); // Rotation lors du saut

        //Pied
        glPushMatrix();
        {
            glRotatef(45, 1.0, 0.0, 0.0);
            glTranslatef(0.0f, 0.2f, 0.0f);
            glScalef(0.9f, 1.5f, 0.8f);

            Tile t;
            t.create_cube(textureCube);

            glPushMatrix();
            {
                glTranslatef(0.0, 0.0, -0.45f);
                glTranslatef(0.0, 0.1f, 0.0);

                glRotatef(90, -1.0, 0.0, 0.0);

                glScalef(0.5, 1.0, 1.0);

                Pyramide p;
                p.createPyramide(texturePattes);
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPopMatrix();
}

GLvoid Rogue_3D_::backLeg(GLuint textureSphere, GLuint textureCyl, GLuint textureCube, GLuint texturePattes)
{
    glPushMatrix();
    {
        glScalef(0.8f, 0.8f, 0.8f);

        glPushMatrix();
        {
            glScalef(0.5, 0.5, 0.5);
            Sphere s;
            s.createSphere(10, 10, textureSphere);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glRotatef(133, 1.0, 0.0, 0.0);

            glRotatef(-(angle_pattes*2), 1, 0, 0);

            Cylindre c;
            c.createCylindre(0.5, 0.5, 2.0, textureCyl);
            glTranslatef(0.0, 0.0, 2.0);

            glPushMatrix();
            {
                glScalef(0.5, 0.5, 0.5);
                Sphere s;
                s.createSphere(10, 10, textureSphere);
            }
            glPopMatrix();

            glRotatef(-90, 1.0, 0.0, 0.0);

            c.createCylindre(0.5, 0.5, 2.0, textureCyl);

            glTranslatef(0.0, 0.0, 2.0);

            glRotatef(-(angle_pattes*2), 1, 0, 0);

            glPushMatrix();
            {
                glRotatef(45, 1.0, 0.0, 0.0);

                glPushMatrix();
                {
                    glScalef(0.5, 0.5, 0.5);
                    Sphere s;
                    s.createSphere(10, 10, textureSphere);
                }
                glPopMatrix();

                c.createCylindre(0.5, 0.5, 0.5, textureCyl);

                glTranslatef(0.0, 0.25, 0.5);
                glScalef(0.9f, 1.5f, 0.8f);

                Tile t;
                t.create_cube(textureCube);

                glRotatef(-(angle_pattes*2), 1, 0, 0);

                //Pied
                glPushMatrix();
                {
                    glTranslatef(0.0, 0.0, -0.45f);
                    glTranslatef(0.0, 0.1f, 0.0);

                    glRotatef(90, -1.0, 0.0, 0.0);

                    glScalef(0.5f, 1.0f, 1.0f);

                    Pyramide p;
                    p.createPyramide(texturePattes);
                }
                glPopMatrix();
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPopMatrix();
}

GLvoid Rogue_3D_::spine(GLuint texture)
{
    glScalef(0.01f, 0.8f, 0.8f);
    Sphere s;
    s.createSphere(10, 10, texture);
}

GLvoid Rogue_3D_::horn(GLuint texture)
{
    glScalef(0.01f, 0.5f, 0.5f);
    Sphere s;
    s.createSphere(10, 10, texture);
}
