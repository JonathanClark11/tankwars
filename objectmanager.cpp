#include "objectmanager.h"
//#include <iostream.h>

void ObjectManager::AddObject(GameObject *obj) {
    objects.insert(obj);
}
void ObjectManager::RemoveObject(GameObject *obj) {
    objects.erase(obj);
}

void ObjectManager::UpdateObjects() {
    GameObjectSet::const_iterator pos;
    for (pos = objects.begin(); pos != objects.end(); pos++) {
        //if obj should be deleted, delete it
        if ((*pos)->ToDelete() == 1) {
            objects.erase(pos);
        }
        //cout<<objects.size()<<endl;
        //update object position/movement blah blah
        (*pos)->Update();
        
        
        GameObjectSet::const_iterator pos2;
        for (pos2 = objects.begin(); pos2 != objects.end(); pos2++) {
            if (pos2 != pos) {
                //check for collision
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

