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

#include "camera.h"
Camera::Camera(float posx, float posy, float posz, float xRot, float yRot, float Angle): position(posx, posy, posz) {
    xrot = xRot;
    yrot = yRot;
    angle = Angle;
}

void Camera::applyCameraTransform() {
    glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on teh x-axis (left and right)
    glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
    glTranslated(-position[0],-position[1],-position[2]); //translate the screen to the position of our camera
}

void Camera::applyReshape(int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
    glMatrixMode (GL_PROJECTION); //set the matrix to projection
    
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0
                    ); //set the perspective (angle of sight, width, height, , depth)
    glMatrixMode (GL_MODELVIEW); //set the matrix back to model
}

void Camera::mouseMovement(int x, int y) {
    int diffx=x-lastx; //check the difference between the current x and the last x position
    int diffy=y-lasty; //check the difference between the current y and the last y position
    lastx=x; //set lastx to the current x position
    lasty=y; //set lasty to the current y position
    xrot += (float) diffy; //set the xrot to xrot with the addition of the difference in the y position
    yrot += (float) diffx;    //set the xrot to yrot with the addition of the difference in the x position
}

void Camera::keyboardInput(unsigned char key, int x, int y) {
    if (key=='q')
    {
        xrot += 1;
        if (xrot >360) xrot -= 360;
    }
    
    if (key=='z')
    {
        xrot -= 1;
        if (xrot < -360) xrot += 360;
    }
    
    if (key=='w')
    {
        float xrotrad, yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        xrotrad = (xrot / 180 * 3.141592654f);
        position[0] += float(sin(yrotrad)) ;
        position[2] -= float(cos(yrotrad)) ;
        position[1] -= float(sin(xrotrad)) ;
    }
    
    if (key=='s')
    {
        float xrotrad, yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        xrotrad = (xrot / 180 * 3.141592654f);
        position[0] -= float(sin(yrotrad));
        position[2] += float(cos(yrotrad)) ;
        position[1] += float(sin(xrotrad));
    }
    
    if (key=='d')
    {
        float yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        position[0] += float(cos(yrotrad)) * 0.2;
        position[2] += float(sin(yrotrad)) * 0.2;
    }
    
    if (key=='a')
    {
        float yrotrad;
        yrotrad = (yrot / 180 * 3.141592654f);
        position[0] -= float(cos(yrotrad)) * 0.2;
        position[2] -= float(sin(yrotrad)) * 0.2;
    }
}