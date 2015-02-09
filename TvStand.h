#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>

#include <vector>
#include <iostream>
#include <glm/glm.hpp>

#include "UnitCube.h"
#include "Ring.h"

using namespace std;

class TvStand{

private:
    Ring frame, handle;
    UnitCube divider, door;
    glm::mat4 frame_cf, handle_cf, divider_cf, door_cf;

public:
    ~TvStand();
    void build();
    void render(bool) const;

};