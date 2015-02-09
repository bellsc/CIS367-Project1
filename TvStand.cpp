#define _USE_MATH_DEFINES
#include <cmath>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "TvStand.h"

using glm::vec3;

TvStand::~TvStand() {

}

//glm::mat4 frame_cf, handle_cf, divider_cf, door_cf;
void TvStand::build() {
    frame.build(.8, 4);
    handle.build(.8, 15);
    divider.build();
    door.build();

    //frame_cf = glm::scale(glm::vec3{2,1,3});
    frame_cf = glm::rotate(150.0f, glm::vec3{0, 0, 1});
    //handle_cf = glm::scale(glm::vec3{.2,.6,1});
   // divider_cf = glm::scale(glm::vec3{4,2,.5});
    //door_cf = glm::scale(glm::vec3{5.5,.4,3});
}

void TvStand::render(bool outline) const {
handle.render(false);
    glPushMatrix();
   // glRotatef(-90,1,0,0);
    glScalef(2,3,1);
    glMultMatrixf(glm::value_ptr(frame_cf));
    frame.render(false);
    glPopMatrix();


    glPushMatrix();
    // glRotatef(-90,1,0,0);
    glScalef(.2,.3,.1);

    handle.render(false);

    glPopMatrix();


    ;

}
