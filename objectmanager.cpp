#include "objectmanager.h"

//#include <iostream.h>

void ObjectManager::AddObject(GameObject *obj) {
    obj->setObjectManager(this);
    objects.insert(obj);
    
}
void ObjectManager::RemoveObject(GameObject *obj) {
    obj->setObjectManager(NULL);
    objects.erase(obj);
}

void ObjectManager::UpdateObjects() {
    GameObjectSet::const_iterator pos;
    for (pos = objects.begin(); pos != objects.end(); pos++) {
        //if obj should be deleted, delete it
        if ((*pos)->ToDelete() == 1) {
            objects.erase(pos);
        }
        
        //check to update Enemy Tank AI
        if ((*pos)->getType() == TANK && (*pos)->IsPlayer() == false) {
            //let enemy tanks know where user is positioned.
            GameObject *user = findPlayer();
            (*pos)->informAI(user);
        }
        
        (*pos)->Update();
        
        GameObjectSet::const_iterator pos2;
        for (pos2 = objects.begin(); pos2 != objects.end(); pos2++) {
            if (pos2 != pos) {
                (*pos)->CheckCollision((*pos2));
            }
        }
    }
}

void ObjectManager::RenderObjects() {
    GameObjectSet::const_iterator pos;
    for (pos = objects.begin(); pos != objects.end(); pos++) {
        (*pos)->Render();
    }
}

GameObject* ObjectManager::findPlayer() {
    GameObjectSet::const_iterator pos;
    for (pos = objects.begin(); pos != objects.end(); pos++) {
        if ((*pos)->IsPlayer() == true) {
            return (*pos);
        }
    }
    return NULL;
}
int ObjectManager::countEnemies() {
    int tankCount = 0;
        GameObjectSet::const_iterator pos;
        for (pos = objects.begin(); pos != objects.end(); pos++) {
            if ((*pos)->IsPlayer() == false && (*pos)->getType() == TANK) {
                tankCount++;
            }
        }
        return tankCount;
}
