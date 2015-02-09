#define _USE_MATH_DEFINES
#include <cmath>
#include "UnitCube.h"

using glm::vec3;
void UnitCube::build(void* data) {

    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
    glGenBuffers(1, &color_buffer);

    //origin is in bottom corner
    float z = 0;

    //Make bottom first
    for (int x = 0; x < 2; x++) {
        vec3 v1{x, x, z};
        vec3 v2{x, 1 - x, z};
        all_index.push_back(all_points.size());
        all_points.push_back(v1);
        all_index.push_back(all_points.size());
        all_points.push_back(v2);

        all_colors.push_back(vec3 {0,0,1});
        all_colors.push_back(vec3 {0,0,1});
    }

    /* repeat the first two vertices to complete the quad */
    pts_count = all_index.size();
   // all_index.push_back(0);
   // all_index.push_back(1);
   // top_count = all_index.size();

    //top
    z = SIDE_LENGTH;
    for (int x = 0; x < 2; x++) {
        vec3 v1{x, x, z};
        vec3 v2{x, 1 - x, z};
        all_index.push_back(all_points.size());
        all_points.push_back(v1);
        all_index.push_back(all_points.size());
        all_points.push_back(v2);
        all_colors.push_back(vec3 {1,0,0});
        all_colors.push_back(vec3 {1,0,0});
    }


    //Sides
    /*
    for( int k = 0; k < 3; k++){
        all_index.push_back(k + 1);
        all_index.push_back(k + 1 + pts_count);
        all_index.push_back(k);
        all_index.push_back(k + pts_count);
    }
    */
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

   // glEnable(GL_LIGHTING);
   // glEnable(GL_LIGHT0);


    glPolygonMode (GL_FRONT, GL_FILL);
    glPolygonMode (GL_BACK, GL_LINE);
    glFrontFace(GL_CCW);
    //glColor3ub (255, 0, 0);
    glDrawRangeElements(GL_QUADS, 0,0, 4, GL_UNSIGNED_SHORT, 0);

    glFrontFace(GL_CW);
    //glColor3ub (0, 255, 0);
    glDrawRangeElements(GL_QUADS, 0, 0, 4, GL_UNSIGNED_SHORT,
            (void *) (sizeof(GLushort) * (4)));
    glFrontFace(GL_CCW);

    //glColor3ub (120, 160, 0);
    glDrawRangeElements(GL_QUAD_STRIP, 0, 0, 10, GL_UNSIGNED_SHORT,
            (void *) (sizeof(GLushort) * (8)));

   /* unbind the buffers */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glEnableClientState(GL_COLOR_ARRAY);

}