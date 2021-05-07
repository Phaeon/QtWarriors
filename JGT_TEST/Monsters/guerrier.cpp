#include "guerrier.h"

GLvoid Guerrier::displayGuerrier(GLfloat angle_queue)
{
    glPushMatrix();
    {
        glClear(GL_COLOR_BUFFER_BIT);

    //Body
        glPushMatrix();
        {
            glTranslatef(0.0, 1.0, 0.0);
            glScalef(0.85, 1.0, 0.85);
            body();
        }
        glPopMatrix();

    //Head
        glPushMatrix();
        {
            glTranslatef(0.0, 1.5, 0.05);
            head();
        }
        glPopMatrix();

    //Right arm
        glPushMatrix();
        {
            glTranslatef(0.7, 0.7, 0.2);
            glScalef(0.4, 0.4, 0.4);
            arm();
        }
        glPopMatrix();

    //Left arm
        glPushMatrix();
        {
            glTranslatef(-0.7, 0.7, 0.2);

            glRotatef(180, 0.0, 1.0, 0.0);
            glScalef(0.4, 0.4, 0.4);
            arm();
        }
        glPopMatrix();

    //Right Leg
        glPushMatrix();
        {
            glTranslatef(-0.8, -2.0, 0.0);

            glRotatef(180, 0.0, 1.0, 0.0);
            glScalef(0.4, 0.4, 0.4);
            leg();
        }
        glPopMatrix();

    //Right Leg
        glPushMatrix();
        {
            glTranslatef(0.8, -2.0, 0.0);
            glScalef(0.4, 0.4, 0.4);
            leg();
        }
        glPopMatrix();

    //Tail

        glPushMatrix();
        {
            glTranslatef(0.0, -1.5, -0.7);
            glRotatef(90, 0.0, 1.0, 0.0);
            glRotatef(33, 1.0, 0.0, 0.0);
            tail(angle_queue);
        }
        glPopMatrix();

    //Armor
        glPushMatrix();
        {
            glTranslatef(0.0, -1.25, 0.0);
            //glScalef(1.0, 1.0, 1.0);
            glRotatef(90, 0.0, 1.0, 0.0);

            Decahedron d;
            d.createDecahedron();
        }
        glPopMatrix();

        glFlush();
    }
    glPopMatrix();
}

GLvoid Guerrier::body()
{
    Octahedron o;
    glPushMatrix();
    {
        glScalef(1.9, 2.5, 2);
        o.createOctahedron();
    }
    glPopMatrix();
}

GLvoid Guerrier::head()
{
    glPushMatrix();
    {
        glScalef(1.0, 1.0, 1.2);
        Sphere s;
        s.createSphere(6.0, 6.0);

        glPushMatrix();
        {
            glTranslatef(0.5, 0.5, -0.3);
            glScalef(0.6, 0.6, 0.6);
            horn(0.0);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glRotatef(180, 0.0, 1.0, 0.0);
            glTranslatef(0.5, 0.5, 0.3);
            glScalef(0.6, 0.6, 0.6);
            horn(0.0);
        }
        glPopMatrix();
    }
    glPopMatrix();
}

GLvoid Guerrier::horn(GLfloat angle)
{
    glPushMatrix();
    {
        glRotatef(-angle, 0, 0, -1);
        glRotatef(100, 0, 0, 1);

        for (size_t i = 0; i < 3; i++)
        {
            glRotatef(20 - angle, 0, 0, 1);

            glTranslatef(0.0, -0.45, 0.0);

            glPushMatrix();
            {
                glTranslatef(0.0, 0.45, 0.0);

                glPushMatrix();
                {
                    glRotatef(90, 1, 0, 0);
                    Cylindre c;
                    c.createCylindre(0.4, 0.35, 0.5);
                    //GLUquadricObj* quadObj = gluNewQuadric();
                    //gluCylinder(quadObj, 0.5, 0.45, 0.5, 6, 6);
                }
                glPopMatrix();

            }
            glPopMatrix();
        }

        glPushMatrix();
        {
            glRotatef(90, 1, 0, 0);
            Cylindre c;
            c.createCylindre(0.4, 0.2, 0.7);
            //GLUquadricObj* quadObj = gluNewQuadric();
            //gluCylinder(quadObj, 0.5, 0.05, 0.75, 6, 6);

            glTranslatef(0.0, 0.0, 0.7);

            Disk d;
            d.createDisk(0.0, 0.2);
            //GLUquadricObj* quadObj = gluNewQuadric();
            //gluDisk(quadObj, 0.0, 0.2, 10, 10);

        }
        glPopMatrix();
    }
    glPopMatrix();
}

GLvoid Guerrier::arm()
{
    //Epaules
    glPushMatrix();
    {
        glScalef(1.3, 1.3, 1.3);
        Octahedron o;
        o.createOctahedron();
    }
    glPopMatrix();

    glTranslatef(0.7, -0.25, -0.0);

    glPushMatrix();
    {
        glScalef(1.3, 1.3, 0.7);
        Octahedron o;
        o.createOctahedron();
    }
    glPopMatrix();

    glTranslatef(1.5, -2.5, 0.0);
    glRotatef(45, 0.0, 0.0, 1.0);

    //bras
    glPushMatrix();
    {
        glRotatef(45, 0.0, 1.0, 0.0);
        glScalef(0.8, 5.0, 0.8);
        Tile t;
        t.create_cube();
    }
    glPopMatrix();

    //coude
    glPushMatrix();
    {
        glTranslatef(0.0, -1.8, 0.0);
        glScalef(0.9, 0.9, 0.9);
        Octahedron o;
        o.createOctahedron();
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

    glTranslatef(0.0, -4.2, 0.0);
    glTranslatef(-1.5, 0.0, 0.0);
    glRotatef(-45, 0.0, 0.0, 1.0);

    //avant-bras
    glPushMatrix();
    {
        glRotatef(45, 0.0, 1.0, 0.0);
        glScalef(0.8, 5.0, 0.8);
        Tile t;
        t.create_cube();
    }
    glPopMatrix();

    //main
    glPushMatrix();
    {
        glTranslatef(0.0, -1.8, 0.0);
        glScalef(0.9, 0.9, 0.9);
        Octahedron o;
        o.createOctahedron();
    }
    glPopMatrix();
}

GLvoid Guerrier::leg()
{
    glPushMatrix();
        {
            glPushMatrix();
            {
                glScalef(1.1, 1.1, 1.1);
                Octahedron o;
                o.createOctahedron();
            }
            glPopMatrix();

            glTranslatef(0.0, -3.0, 0.0);

            glPushMatrix();
            {
                glRotatef(45, 0.0, 1.0, 0.0);
                glScalef(0.8, 4.0, 0.8);

                Tile t;
                t.create_cube();
            }
            glPopMatrix();

            glPushMatrix();
            {
                glTranslatef(0.0, -1.25, 0.0);
                glScalef(0.9, 0.9, 0.9);

                Octahedron o;
                o.createOctahedron();
            }
            glPopMatrix();

            glTranslatef(0.0, -4.0, 0.0);

            glPushMatrix();
            {
                glRotatef(45, 0.0, 1.0, 0.0);
                glScalef(0.8, 4.0, 0.8);

                Tile t;
                t.create_cube();
            }
            glPopMatrix();

            glTranslatef(0.0, -1.0, 0.0);

            Pyramide p;
            p.createPyramide();

        }
        glPopMatrix();
}

GLvoid Guerrier::tail(GLfloat angle)
{
    glRotatef(-angle, 0, 0, -1);
    glRotatef(100, 0, 0, 1);

    for (size_t i = 0; i < 5; i++)
    {
        glRotatef(15 - angle, 0, 0, 1);

        glTranslatef(0.0, -0.40, 0.0);

        glPushMatrix();
        {
            glTranslatef(0.0, 0.40, 0.0);

            glPushMatrix();
            {
                glRotatef(90, 1, 0, 0);

                Cylindre c;
                c.createCylindre(0.5, 0.45, 0.5);

                //GLUquadricObj* quadObj = gluNewQuadric();
                //gluCylinder(quadObj, 0.5, 0.45, 0.5, 6, 6);
            }
            glPopMatrix();

        }
        glPopMatrix();
    }


    for (size_t i = 0; i < 10; i++)
    {
        glRotatef(5 - angle, 0, 0, -1);
        glTranslatef(0.0, -0.40, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.0, 0.40, 0.0);

            glPushMatrix();
            {
                glRotatef(90, 1, 0, 0);

                Cylindre c;
                c.createCylindre(0.5, 0.45, 0.5);

                //GLUquadricObj* quadObj = gluNewQuadric();
                //gluCylinder(quadObj, 0.5, 0.45, 0.5, 6, 6);
            }
            glPopMatrix();

        }
        glPopMatrix();
    }

    glPushMatrix();
    {
        Sphere s;
        glScalef(0.8, 0.8, 0.8);
        s.createSphere(10, 10);
    }
    glPopMatrix();
}
