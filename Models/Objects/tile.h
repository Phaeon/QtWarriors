#ifndef TILE_H
#define TILE_H

#include "library.hpp"
#include <iostream>
#include <vector>
#include <assert.h>

class Tile
{
private:
    unsigned int _x, _y;
    static std::vector<std::vector<GLfloat>> _sommets, _faces, _normales;
    GLuint _cube;

public:
    Tile();
    ~Tile()=default;

    void cube(GLfloat taille);
    void create_cube(GLuint textures);
    //void initCube();

    GLuint get_Cube() { return _cube; }
    void set_cube(GLuint liste) { _cube = liste; }

};

#endif // TILE_H
