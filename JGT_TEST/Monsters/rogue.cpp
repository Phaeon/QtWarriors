#include "rogue.h"

GLvoid Rogue::displayRogue(GLfloat angle_pattes)
{
    glPushMatrix();
    {
        //glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(255, 255, 255);

        //glScalef(0.5, 0.5, 0.5);

    //Body
        glPushMatrix();
        {
            body();
        }
        glPopMatrix();

    //Head
        glPushMatrix();
        {
            glRotatef(33, 1.0, 0.0, 0.0);
            glTranslatef(0.0, 1.75, 0.0);

            glRotatef(90, 1.0 , 0.0, 0.0);
            head();
        }
        glPopMatrix();

    //Left front leg
        glPushMatrix();
        {
            glTranslatef(1.25, -0.3, 0.3);
            frontLeg(angle_pattes);
        }
        glPopMatrix();

    //Right front leg
        glPushMatrix();
        {
            glTranslatef(-1.25, -0.3, 0.3);
            frontLeg(angle_pattes);
        }
        glPopMatrix();

    //Right back leg
        glPushMatrix();
        {
            glTranslatef(0.65, -0.8, -3.5);
            backLeg(angle_pattes);
        }
        glPopMatrix();

    //Left back leg
        glPushMatrix();
        {
            glTranslatef(-0.65, -0.8, -3.5);
            backLeg(angle_pattes);
        }
        glPopMatrix();

        glFlush();
    }
    glPopMatrix();
}

GLvoid Rogue::body()
{

//Sphere main body
    glPushMatrix();
    {
        glScalef(1.35, 1.35, 1.35);

        Sphere s;
        s.createSphere(10, 10);
    }
    glPopMatrix();

    glTranslatef(0.0, -0.4, -2);

    //Cylindre/Scaled sphere second body
    glPushMatrix();
    {
        Sphere s;

        glRotatef(-10, 1.0, 0.0, 0.0);
        glScalef(0.6, 0.6, 2.5);
        s.createSphere(10, 10);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0.0, 1.25, 1.5);
        spine();
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0.0, 0.25, -0.75);
        spine();
    }
    glPopMatrix();
}

GLvoid Rogue::head()
{
    glPushMatrix();
    {
        Cylindre c;
        c.createCylindre(0.35, 0.35, 0.5);

        //GLUquadricObj* quadObj = gluNewQuadric();
        //gluCylinder(quadObj, 0.35, 0.35, 0.5, 10, 10);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0.0, 0.0, -0.5);

        glScalef(0.8, 1.1, 0.8);
        Sphere s;
        s.createSphere(10, 10);

    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0.0, 0.5, -1.25);
        horn();
    }
    glPopMatrix();
}

GLvoid Rogue::frontLeg(GLfloat angle_pattes)
{

    glPushMatrix();
    {
        glScalef(0.5, 0.5, 0.5);
        Sphere s;
        s.createSphere(10, 10);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glRotatef(133, 1.0, 0.0, 0.0);

        glRotatef(-angle_pattes*2, 1, 0, 0); // Rotation lors du saut

        Cylindre c;
        glPushMatrix();
        {
            c.createCylindre(0.5, 0.5, 2.0);
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
            s.createSphere(10, 10);
        }
        glPopMatrix();

        glRotatef(-90, 1.0, 0.0, 0.0);

        glRotatef(-(angle_pattes*2), 1, 0, 0); // Rotation lors du saut

        glPushMatrix();
        {
            c.createCylindre(0.5, 0.5, 2.0);
            //gluCylinder(quadObj, 0.5, 0.5, 2.0, 10, 10);
        }
        glPopMatrix();

        glTranslatef(0.0, 0.0, 2.0);

        glRotatef(-(angle_pattes*2), 1, 0, 0); // Rotation lors du saut

        //Pied
        glPushMatrix();
        {
            glRotatef(45, 1.0, 0.0, 0.0);
            glTranslatef(0.0, 0.2, 0.0);
            glScalef(0.9, 1.5, 0.8);

            Tile t;
            t.create_cube();

            glPushMatrix();
            {
                glTranslatef(0.0, 0.0, -0.45);
                glTranslatef(0.0, 0.1, 0.0);

                glRotatef(90, -1.0, 0.0, 0.0);

                glScalef(0.5, 1.0, 1.0);

                Pyramide p;
                p.createPyramide();
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPopMatrix();
}

GLvoid Rogue::backLeg(GLfloat angle_pattes)
{
    glPushMatrix();
    {
        glScalef(0.8, 0.8, 0.8);

        glPushMatrix();
        {
            glScalef(0.5, 0.5, 0.5);
            Sphere s;
            s.createSphere(10, 10);
        }
        glPopMatrix();

        glPushMatrix();
        {
            glRotatef(133, 1.0, 0.0, 0.0);

            glRotatef(-(angle_pattes*2), 1, 0, 0);

            Cylindre c;
            c.createCylindre(0.5, 0.5, 2.0);
            //GLUquadricObj* quadObj = gluNewQuadric();
            //gluCylinder(quadObj, 0.5, 0.5, 2.0, 10, 10);

            glTranslatef(0.0, 0.0, 2.0);

            glPushMatrix();
            {
                glScalef(0.5, 0.5, 0.5);
                Sphere s;
                s.createSphere(10, 10);
            }
            glPopMatrix();

            glRotatef(-90, 1.0, 0.0, 0.0);

            c.createCylindre(0.5, 0.5, 2.0);
            //gluCylinder(quadObj, 0.5, 0.5, 2.0, 10, 10);

            glTranslatef(0.0, 0.0, 2.0);

            glRotatef(-(angle_pattes*2), 1, 0, 0);

            glPushMatrix();
            {
                glRotatef(45, 1.0, 0.0, 0.0);

                glPushMatrix();
                {
                    glScalef(0.5, 0.5, 0.5);
                    Sphere s;
                    s.createSphere(10, 10);
                }
                glPopMatrix();

                c.createCylindre(0.5, 0.5, 0.5);
                //gluCylinder(quadObj, 0.5, 0.5, 0.5, 10, 10);

                glTranslatef(0.0, 0.25, 0.5);
                glScalef(0.9, 1.5, 0.8);

                Tile t;
                t.create_cube();

                glRotatef(-(angle_pattes*2), 1, 0, 0);

                //Pied
                glPushMatrix();
                {
                    glTranslatef(0.0, 0.0, -0.45);
                    glTranslatef(0.0, 0.1, 0.0);

                    glRotatef(90, -1.0, 0.0, 0.0);

                    glScalef(0.5, 1.0, 1.0);

                    Pyramide p;
                    p.createPyramide();
                }
                glPopMatrix();
            }
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPopMatrix();
}

GLvoid Rogue::spine()
{
    glScalef(0.01, 0.8, 0.8);
    Sphere s;
    s.createSphere(10, 10);
}

GLvoid Rogue::horn()
{
    glScalef(0.01, 0.5, 0.5);
    Sphere s;
    s.createSphere(10, 10);
}
