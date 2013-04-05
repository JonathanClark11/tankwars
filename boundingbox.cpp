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

#include "boundingbox.h"

bool BoundingBox::collision(BoundingBox b2) {
    if ( min[0] < b2.max[0] && b2.min[0] < max[0]
        && min[1] < b2.max[1] && b2.min[1] < max[1]
        && min[2] < b2.max[2] && b2.min[2] < max[2] ) {
        return true;
    }
    
    return false;
}
    
void BoundingBox::Render() {
    glPushMatrix();
	// Center the Skybox around the given x,y,z position
    glColor3f(1.0, 0.0, 0.0);
    //front
    glBegin(GL_LINE_LOOP);
    glVertex3f(min[0], min[1],    max[2]);
    glVertex3f(min[0], max[1],    max[2]);
    glVertex3f(max[0], max[1],    max[2]);
    glVertex3f(max[0], min[1],    max[2]);
    glEnd();
    
    //back
    glBegin(GL_LINE_LOOP);
    glVertex3f(min[0], min[1],    min[2]);
    glVertex3f(min[0], max[1],    min[2]);
    glVertex3f(max[0], max[1],    min[2]);
    glVertex3f(max[0], min[1],    min[2]);
    glEnd();
    
    //right
    glBegin(GL_LINE_LOOP);
    glVertex3f(min[0], min[1],    min[2]);
    glVertex3f(min[0], max[1],    min[2]);
    glVertex3f(min[0], max[1],    max[2]);
    glVertex3f(min[0], min[1],    max[2]);
    glEnd();
    
    //left
    glBegin(GL_LINE_LOOP);
    glVertex3f(max[0], min[1],    min[2]);
    glVertex3f(max[0], max[1],    min[2]);
    glVertex3f(max[0], max[1],    max[2]);
    glVertex3f(max[0], min[1],    max[2]);
    glEnd();
    glPopMatrix();
    glColor3f(1.0, 1.0, 1.0);
}