#ifndef _BOUNDINGBOX_H_
#define _BOUNDINGBOX_H_
#include "vector.h"
class BoundingBox {
public:
    Vec3 min;
    Vec3 max;
    Vec3 rotation;
    BoundingBox() : min(0, 0, 0), max(0, 0, 0), rotation(0, 0, 0) {}
    BoundingBox(Vec3 Min, Vec3 Max, Vec3 Rot) : min(0, 0, 0), max(0, 0, 0), rotation(0, 0, 0) {
        min = Min;
        max = Max;
        rotation = Rot;
    }
    BoundingBox(Vec3 Pos, float Size, Vec3 Rot) : min(0, 0, 0), max(0, 0, 0), rotation(0, 0, 0) {
        min = Vec3(Pos[0] - Size, Pos[1] - Size, Pos[2] - Size);
        max = Vec3(Pos[0] + Size, Pos[1] + Size, Pos[2] + Size);
        rotation = Rot;
    }
    bool collision(BoundingBox b2);
    void Render();
};
#endif