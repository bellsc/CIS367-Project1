#define _USE_MATH_DEFINES
#include <cmath>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "TvStand.h"

using glm::vec3;

TvStand::~TvStand() {

}

void TvStand::build() {
    frame.build(.8, 4, glm::vec3{.6,.3,0}, 5);
    handle.build(.8, 15, glm::vec3{.7,.3,0}, 5);
    divider.build(glm::vec3{.6,.3,0}, 5);
    door.build(glm::vec3{.6,.3,0}, 5);

    door_cf = glm::scale(glm::vec3{1.1, 1.5, .15});
}

void TvStand::render(bool outline) const {

    //Main frame
    glPushMatrix();
    glScalef(2,2.6,1);
    glRotatef(-45,0,0,1);
    frame.render(outline);
    glPopMatrix();

    //Middle bar
    glPushMatrix();
    glScalef(2.3, .3 , 1);
    glTranslatef(0,.7,0);
    divider.render(outline);
    glPopMatrix();

    //Back
    glPushMatrix();
    glTranslatef(0,-.63,-.4);
    glScalef(2.3,1.9, .2);
    glRotatef(0, 1, 0, 0);
    divider.render(outline);
    glPopMatrix();


    //Door 1
    glPushMatrix();
    glScalef(1.1, 1.6, .15);
    glTranslatef(-.52,-.45,3);
    door.render(outline);
    glPopMatrix();

    //Door 2
    glPushMatrix();
    glRotatef(90,0,1,0);
    glMultMatrixf(glm::value_ptr(door_cf));
    glTranslatef(-.75,-.46,7);
    door.render(outline);
    glPopMatrix();

    //Handle 1
    glPushMatrix();
    glTranslatef(-.22,-.7,.58);
    glScalef(.1, .3, .15);
    glRotatef(90,0,1,0);
    handle.render(outline);
    glPopMatrix();

    //Handle 2
    glPushMatrix();
    glTranslatef(1.17,-.7,1.15);
    glScalef(.1, .3, .10);
    handle.render(outline);
    glPopMatrix();
}













