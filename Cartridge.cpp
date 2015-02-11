#define _USE_MATH_DEFINES
#include <cmath>
#include <time.h>
#include "Cartridge.h"

using glm::vec3;

Cartridge::~Cartridge() {
    if (glIsBuffer(vertex_buffer))
        glDeleteBuffers(1, &vertex_buffer);
    if (glIsBuffer(color_buffer))
        glDeleteBuffers(1, &color_buffer);
    if (glIsBuffer(index_buffer))
        glDeleteBuffers(1, &index_buffer);
}

void Cartridge::build(short circ_pts, glm::vec3 color, short variation) {

    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &index_buffer);
    glGenBuffers(1, &color_buffer);

    circ_points = circ_pts;

    //For light and dark color variations
    srand(time(NULL));

    float angle = 0;
    float z = DEPTH / 2;

    float xradius = WIDTH / 2;
    float yradius = WIDTH / 8;


    //front quad
    all_points.push_back(vec3{-WIDTH / 2.0, -HEIGHT / 2.0, z});
    all_points.push_back(vec3{WIDTH / 2.0, -HEIGHT / 2.0, z});
    all_points.push_back(vec3{WIDTH / 2.0, HEIGHT / 2.0, z});
    all_points.push_back(vec3{-WIDTH / 2.0, HEIGHT / 2.0, z});

    for (int i = 0; i < 4; i++){
        vec3 lightColor{color.x + (rand() % variation + C_ADJUST) / 100.0, color.y + (rand() % variation + C_ADJUST) / 100.0, color.z + (rand() % variation + C_ADJUST) / 100.0};
        all_colors.push_back(lightColor);
    }

    //Upper, front rim
    angle = M_PI/(circ_points-1);
    for (int i=1; i < circ_points-1; i++){

        vec3 v1{xradius * cos(angle), HEIGHT/2 + yradius * sin(angle), z};
        all_points.push_back(v1);
        vec3 lightColor{color.x+(rand()%variation+ C_ADJUST)/100.0, color.y+(rand()%variation+ C_ADJUST)/100.0, color.z+(rand()%variation+ C_ADJUST)/100.0};
        all_colors.push_back(lightColor);
        angle += M_PI/(circ_points-1);
    }

    //center for front fan
    all_points.push_back(vec3{0, HEIGHT/2, z});
    vec3 lightColor{color.x+(rand()%variation+ C_ADJUST)/100.0, color.y+(rand()%variation+ C_ADJUST)/100.0, color.z+(rand()%variation+ C_ADJUST)/100.0};
    all_colors.push_back(lightColor);

    z = -DEPTH/2;
    //back quad
    all_points.push_back(vec3{-WIDTH / 2.0, -HEIGHT / 2.0, z});
    all_points.push_back(vec3{WIDTH / 2.0, -HEIGHT / 2.0, z});
    all_points.push_back(vec3{WIDTH / 2.0, HEIGHT / 2.0, z});
    all_points.push_back(vec3{-WIDTH / 2.0, HEIGHT / 2.0, z});

    for (int i = 0; i < 4; i++){
        vec3 darkColor{color.x-(rand()%variation+ C_ADJUST)/100.0, color.y-(rand()%variation+ C_ADJUST)/100.0, color.z-(rand()%variation+ C_ADJUST)/100.0};
        all_colors.push_back(darkColor);
    }

    // back rim
    angle = M_PI/(circ_points-1);
    for (int i=0; i < circ_points-2; i++){
        vec3 v1{xradius * cos(angle), HEIGHT/2 + yradius * sin(angle), z};
        all_points.push_back(v1);
        vec3 darkColor{color.x-(rand()%variation+ C_ADJUST)/100.0, color.y-(rand()%variation+ C_ADJUST)/100.0, color.z-(rand()%variation+ C_ADJUST)/100.0};
        all_colors.push_back(darkColor);
        angle += M_PI/(circ_points-1);
    }

    //center for back fan
    all_points.push_back(vec3{0, HEIGHT/2, z});
    vec3 darkColor{color.x-(rand()%variation+ C_ADJUST)/100.0, color.y-(rand()%variation+ C_ADJUST)/100.0, color.z-(rand()%variation+ C_ADJUST)/100.0};
    all_colors.push_back(darkColor);

    //Box for image
    all_points.push_back(vec3{-WIDTH / 4.0, -HEIGHT / 2.3, z+.1});
    all_points.push_back(vec3{WIDTH / 4.0, -HEIGHT / 2.3, z+.1});
    all_points.push_back(vec3{WIDTH / 4.0, HEIGHT / 1.75, z+.1});
    all_points.push_back(vec3{-WIDTH / 4.0, HEIGHT / 1.75, z+.1});

    for (int i = 0; i < 4; i++){
        all_colors.push_back(vec3{.2,.2,.2});
    }

    //Outside quadstrip
    all_index.push_back(0);
    all_index.push_back(3);
    all_index.push_back(circ_points+3);
    all_index.push_back(circ_points+6);
    all_index.push_back(circ_points+4);
    all_index.push_back(circ_points+5);
    all_index.push_back(1);
    all_index.push_back(2);
    all_index.push_back(0);
    all_index.push_back(3);


    //front fan
    all_index.push_back( circ_points+2);
    all_index.push_back(2);
    for(int i = 4; i <=  circ_points+1; i++){
        all_index.push_back(i);
    }
    all_index.push_back(3);
    all_index.push_back( circ_points+2);


    //back fan
    all_index.push_back(2* (circ_points+2)+1);
    all_index.push_back(circ_points+5);
    for(int i = circ_points+7; i <  2*(circ_points+2) +1; i++){
        all_index.push_back(i);
    }
    all_index.push_back(circ_points+6);
    all_index.push_back(2* (circ_points+2)+1);


    //top quadstrip
    all_index.push_back(2);
    all_index.push_back(2+circ_points+3);
    for(int i = 4; i < circ_points+2;i++){
        all_index.push_back(i);
        all_index.push_back(i+circ_points+3);
    }
    all_index.push_back(3);
    all_index.push_back(3+circ_points+3);

    //bottom quad
    all_index.push_back(0);
    all_index.push_back(circ_points+3);
    all_index.push_back(circ_points+4);
    all_index.push_back(1);


    //image box
    for(int i = 0; i< 4; i++){
        all_index.push_back(i + 2*(3+circ_points));
    }
    all_index.push_back(2*(3+circ_points));


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

void Cartridge::render(bool outline) const {
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

    //horizontal outside
    int n =  10;
    glFrontFace(GL_CCW);
    glDrawElements(GL_QUAD_STRIP, n, GL_UNSIGNED_SHORT, 0);

    //front fan
    glFrontFace(GL_CCW);
    glDrawElements(GL_TRIANGLE_FAN, circ_points+2, GL_UNSIGNED_SHORT,
            (void *) ((sizeof(GLushort) * (n))));

    //back fan
    n += circ_points+2;
    glFrontFace(GL_CW);
    glDrawElements(GL_TRIANGLE_FAN, circ_points+2, GL_UNSIGNED_SHORT,
            (void *) ((sizeof(GLushort) * (n))));

    //top quad
    n += circ_points+2;
    glFrontFace(GL_CCW);
    glDrawElements(GL_QUAD_STRIP, 2 * circ_points, GL_UNSIGNED_SHORT,
           (void *) ((sizeof(GLushort) * (n))));

    n += 2 * circ_points;
    glFrontFace(GL_CCW);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_SHORT,
            (void *) ((sizeof(GLushort) * (n))));

    n += 4;
    glFrontFace(GL_CCW);
    glLineWidth(2);
    glDrawElements(GL_LINE_LOOP, 5, GL_UNSIGNED_SHORT,
            (void *) ((sizeof(GLushort) * (n))));


    /* unbind the buffers */
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glEnableClientState(GL_COLOR_ARRAY);
}