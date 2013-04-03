#if defined(__APPLE_CC__)
#include<OpenGL/gl.h>
#include<OpenGL/glu.h>
#include<GLUT/glut.h>
#elif defined(WIN32)
#include<windows.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#else
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<stdint.h>
#endif

#include "projectile.h"

void Projectile::Render() {
    if (ToDelete() == 1) return;
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(position[0], position[1], position[2]);
    glRotatef(direction[0], 1, 0, 0);
    glRotatef(direction[1], 0, 1, 0);
    glRotatef(direction[2], 0, 0, 1);
    
    glutSolidCube(0.1);
    glPopMatrix();
    glColor3f(1.0, 1.0, 1.0);

    //testing... should be moved to update function.
    Update();
}
    
void Projectile::Update() {
    if (ToDelete() == 1) return;
    position[2] += velocity * cos(direction[1] * 3.14159265 / 180);
    position[0] += velocity * sin(direction[1] * 3.14159265 / 180);
    position[1] = 0.37;
}

void Projectile::CheckCollision(GameObject *obj) {
    //check if inside the map
    if (position[0] > 1024 || position[0] < 0 ||
        position[2] > 1024 || position[2] < 0 ||
        position[1] > 1024 || position[1] < 0) {
        destroy();
    }
    
    
}