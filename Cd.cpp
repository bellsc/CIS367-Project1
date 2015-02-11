#define _USE_MATH_DEFINES
#include <cmath>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Cd.h"

using glm::vec3;

Cd::~Cd() {

}

void Cd::build(glm::vec3 color, short variation) {

    inner.build(.5, 15, glm::vec3{.8,.8,.8}, 2);
    outerTop.build(IN_RAD, 25, color, variation);
    outerBottom.build(IN_RAD, 25, glm::vec3{.5,.5,.5}, 15);
}

void Cd::render(bool outline) const {

    //Inner ring
    glPushMatrix();
    glScalef(SCALE/5, SCALE/5, HEIGHT);
    inner.render(outline);
    glPopMatrix();

    //Outer, top ring
    glPushMatrix();
    glTranslatef(0,0,HEIGHT/2);
    glScalef(SCALE,SCALE, HEIGHT);
    outerTop.render(outline);
    glPopMatrix();

    //Outer, bottom ring
    glPushMatrix();
    glTranslatef(0,0,-HEIGHT/2);
    glScalef(SCALE,SCALE, HEIGHT);
    outerBottom.render(outline);
    glPopMatrix();

}













