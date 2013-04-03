#include "vector.h"
class Projectile {
private:
    Vec3 position;
    Vec3 direction;
    float velocity;

public:
    Projectile() : position(0, 0, 0), direction(0, 0, 0) {}
    Projectile(Vec3 Pos, Vec3 Dir) : position(0, 0, 0), direction(0, 0, 0) {
        position = Pos;
        direction = Dir;
        velocity = 1.0f;
    }
    
    void Update();
    void Render();
};