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

#include <iostream>
#include <stdlib.h>
#include <string>
#include <math.h>




#include "camera.h"
#include "tank.h"

#include "heightfield.h"
using namespace std;
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
/// Global State Variables ///////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// time increment between calls to idle() in ms,
// currently set to 30 FPS
float dt = 1000.0f*1.0f/30.0f;

// flag to indicate that we should clean up and exit
bool quit = false;

// window handles for mother ship and scout ship
int mother_window;

// display width and height
int disp_width=800, disp_height=600;


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
/// Initialization/Setup and Teardown ////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

Camera cam;
bool wireframe = false;
HeightMap hField;
Tank tanks[5];

void init(){
    hField.Create("Data/maps/heightField.raw", 128, 128);
    string tankmodel = "Data/models/shuttle.obj";
    cam = Camera();
    for (int i = 0; i < sizeof(tanks); i++) {
        //tanks[i] = Tank("Data/models/shuttle.obj", 1);
    }
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    glViewport( 0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT) );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_NORMALIZE );
    glDepthFunc(GL_LEQUAL);
    // lighting stuff
    GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat diffuse[] = {0.9, 0.9, 0.9, 1.0};
    GLfloat specular[] = {0.4, 0.4, 0.4, 1.0};
    GLfloat position0[] = {1.0, 1.0, 1.0, 0.0};
    glLightfv( GL_LIGHT0, GL_POSITION, position0 );
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambient );
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuse );
    glLightfv( GL_LIGHT0, GL_SPECULAR, specular );
    GLfloat position1[] = {-1.0, -1.0, -1.0, 0.0};
    glLightfv( GL_LIGHT1, GL_POSITION, position1 );
    glLightfv( GL_LIGHT1, GL_AMBIENT, ambient );
    glLightfv( GL_LIGHT1, GL_DIFFUSE, diffuse );
    glLightfv( GL_LIGHT1, GL_SPECULAR, specular );
    
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    glEnable( GL_LIGHT1 );
    glEnable( GL_COLOR_MATERIAL );
    
}

// free any allocated objects and return
void cleanup(){
    /////////////////////////////////////////////////////////////
    /// TODO: Put your teardown code here! //////////////////////
    /////////////////////////////////////////////////////////////

}



//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
/// Callback Stubs ///////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

// window resize callback
void resize_callback( int width, int height ){    
    /////////////////////////////////////////////////////////////
    /// TODO: Put your resize code here! ////////////////////////
    /////////////////////////////////////////////////////////////
    cam.applyReshape(width, height);
}

void changeGLMode() {
	if (wireframe == false) {
		glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
		wireframe = true;
	} else {
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
		wireframe = false;
	}
    
}

// keyboard callback
void keyboard_callback( unsigned char key, int x, int y ){
    cam.keyboardInput(key, x, y);
    switch( key ){
        case 27:
            quit = true;
            break;
        case 9:				//TAB	(wireframe/fill)
			changeGLMode();
			break;
        default:
            break;
    }
    
    /////////////////////////////////////////////////////////////
    /// TODO: Put your keyboard code here! //////////////////////
    /////////////////////////////////////////////////////////////
    
}

// display callback
void display_callback( void ){
    int current_window;
    
    // retrieve the currently active window
    current_window = glutGetWindow();
    
    // clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 

    /////////////////////////////////////////////////////////////
    /// TODO: Put your rendering code here! /////////////////////
    /////////////////////////////////////////////////////////////
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 70.0f, float(glutGet(GLUT_WINDOW_WIDTH))/float(glutGet(GLUT_WINDOW_HEIGHT)), 0.1f, 2000.0f );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    cam.applyCameraTransform();
    
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, -100, 0);
    hField.Render();
    glPopMatrix();

    glBegin(GL_LINES);
    glColor3f( 1.0f, 0.0f, 0.0f );
    glVertex3f( 1.0f, 0.0f, 0.0f );
    glVertex3f( 0.0f, 0.0f, 0.0f );
    glColor3f( 0.0f, 1.0f, 0.0f );
    glVertex3f( 0.0f, 1.0f, 0.0f );
    glVertex3f( 0.0f, 0.0f, 0.0f );
    glColor3f( 0.0f, 0.0f, 1.0f );
    glVertex3f( 0.0f, 0.0f, 1.0f );
    glVertex3f( 0.0f, 0.0f, 0.0f );
    glEnd();

    // swap the front and back buffers to display the scene
    glutSetWindow( current_window );
    glutSwapBuffers();
}

// not exactly a callback, but sets a timer to call itself
// in an endless loop to update the program
void idle( int value ){
    
    // if the user wants to quit the program, then exit the
    // function without resetting the timer or triggering
    // a display update
    if( quit ){
        // cleanup any allocated memory
        cleanup();
        
        // perform hard exit of the program, since glutMainLoop()
        // will never return
        exit(0);
    }
    
    /////////////////////////////////////////////////////////////
    /// TODO: Put your idle code here! //////////////////////////
    /////////////////////////////////////////////////////////////

    
    // set the currently active window to the mothership and
    // request a redisplay
    glutSetWindow( mother_window );
    glutPostRedisplay();
    
    // set a timer to call this function again after the
    // required number of milliseconds
    glutTimerFunc( dt, idle, 0 );
}

void mouseMovement(int x, int y) {
    cam.mouseMovement(x, y);
}

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
/// Program Entry Point //////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
int main( int argc, char **argv ){
    // initialize glut
    glutInit( &argc, argv );
    
    // use double-buffered RGB+Alpha framebuffers with a depth buffer.
    glutInitDisplayMode( GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE );
    
    // initialize the mothership window
    glutInitWindowSize( disp_width, disp_height );
    glutInitWindowPosition( 0, 100 );
    mother_window = glutCreateWindow( "Tank Wars" );
    glutKeyboardFunc( keyboard_callback );
    glutDisplayFunc( display_callback );
    glutReshapeFunc( resize_callback );
    
    glutPassiveMotionFunc(mouseMovement); //check for mouse movement
    
    glutSetWindow( mother_window );
    init();
    
    // start the idle on a fixed timer callback
    idle( 0 );
    
    // start the blug main loop
    glutMainLoop();
    
    return 0;
}