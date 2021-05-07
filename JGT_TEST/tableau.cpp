#include "tableau.h"

unsigned int nb_cases_x = 25;
unsigned int nb_cases_y = 25;

std::vector<Tile> Tableaux;
float gap = 1.1;

void create_table()
{
    for(unsigned int i = 0; i < nb_cases_x; ++i)
    {
        glTranslatef(0.0, 0.0, -gap);
        glPushMatrix();
        {
            for(unsigned int j = 0; j < nb_cases_y; ++j)
            {
                Tile c;
                c.create_cube();
                glTranslatef(-gap, 0.0, 0.0);

                Tableaux.push_back(c);
            }
        }
        glPopMatrix();
    }
}
