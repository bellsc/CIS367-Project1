#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

#include <vector>
#include <iostream>
#include <glm/glm.hpp>
using namespace std;

class Ring{

private:
    const float HEIGHT = 1.0f;
    const float OUTER_RAD = 1.0f;
    short circ_points = 3;

protected:
    GLuint vertex_buffer, color_buffer, index_buffer;
    std::vector <glm::vec3> all_points, all_colors;
    vector<GLushort> all_index;

public:
    ~Ring();
    void build(float innerRad, short circ_points);
    void render(bool) const;

};