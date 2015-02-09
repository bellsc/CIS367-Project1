#include "BufferObject.h"

class TruncCone : public BufferObject {
private:
    const float HEIGHT = 1.0f;
    const float BOT_RAD = 1.0f;
    short circ_points = 3;

protected:

public:
    void build(float topRad, short circ_points);
    void render(bool) const;

};