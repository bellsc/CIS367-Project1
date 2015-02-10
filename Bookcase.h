#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

#include <vector>
#include <iostream>
#include <glm/glm.hpp>

#include "UnitCube.h"
#include "Ring.h"

#pragma once

using namespace std;

class Bookcase{

private:
    UnitCube base;
    Ring section;

public:
    ~Bookcase();
    void build();
    void render(bool outline, short numSections) const;

};