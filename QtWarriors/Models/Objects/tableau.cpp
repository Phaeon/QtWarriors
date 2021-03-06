#include "tableau.h"

unsigned int nb_cases_x = 10;
unsigned int nb_cases_y = 10;

std::vector<Tile> Tableaux;
float gap = 1.3f;

void create_table(GLuint texture)
{
    for(unsigned int i = 0; i < nb_cases_x; ++i)
    {
        glTranslatef(0.0, 0.0, -gap);
        glPushMatrix();
        {
            for(unsigned int j = 0; j < nb_cases_y; ++j)
            {
                Tile t;
                glColor3f(1.0, 1.0, 1.0);
                t.initCube(texture);
                t.displayCube();

                glTranslatef(-gap, 0.0, 0.0);

                Tableaux.push_back(t);
            }
        }
        glPopMatrix();
    }
}
