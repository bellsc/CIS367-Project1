#define _USE_MATH_DEFINES
#include <cmath>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Bookcase.h"

using glm::vec3;

Bookcase::~Bookcase() {

}

//glm::mat4 frame_cf, handle_cf, divider_cf, door_cf;
void Bookcase::build() {
    base.build(glm::vec3{.25,.25,.25}, 3);
    section.build(.9, 4, glm::vec3{.2,.2,.2}, 3);
}

void Bookcase::render(bool outline, short numSections) const {

    //base

    glPushMatrix();
    glTranslatef(0,-.59,0);
    glScalef(1,.2, 1);
    base.render(outline);
    glPopMatrix();


    for(float i=0;i<numSections;i++){
        glPushMatrix();
        glTranslatef(0,i-i*.02, 0);
        glScalef(.7,.7,1);
        glRotatef(45,0,0,1);
        section.render(outline);
        glPopMatrix();
    }
    /*
    //Handle 1
    glPushMatrix();
    glTranslatef(-.22,-.7,.58);
    glScalef(.1, .3, .15);
    glRotatef(90,0,1,0);

    handle.render(false);

    glPopMatrix();

    //Handle 2
    glPushMatrix();

    glTranslatef(1.17,-.7,1.15);
    glScalef(.1, .3, .10);
    handle.render(false);
    glPopMatrix();
    */
}













