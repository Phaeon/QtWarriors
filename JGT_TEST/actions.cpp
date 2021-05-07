#include "actions.h"

extern GLfloat x_rot;
extern GLfloat y_rot;
extern GLfloat z;

void camera_key(int key, int x, int y)
{
    switch(key)
        {
            case GLUT_KEY_PAGE_UP:
                z++;
                break;
            case GLUT_KEY_PAGE_DOWN:
                z--;
                break;
            case GLUT_KEY_UP:
                x_rot += 10;
                break;
            case GLUT_KEY_DOWN:
                x_rot -= 10;
                break;
            case GLUT_KEY_LEFT:
                y_rot -= 10;
                break;
            case GLUT_KEY_RIGHT:
                y_rot += 10;
                break;

        }
}
