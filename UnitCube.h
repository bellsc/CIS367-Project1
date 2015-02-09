#include "BufferObject.h"

class UnitCube : public BufferObject {
private:
    const float SIDE_LENGTH = 1.0f;

protected:

public:
    void build();
    void render(bool) const;

};