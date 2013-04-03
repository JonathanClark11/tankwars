#include "gameobject.h"

class SceneManager {
private:
    GameObject objects[100];    //maximum 100 objects in game.
    
public:
    SceneManager() {}
    
    void AddObject(GameObject obj);
    void UpdateObjects();
    void RenderObjects();
};