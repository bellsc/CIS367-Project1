#include "BufferObject.h"

class UnitCube : public BufferObject {
private:
    const float SIDE_LENGTH = 1.0f;
    int top_count, pts_count;

protected:

public:
    void build(void*);
    void render(bool) const;

};