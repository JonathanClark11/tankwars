#include "gameobject.h"

void GameObject::Update() {}
void GameObject::Render() {}
void GameObject::CheckCollision(GameObject *obj) {}
void GameObject::informAI(GameObject *user) {}
    
void GameObject::destroy() {
        if (toDelete == 0) {
            PlayerStats::points += pointsValue;
        }
        toDelete = 1;
    }
    
    int GameObject::ToDelete() { return toDelete; }
    ObjectType GameObject::getType() { return type; }
    
    void GameObject::setPosition(Vec3 pos) {
        position = pos;
    }
    Vec3 GameObject::getPosition() { return position; }
    bool GameObject::IsPlayer() { return isPlayer; }