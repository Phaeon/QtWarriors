#include "initwindow.h"

GLuint blend = 1;
GLuint light = 1;

extern GLfloat x_rot;
extern GLfloat y_rot;
extern GLfloat z_rot;

extern GLfloat z;

void InitializeScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0f, 0.0f, z);

    glRotatef(-x_rot, 1.0f, 0.0f, 0.0f);
    glRotatef(-y_rot, 0.0f, 1.0f, 0.0f);
    glRotatef(z_rot, 0.0f, 0.0f, 1.0f);

    //(eye_x, eye_y, eye_z) : position de la caméra dans la scene
    //(center_x, center_y, center_z) : position du point que la caméra regarde
    //(up_x, up_y, up_z) : angles de rotation de la caméra sur elle-même
    //gluLookAt(20, 15, 20, -100, -50, -100, 0, 1, 0);     //eye_x = eye_z : "escalier"

}

GLvoid Reshape(GLsizei width, GLsizei height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0f, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 15, 0, 0, 0, 0, 0, 1, 0);
    glLoadIdentity();

}

int InitWindow(int argc, char** argv, void(*Modelisation)())
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(1000, 750);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Test");

    glutDisplayFunc(Modelisation);
    glutIdleFunc(Modelisation);

    glutReshapeFunc(&Reshape);
    glutSpecialFunc(&camera_key);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_COLOR_MATERIAL);
    glShadeModel(GL_SMOOTH);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glutMainLoop();

    return 1;
}
