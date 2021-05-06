#include "guerrier.h"

GLvoid Guerrier::displayGuerrier()
{
    //glClear(GL_COLOR_BUFFER_BIT);
    /*
    glColor3f(1.0, 1.0, 1.0);
    glCallList(1);
    glTranslatef(-1.1, 0.0, 0.0);
    glCallList(1);
    */

    glColor3f(1.0, 1.0, 1.0);

    glScalef(0.5, 0.5, 0.5);
    glRotatef(180, 0.0, 1.0, 0.0);

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
        glTranslatef(0.6, 0.7, 0.2);
        glScalef(0.4, 0.4, 0.4);
        bras();
    }
    glPopMatrix();

//Left arm
    glPushMatrix();
    {
        glTranslatef(-0.6, 0.7, 0.2);

        glRotatef(180, 0.0, 1.0, 0.0);
        glScalef(0.4, 0.4, 0.4);
        bras();
    }
    glPopMatrix();

//Right Leg
    glPushMatrix();
    {
        glTranslatef(-0.8, -2.0, 0.0);

        glRotatef(180, 0.0, 1.0, 0.0);
        glScalef(0.4, 0.4, 0.4);
        jambe();
    }
    glPopMatrix();

//Right Leg
    glPushMatrix();
    {
        glTranslatef(0.8, -2.0, 0.0);
        glScalef(0.4, 0.4, 0.4);
        jambe();
    }
    glPopMatrix();

//Tail

    glPushMatrix();
    {
        glTranslatef(0.0, -1.5, -0.7);
        glRotatef(90, 0.0, 1.0, 0.0);
        glRotatef(33, 1.0, 0.0, 0.0);
        queue(0.0);
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
            corne(0.0);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glRotatef(180, 0.0, 1.0, 0.0);
            glTranslatef(0.5, 0.5, 0.3);
            glScalef(0.6, 0.6, 0.6);
            corne(0.0);
        }
        glPopMatrix();
    }
    glPopMatrix();
}

GLvoid Guerrier::corne(GLfloat angle) // ! - Remplacer les glut ! - //
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

GLvoid Guerrier::bras()
{
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

    glTranslatef(1.5, -1.2, 0.0);
    glRotatef(90, 0.0, 0.0, 1.0);

    glPushMatrix();
    {
        glRotatef(45, 0.0, 1.0, 0.0);
        glScalef(0.8, 5.0, 0.8);
        Tile t;
        t.create_cube();
    }
    glPopMatrix();

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

    glTranslatef(0.0, -4.0, 0.0);

    glPushMatrix();
    {
        glRotatef(45, 0.0, 1.0, 0.0);
        glScalef(0.8, 5.0, 0.8);
        Tile t;
        t.create_cube();
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0.0, -1.8, 0.0);
        glScalef(0.9, 0.9, 0.9);
        Octahedron o;
        o.createOctahedron();
    }
    glPopMatrix();
}

GLvoid Guerrier::jambe()
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

            // ! - Fermer Pied - ! //

            Pyramide p;
            p.createPyramide();

        }
        glPopMatrix();
}

GLvoid Guerrier::queue(GLfloat angle) // ! - Remplacer les glut ! - //
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
        glTranslatef(0.0, -0.40, 0.0);
        glPushMatrix();
        {
            glTranslatef(0.0, 0.40, 0.0);

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
        glScalef(0.8, 0.8, 0.8);
        s.createSphere(10, 10);
    }
    glPopMatrix();
}
