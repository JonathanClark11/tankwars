#include "vector.h"
#include "gameobject.h"
class Projectile : public GameObject {
private:
    Vec3 direction;
    float velocity;
    GameObject *creator;
public:
    Projectile() : GameObject(0, PROJECTILE, Vec3(0,0,0)), direction(0, 0, 0) {}
    Projectile(Vec3 Pos, Vec3 Dir, GameObject *Creator) : GameObject(0, PROJECTILE, Vec3(Pos[0],Pos[1],Pos[2])), direction(0, 0, 0) {
        direction = Dir;
        velocity = 0.7f;
        creator = Creator;
    }
    
    void CheckCollision(GameObject *obj);
    void Render();
    void Update();
};