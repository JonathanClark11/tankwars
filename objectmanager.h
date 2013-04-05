#include "gameobject.h"
#include <set>
#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_
typedef std::set<GameObject*> GameObjectSet;

class ObjectManager {
private:
    GameObjectSet objects;
    
public:
    ObjectManager() { }
    
    void AddObject(GameObject *obj);
    void RemoveObject(GameObject *obj);
    void UpdateObjects();
    void RenderObjects();
    
    GameObject* findPlayer();
};
#endif