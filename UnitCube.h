

#include "BufferObject.h"

#pragma once

class UnitCube : public BufferObject {
private:
    const float SIDE_LENGTH = 1.0f;
    short C_ADJUST = 10;

protected:

public:
    void build(glm::vec3 color, short variation);
    void render(bool) const;

};