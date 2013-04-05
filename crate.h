#ifndef _CRATE_H_
#define _CRATE_H_

#include "vector.h"
#include "gameobject.h"
#include "texloader.h"

#define texPath "Data/textures/crate.tga"

class Crate : public GameObject {
private:
    Vec3 rotation;
    GLuint texture;
public:
    Crate() : GameObject(0, CRATE, Vec3(0,0,0)), rotation(0, 0, 0) {
        texture = TextureLoader::LoadTexture(texPath);
    };
    Crate(Vec3 pos, Vec3 rot) : GameObject(0, CRATE, Vec3(pos[0], pos[1], pos[2])), rotation(rot[0], rot[1], rot[2]) {
        texture = TextureLoader::LoadTexture(texPath);
    };
    void Render();
    void Update();
    void CheckCollision(GameObject *obj);
};
#endif