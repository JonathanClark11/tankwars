#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_
#include "boundingbox.h"
class GameObject {
private:
    int toDelete;
    
public:
    BoundingBox bbox;
    GameObject() { toDelete = 0; }
    virtual void Update() {};
    virtual void Render() {};
    virtual void CheckCollision(GameObject *obj) {};
    
    virtual void destroy() {
        toDelete = 1;
    };
    
    int ToDelete() { return toDelete; }
};
#endif