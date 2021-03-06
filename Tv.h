#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

#include <vector>
#include <iostream>
#include <glm/glm.hpp>

#include "UnitCube.h"
#include "Ring.h"
#include "TruncCone.h"

#pragma once

using namespace std;

class Tv{

private:
    Ring frame;
    UnitCube screen, backing;
    TruncCone base, stem;

public:
    ~Tv();
    void build();
    void render(bool) const;

};