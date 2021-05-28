#include "decahedron.h"

std::vector<std::vector<GLfloat> > Decahedron::_sommets({});
std::vector<std::vector<GLfloat> > Decahedron::_faces({});


static const GLfloat nombre_or = ((1.0f + sqrt(5.0f)) / 2.0f);

Decahedron::Decahedron()
{
    facesDecahedron();
}

GLvoid Decahedron::facesDecahedron()
{
    _sommets =
    {
        {1.0f, 1.0f, 1.0f},   // A (0)
        {1.0f, 1.0f, -1.0f},   // B (1)
        {1.0f, -1.0f, 1.0f},   // C (2)
        {1.0f, -1.0f, -1.0f},   // D (3)
        {-1.0f, 1.0f, 1.0f},   // E (4)
        {-1.0f, 1.0f, -1.0f},   // H (5)
        {-1.0f, -1.0f, 1.0f},   // F (6)
        {-1.0f, -1.0f, -1.0f},  // G (7)
        {1.0f/((1.0f + static_cast<float>(sqrt((5.0)))) / 2.0f), nombre_or, 0.0f}, // M (8)
        {1.0f/nombre_or, -nombre_or, 0.0f}, // N (9)
        {-1.0f/nombre_or, nombre_or, 0.0f}, // O (10)
        {-1.0f/nombre_or, -nombre_or, 0.0f}, // P (11)
        {0.0f, 1.0f/nombre_or, nombre_or},  // I (12)
        {0.0f, 1.0f/nombre_or, -nombre_or}, // J (13)
        {0.0f, -1.0f/nombre_or, nombre_or}, // K (14)
        {0.0f, -1.0f/nombre_or, -nombre_or}, // L (15)
        {nombre_or, 0.0f, 1.0f/nombre_or}, // Q (16)
        {nombre_or, 0.0f, -1.0f/nombre_or}, // R (17)
        {-nombre_or, 0.0f, 1.0f/nombre_or}, // S (18)
        {-nombre_or, 0.0f, -1.0f/nombre_or} // T (19)
    };

    _faces =
    {
        {12, 14, 6, 18, 4}, // I K F S E
        {14, 2, 9, 11, 6}, // K C N P F
        {14, 12, 0, 16, 2}, // K I A Q C
        {12, 4, 10, 8, 0}, // I E O M A
        {0, 8, 1, 17, 16}, // A M B R Q
        {2, 16, 17, 3, 9}, // C Q R D N
        {6, 11, 7, 19, 18}, // F P G T S
        {18, 19, 5, 10, 4}, // S T H O E
        {8, 10, 5, 13, 1}, // M O H J B
        {1, 13, 15, 3, 17}, // B J L D R
        {9, 3, 15, 7, 11}, // N D L G P
        {19, 7, 15, 13, 5}, // T G L J H
    };
}

GLvoid Decahedron::createDecahedron(GLuint texture)
{
    glEnable(GL_TEXTURE_2D);
    for (size_t i = 0; i < 12; i++)
    {
        n nor = normale(_sommets[_faces[i][0]][0], _sommets[_faces[i][0]][1], _sommets[_faces[i][0]][2],
                _sommets[_faces[i][1]][0], _sommets[_faces[i][1]][1], _sommets[_faces[i][1]][2],
                _sommets[_faces[i][4]][0], _sommets[_faces[i][4]][1], _sommets[_faces[i][4]][2]);

        glNormal3f(nor.x, nor.y, nor.z);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_POLYGON);
        {
            glTexCoord2f(1.0f, 0.0f);       glVertex3f(_sommets[_faces[i][0]][0], _sommets[_faces[i][0]][1], _sommets[_faces[i][0]][2]);
            glTexCoord2f(0.309f, 0.951f);   glVertex3f(_sommets[_faces[i][1]][0], _sommets[_faces[i][1]][1], _sommets[_faces[i][1]][2]);
            glTexCoord2f(-0.809f, 0.588f);  glVertex3f(_sommets[_faces[i][2]][0], _sommets[_faces[i][2]][1], _sommets[_faces[i][2]][2]);
            glTexCoord2f(-0.809f, -0.588f); glVertex3f(_sommets[_faces[i][3]][0], _sommets[_faces[i][3]][1], _sommets[_faces[i][3]][2]);
            glTexCoord2f(0.309f, -0.951f);  glVertex3f(_sommets[_faces[i][4]][0], _sommets[_faces[i][4]][1], _sommets[_faces[i][4]][2]);
        }
        glEnd();
    }
    glDisable(GL_TEXTURE_2D);
}
