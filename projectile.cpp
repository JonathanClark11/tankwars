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
    glPushMatrix();
    glTranslatef(position[0], position[1], position[2]);
    glRotatef(direction[0], 1, 0, 0);
    glRotatef(direction[1], 0, 1, 0);
    glRotatef(direction[2], 0, 0, 1);

    glutSolidCube(0.5);
    glPopMatrix();
    
    //testing... should be moved to update function.
    Update();
}
    
void Projectile::Update() {
    position[2] += velocity * cos(direction[1] * 3.14159265 / 180);
    position[0] += velocity * sin(direction[1] * 3.14159265 / 180);
}