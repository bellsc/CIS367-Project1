#define _USE_MATH_DEFINES
#include <cmath>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Tv.h"

using glm::vec3;

Tv::~Tv() {

}

void Tv::build() {
    frame.build(.9, 4, glm::vec3{.2,.2,.2}, 4);
    screen.build(glm::vec3{.1,0,.6}, 4);
    backing.build(glm::vec3{.2,.2,.2}, 2);
    base.build(.2, 15, glm::vec3{.3,.3,.3}, 2);
    stem.build(.95, 15, glm::vec3{.3,.3,.3}, 2);
}

void Tv::render(bool outline) const {

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

}













