#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#include "boundingbox.h"
#include "playerstats.h"
#include "vector.h"
//#include "objectmanager.h"

#include <iostream.h>
enum ObjectType { TANK, PROJECTILE, CRATE };
class GameObject {
private:
    int toDelete;
    int pointsValue;
    ObjectType type;
    
public:
    bool isPlayer;
    Vec3 position;
    BoundingBox bbox;
    GameObject(int points, ObjectType Type, Vec3 pos) : position(pos[0], pos[1], pos[2]) {
        toDelete = 0;
        pointsValue = points;
        type = Type;
    }
    virtual void Update();
    virtual void Render();
    virtual void CheckCollision(GameObject *obj);
    virtual void informAI(GameObject *user);//, ObjectManager *objManager) {};
    
    virtual void destroy();
    
    int ToDelete();
    ObjectType getType();
    
    void setPosition(Vec3 pos);
    Vec3 getPosition();
    bool IsPlayer();
};
#endif