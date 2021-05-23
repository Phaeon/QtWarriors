#include "tile.h"

std::vector<std::vector<GLfloat> > Tile::_sommets({});
std::vector<std::vector<GLfloat> > Tile::_faces({});
std::vector<std::vector<GLfloat> > Tile::_normales({});

Tile::Tile()
    :_x(0), _y(0)
{
    cube(1);
}

void Tile::cube(GLfloat taille)
{
    _sommets = {{taille *  0.5f, taille *  0.5f, taille *  0.5f},
                {taille * -0.5f, taille *  0.5f, taille *  0.5f},
                {taille * -0.5f, taille * -0.5f, taille *  0.5f},
                {taille *  0.5f, taille * -0.5f, taille *  0.5f},
                {taille *  0.5f, taille *  0.5f, taille * -0.5f},
                {taille *  0.5f, taille * -0.5f, taille * -0.5f},
                {taille * -0.5f, taille * -0.5f, taille * -0.5f},
                {taille * -0.5f, taille *  0.5f, taille * -0.5f}};

    _faces = {{0, 1, 2, 3}, // Devant
              {4, 5, 6, 7}, // Derrière
              {0, 3, 5, 4}, // Droite
              {1, 7, 6, 2}, // Gauche
              {0, 4, 7, 1}, // Dessus
              {3, 2, 6, 5}}; // Dessous

    _normales = {{0, 0, 1},
                 {0, 0, -1},
                 {1, 0, 0},
                 {-1, 0, 0},
                 {0, 1, 0},
                 {0, -1, 0}};
}

void Tile::create_cube(GLuint texture)
{
    glEnable(GL_TEXTURE_2D);
    for(int i = 0; i < 6; i++)
    {
        glNormal3f(_normales[i][0], _normales[i][1], _normales[i][2]);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f);
            glVertex3f(_sommets[_faces[i][0]][0], _sommets[_faces[i][0]][1], _sommets[_faces[i][0]][2]);
            glTexCoord2f(1.0f, 0.0f);
            glVertex3f(_sommets[_faces[i][1]][0], _sommets[_faces[i][1]][1], _sommets[_faces[i][1]][2]);
            glTexCoord2f(1.0f, 1.0f);
            glVertex3f(_sommets[_faces[i][2]][0], _sommets[_faces[i][2]][1], _sommets[_faces[i][2]][2]);
            glTexCoord2f(0.0f, 1.0f);
            glVertex3f(_sommets[_faces[i][3]][0], _sommets[_faces[i][3]][1], _sommets[_faces[i][3]][2]);
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);

}

/*
void Tile::initCube()
{
    set_cube(glGenLists(1));        //_cube = glGenlist(1);
    glNewList(get_Cube(), GL_COMPILE);
    create_cube();
    glEndList();

    glShadeModel(GL_FLAT);
    glClearColor(0.0, 0.0, 0.0, 0.0);
}
*/































