#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

#include <vector>
#include <iostream>
#include <glm/glm.hpp>

#include "Ring.h"

#pragma once

using namespace std;

class Cd{

private:
    const float HEIGHT = 0.02;
    const float SCALE = .35;
    const float IN_RAD = 0.2;
    Ring inner, outerTop, outerBottom;


public:
    ~Cd();
    void build(glm::vec3 color, short variation);
    void render(bool) const;

};