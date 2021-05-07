#include "wizard.h"

GLvoid Wizard::displayWizard(GLfloat angle_right_meca_arm, GLfloat angle_left_meca_arm)
{
    glPushMatrix();
    {
        //glClear(GL_COLOR_BUFFER_BIT);

        //glScalef(0.5, 0.5, 0.5);

        //glColor3f(255.0, 255.0, 255.0);

    //Body - dress
        glPushMatrix();
        {
            glScalef(1.2, 1.0, 1.0);
            dress();
        }
        glPopMatrix();

    //Head
        glPushMatrix();
        {
            glTranslatef(0.0, 1.5, 0.0);
            glScalef(0.8, 0.8, 0.8);
            head();
        }
        glPopMatrix();

    //Right mechanical arm
        glPushMatrix();
        {
            glTranslatef(-0.5, 0.5, -0.4);
            glRotatef(180, 0.0, 1.0, 0.0);

            glScalef(0.75, 0.75, 0.75);
            rightMecaArm(angle_right_meca_arm);
        }
        glPopMatrix();

    //First left mechanical arm
        glPushMatrix();
        {
            glTranslatef(0.28, 0.6, -0.45);
            glRotatef(180.0, 0.0, 1.0, 0.0);

            glScalef(0.75, 0.75, 0.75);
            leftMecaArm(angle_left_meca_arm);
        }
        glPopMatrix();

    //First left mechanical arm
        glPushMatrix();
        {
            glTranslatef(0.8, 0.1, -0.2);
            glRotatef(-30, 1.0, 0.0, 0.0);
            glRotatef(-20, 0.0, 0.0, 1.0);
            glRotatef(180.0, 0.0, 1.0, 0.0);

            glScalef(0.75, 0.75, 0.75);
            leftMecaArm(angle_left_meca_arm);
        }
        glPopMatrix();

        glFlush();
    }
    glPopMatrix();
}

GLvoid Wizard::dress()
{
    glPushMatrix();
    {
        glScalef(1.0, 1.0, 1.0);
        Sphere s;
        s.createSphere(10, 10);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glRotatef(90, 1.0, 0.0, 0.0);

        Cylindre c;
        c.createCylindre(1.0, 1.0, 3.0);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glTranslatef(0.0, -3.0, 0.0);
        glRotatef(-90, 1.0, 0.0, 0.0);
        Cone c;
        c.createCone(1.1, 1.0);
    }
    glPopMatrix();
}

GLvoid Wizard::head()
{
    glPushMatrix();
    {
        glRotatef(90, 1.0, 0.0, 0.0);
        Cylindre c;
        c.createCylindre(0.25, 0.3, 1.0);
    }
    glPopMatrix();

    glTranslatef(0.0, 0.625, -1.1);

    glPushMatrix();
    {
        glScalef(1.0, 1.25, 1.5);
        glRotatef(-90, 1.0, 0.0, 0.0);
        Pyramide p;
        p.createPyramide();
    }
    glPopMatrix();
}

GLvoid Wizard::rightMecaArm(GLfloat angle_right_meca_arm)
{
    glPushMatrix();
    {
        glScalef(0.55, 0.55, 0.55);

        Sphere s;
        s.createSphere(10, 10);
    }
    glPopMatrix();

    glPushMatrix();
    {
        glRotatef(60, -1.0, 0.0, 0.0);
        glRotatef(35, 0.0, 1.0, 0.0);

        glRotatef(angle_right_meca_arm, 1.0, 0.0, 0.0);

        Cylindre c;
        c.createCylindre(0.3, 0.3, 2.5);

        glTranslatef(0.0, 0.0, 2.5);

        glPushMatrix();
        {
            glTranslatef(0.0, 0.7, 0.0);
            glScalef(0.65, 0.65, 0.65);

            Octahedron o;
            o.createOctahedron();
        }
        glPopMatrix();

        glRotatef(80, -1.0, 0.0, 0.0);

        c.createCylindre(0.3, 0.3, 2.5);

        glTranslatef(0.0, 0.0, 2.5);

        glPushMatrix();
        {
            glScalef(0.55, 0.55, 0.55);

            Sphere s;
            s.createSphere(10, 10);
        }
        glPopMatrix();
    }
    glPopMatrix();
}

GLvoid Wizard::leftMecaArm(GLfloat angle_left_meca_arm)
{
    glPushMatrix();
    {
        glScalef(0.55, 0.55, 0.55);

        Sphere s;
        s.createSphere(10, 10);
    }
    glPopMatrix();

    //glRotatef(angle_left_meca_arm, 1.0, 0.0, 0.0);

    glPushMatrix();
    {
        glRotatef(100, -1.0, 0.0, 0.0);
        glRotatef(-25, 0.0, 1.0, 0.0);
        Cylindre c;
        c.createCylindre(0.3, 0.3, 2.5);

        glTranslatef(0.0, 0.0, 2.5);

        glPushMatrix();
        {
            glScalef(0.5, 0.5, 0.5);

            Sphere s;
            s.createSphere(10, 10);
        }
        glPopMatrix();

        glRotatef(60, -1.0, 0.0, 0.0);
        glRotatef(80.0, 0.0, 0.0, 1.0);

        c.createCylindre(0.3, 0.3, 2.5);

        glTranslatef(0.0, 0.0, 2.5);

        glPushMatrix();
        {
            glScalef(0.55, 0.55, 0.55);

            Sphere s;
            s.createSphere(10, 10);
        }
        glPopMatrix();
    }
    glPopMatrix();
}
