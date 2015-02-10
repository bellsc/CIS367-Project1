#include "BufferObject.h"

#pragma once

class TruncCone : public BufferObject {
private:
    const float HEIGHT = 1.0f;
    const float BOT_RAD = 1.0f;
    short C_ADJUST = 10;
    short circ_points = 3;

protected:

public:
    void build(float topRad, short circ_points, glm::vec3 color, short variation);
    void render(bool) const;

};