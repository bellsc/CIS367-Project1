#define _USE_MATH_DEFINES
#include <cmath>
#include <time.h>
#include "UnitCube.h"

using glm::vec3;
UnitCube::~UnitCube() {
    if (glIsBuffer(vertex_buffer))
        glDeleteBuffers(1, &vertex_buffer);
    if (glIsBuffer(color_buffer))
        glDeleteBuffers(1, &color_buffer);
    if (glIsBuffer(index_buffer))
        glDeleteBuffers(1, &index_buffer);
}

void UnitCube::build(glm::vec3 color, short variation) {

    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
    glGenBuffers(1, &color_buffer);

    //Set up light and dark color variations
    srand (time(NULL));


    float x, y, z;
    x = y = z = SIDE_LENGTH / 2;

    //bottom
    all_points.push_back(vec3 {-x, -y, -z});
    all_points.push_back(vec3 {x, -y, -z});
    all_points.push_back(vec3 {x, y, -z});
    all_points.push_back(vec3 {-x, y, -z});

    for (int i = 0; i < 4; i++) {
        all_index.push_back(i);
        vec3 darkColor{color.x-(rand()%variation+ C_ADJUST)/100.0, color.y-(rand()%variation+ C_ADJUST)/100.0, color.z-(rand()%variation+ C_ADJUST)/100.0};
        all_colors.push_back(darkColor);
    }

    //top
    all_points.push_back(vec3 {-x, -y, z});
    all_points.push_back(vec3 {x, -y, z});
    all_points.push_back(vec3 {x, y, z});
    all_points.push_back(vec3 {-x, y, z});

    for (int i = 0; i < 4; i++) {
        all_index.push_back(i+4);
        vec3 normColor{color.x-variation/200.0+(rand()%variation)/100.0,
                color.y-variation/200.0-(rand()%variation)/100.0,
                color.z-variation/200.0-(rand()%variation)/100.0};
        all_colors.push_back(normColor);
    }

    //Sides
    all_index.push_back(7);
    all_index.push_back(3);
    all_index.push_back(6);
    all_index.push_back(2);
    all_index.push_back(5);
    all_index.push_back(1);
    all_index.push_back(4);
    all_index.push_back(0);
    all_index.push_back(7);
    all_index.push_back(3);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, all_points.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);
    float *vertex_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    /* Initialize the vertices */
    float *ptr = vertex_ptr;
    for (auto v : all_points) {
        ptr[0] = v.x;
        ptr[1] = v.y;
        ptr[2] = v.z;
        ptr += 3;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //colors
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glBufferData(GL_ARRAY_BUFFER, all_colors.size() * sizeof(float) * 3, NULL, GL_DYNAMIC_DRAW);
    float *color_ptr = (float *) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    /* Initialize the vertices */
    float *cptr = color_ptr;
    for (auto v : all_colors) {
        cptr[0] = v.x;
        cptr[1] = v.y;
        cptr[2] = v.z;
        cptr += 3;
    }
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /* Initialize the indices */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, all_index.size() * sizeof(GLushort), all_index.data(), GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void UnitCube::render(bool outline) const {
    /* bind vertex buffer */

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);
    glEnableClientState(GL_COLOR_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, color_buffer);
    glColorPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

    /* render the polygon */
    if(outline)
        glPolygonMode(GL_FRONT, GL_LINE);
    else
        glPolygonMode (GL_FRONT, GL_FILL);
    glPolygonMode (GL_BACK, GL_LINE);
    glFrontFace(GL_CW);
    glDrawRangeElements(GL_QUADS, 0,0, 4, GL_UNSIGNED_SHORT, 0);

    glFrontFace(GL_CCW);
    glDrawRangeElements(GL_QUADS, 0, 0, 4, GL_UNSIGNED_SHORT,
            (void *) (sizeof(GLushort) * (4)));
    glFrontFace(GL_CW);

    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 10, GL_UNSIGNED_SHORT,
            (void *) (sizeof(GLushort) * (8)));

   /* unbind the buffers */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glEnableClientState(GL_COLOR_ARRAY);

}