#include "gameobject.h"
#include <set>

typedef std::set<GameObject*> GameObjectSet;

class ObjectManager {
private:
    GameObjectSet objects;
    
public:
    ObjectManager() {}
    
    void AddObject(GameObject *obj);
    void UpdateObjects();
    void RenderObjects();
};