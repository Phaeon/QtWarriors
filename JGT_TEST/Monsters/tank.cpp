#include "tank.h"

GLvoid Tank::displayTank(GLfloat angle, GLfloat angle_attaque)
{
    glPushMatrix();
    {
        //glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(255, 255, 255);

        glScalef(0.5, 0.5, 0.5);

    //Body
        glPushMatrix();
        {
            glTranslatef(0.0, 1.1, 0.0);
            body();
        }
        glPopMatrix();

    //Left arm
        glPushMatrix();
        {
            glTranslatef(10.0f, 4.0f, 0.0f);
            glRotatef(55, 0, 0, 1);
            glRotatef(180, 0, 0, 1);
            glRotatef(angle_attaque, 1, 0, 0);

            arm();
        }
        glPopMatrix();

    //Right arm
        glPushMatrix();
        {

            glTranslatef(-9.0f, 4.0f, -0.0f);
            glRotatef(-50, 0.0, 0.0, 1.0);
            glRotatef(180, 0, 0, 1);
            glRotatef(angle_attaque, 1, 0, 0);
            arm();
        }
        glPopMatrix();

    //Left leg
        glPushMatrix();
        {
            glRotatef(angle, 1, 0, 0); // Rotation lors du mouvement
            glTranslatef(4.7, -0.5, 0.0);
            leg();
        }
        glPopMatrix();

    //Right leg
        glPushMatrix();
        {
            glRotatef(angle, -1, 0, 0); // Rotation inverse lors du mouvement
            glTranslatef(-3.8f, -0.5f, 0.0f);
            leg();
        }
        glPopMatrix();

        glFlush();
    }
    glPopMatrix();
}

GLvoid Tank::body()
{
//Lower Body
    glPushMatrix();
    {
      glTranslatef(0.0f, 1.5f, 0.0f);
      glScalef(4.3f, 1.4f, 2.4f);
      glRotatef(30, 1, 1, 0);

      Decahedron d;
      d.createDecahedron();
    }
    glPopMatrix();

    glTranslatef(0.0f, 4.2f, 0.0f);

//Main body
    glPushMatrix();
    {
      glScalef(6.5f, 2.5f, 3.0f);
      glRotatef(45, 1, 1, 0);

      Decahedron d;
      d.createDecahedron();
    }
    glPopMatrix();
}

GLvoid Tank::arm()
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
           d.createDecahedron();
         }
         glPopMatrix();

         glTranslatef(0.0, 2.0, 0.0);

     //Arm
         glPushMatrix();
         {
           glScalef(1.2f, 1.2f, 1.2f);

           Decahedron d;
           d.createDecahedron();
         }
         glPopMatrix();

         glTranslatef(0.0, 3.5, 0.0);

    //Arm
         glPushMatrix();
         {
           glRotatef(10, 0, 0, 1);
           glScalef(1.5f, 2.1f, 1.5f);

           Decahedron d;
           d.createDecahedron();
         }
         glPopMatrix();
       }
       glPopMatrix();
}

GLvoid Tank::leg()
{
    glPushMatrix();
    {
        glRotatef(15, 1, 1, 0);
        glScalef(1.2, 0.4, 1.2);

        Decahedron d;
        d.createDecahedron();
    }
    glPopMatrix();

    glTranslatef(0.0, 1.2, 0.0);

    glPushMatrix();
    {
        glScalef(1.5, 0.6, 1.5);

        Decahedron d;
        d.createDecahedron();
    }
    glPopMatrix();
}
