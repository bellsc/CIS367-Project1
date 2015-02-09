#include "BufferObject.h"

class UnitDisk : public BufferObject {
private:
    const float OUTER_RAD = 1.0;
    const float INNER_RAD = 0.5;
    const float THICKNESS = 1.0;
    int top_count, pts_count;

protected:

public:
    void build(void*);
    void render(bool) const;

};