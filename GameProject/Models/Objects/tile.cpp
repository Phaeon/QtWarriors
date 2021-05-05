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

    _faces = {{0, 1, 2, 3},
              {4, 5, 6, 7},
              {0, 3, 5, 4},
              {1, 7, 6, 2},
              {0, 4, 7, 1},
              {3, 2, 6, 5}};
}

void Tile::create_cube()
{
    for(int i = 0; i < 6; i++)
    {
        //glNormal3fv(_normales_faces[i]);
        //glBindTexture(GL_TEXTURE_2D, texture[0]);
        glBegin(GL_QUADS);
            glColor3f(255.0, 255.0, 255.0);
            //glTexCoord2f(0.0f, 0.0f);
            glVertex3f(_sommets[_faces[i][0]][0], _sommets[_faces[i][0]][1], _sommets[_faces[i][0]][2]);
            //glTexCoord2f(1.0f, 0.0f);
            glVertex3f(_sommets[_faces[i][1]][0], _sommets[_faces[i][1]][1], _sommets[_faces[i][1]][2]);
            //glTexCoord2f(1.0f, 1.0f);
            glVertex3f(_sommets[_faces[i][2]][0], _sommets[_faces[i][2]][1], _sommets[_faces[i][2]][2]);
            //glTexCoord2f(0.0f, 1.0f);
            glVertex3f(_sommets[_faces[i][3]][0], _sommets[_faces[i][3]][1], _sommets[_faces[i][3]][2]);
        glEnd();
    }
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































