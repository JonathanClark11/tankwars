#include "objectmanager.h"

void ObjectManager::AddObject(GameObject *obj) {
    objects.insert(obj);
}

void ObjectManager::UpdateObjects() {
    GameObjectSet::const_iterator pos;
    for (pos = objects.begin(); pos != objects.end(); pos++) {
        (*pos)->Update();
    }
}

void ObjectManager::RenderObjects() {
    GameObjectSet::const_iterator pos;
    for (pos = objects.begin(); pos != objects.end(); pos++) {
        (*pos)->Render();
    }
}

