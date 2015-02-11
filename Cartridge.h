#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

#include <vector>
#include <iostream>
#include <glm/glm.hpp>

#pragma once
using namespace std;

class Cartridge{

private:
    const float HEIGHT = .75f * .45f;
    const float WIDTH = 1.3f * .45f;
    const float DEPTH = .2f * .5f;
    const short C_ADJUST = 10;
    short circ_points = 7;

protected:
    GLuint vertex_buffer, color_buffer, index_buffer;
    std::vector <glm::vec3> all_points, all_colors;
    vector<GLushort> all_index;

public:
    ~Cartridge();
    void build(short circ_points, glm::vec3 color, short variation);
    void render(bool) const;

};