#ifndef CAMERA_H
#define CAMERA_H
#include "vector.h"

class Camera {

private:
    Vec3 position;
    float lastx, lasty;
    float xrot, yrot, angle;

public:
    Camera(): position(0,0,0) {}
    Camera(float posx, float posy, float posz, float xRot, float yRot, float Angle);
    
    void applyCameraTransform(void);
    void applyReshape(int w, int h);
    void mouseMovement(int x, int y);
    void keyboardInput(unsigned char key, int x, int y);
};
#endif