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
//    if ( pBox1._min.x > pBox2._max.x || pBox2._min.x > pBox1._max.x
//        ||pBox1._min.y > pBox2._max.y || pBox2._min.y > pBox1._max.y
//        ||pBox1._min.z > pBox2._max.z || pBox2._min.z > pBox1._max.z )
//    {
//        return false;
//    }
//    
//    return true;
}
    
void BoundingBox::Render() {
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
    
}