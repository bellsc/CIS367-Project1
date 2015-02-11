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

    /*
    //Main frame
    glPushMatrix();
    glTranslatef(0,1.8,.12);
    glScalef(2.9, 2.1, .12);
    glRotatef(45,0,0,1);
    frame.render(outline);
    glPopMatrix();
    //glMultMatrixf(glm::value_ptr(frame_cf));

    //Screen
    glPushMatrix();
    glTranslatef(0,1.8,.13);
    glScalef(3.7, 2.7, .1);
    //glRotatef(45,0,0,1);
    screen.render(outline);
    glPopMatrix();


    //Backing
    glPushMatrix();
    glTranslatef(0,1.8,0);
    glScalef(3.7, 2.7, .3);
    //glRotatef(45,0,0,1);
    backing.render(outline);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,1.6,-.2);
    glScalef(3.1, 2.3, .3);
    //glRotatef(180,1,0,0);
    backing.render(outline);
    glPopMatrix();


    //Base
    glPushMatrix();
    // glTranslatef(0,-.05,0);
    glScalef(1.3, .15, .4);
    glRotatef(-90,1,0,0);
    base.render(outline);
    glPopMatrix();

    //Stem
    glPushMatrix();
    glTranslatef(0,.22,-.15);
    glScalef(.14, .5, .14);
    glRotatef(-90,1,0,0);
    stem.render(outline);
    glPopMatrix();
*/
}













