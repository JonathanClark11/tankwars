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

#include "objectmanager.h"
#include "quaternion.h"
#include "tank.h"
#include "skybox.h"

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

OpenGLCamera camera(real3(0,0,0), real3(1, 1, 1), real3(0, 1, 0), 1);

bool wireframe = false;
HeightMap hField;           //our terrain (map)
SkyBox sbox;                //skybox
Tank *tanks[5];
Tank player;                //player's tank
//Projectile bullets[100];     //max 100 bullets on the map.
ObjectManager scene;         //manager for scene. all objects should be added to this (exception: player and heightmap)

GLfloat density = 0.00125; //set the density to 0.3 which is acctually quite thick
GLfloat fogColor[4] = {0.5f, 0.5f, 0.5f, 1.0f}; //set the for color to grey


/*
    Config
 */
char* heightmapFile = "Data/maps/heightmap_result.raw";
char* heightmapTexture = "Data/textures/texture.tga";
char* tankmodelFile = "Data/models/tank.obj";
char* tanktextureFile = "Data/textures/camo.tga";

void setup_lights() {
    // lighting stuff
    GLfloat ambient[] = {0.5, 0.5, 0.5, 0.5};
    GLfloat diffuse[] = {0.2, 0.2, 0.2, 1.0};
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
    glEnable( GL_LIGHT2 );
    
}


void init(){
    scene = ObjectManager();
    //hField.Create(heightmapFile, heightmapTexture, 256, 256);
    hField.Create(heightmapTexture);
    
    char* SkyBoxTextures[6] = {"Data/textures/skybox/front.tga", "Data/textures/skybox/back.tga", "Data/textures/skybox/left.tga", "Data/textures/skybox/right.tga", "Data/textures/skybox/up.tga", "Data/textures/skybox/down.tga" };
    sbox.Create(SkyBoxTextures);
    
    
    camera = OpenGLCamera(real3(10,hField.getHeight(10, 3) + 2,-5), real3(2, 1, 2), real3(0, 1, 0),0.5);
    
    //enemy tank 1
    tanks[0] = new Tank(tankmodelFile, tanktextureFile, 2);
    tanks[0]->setPosition(Vec3(10, hField.getHeight(10, 3), 10));
    tanks[0]->setRotation(Vec3(0, 180, 0));
    scene.AddObject(tanks[0]);

    
    
    //player setup
    player = Tank(tankmodelFile, tanktextureFile, 2);
    player.setPosition(Vec3(10, hField.getHeight(10, 3), 4));
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    glViewport( 0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT) );
    glEnable(GL_CULL_FACE);
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_NORMALIZE );
    glDepthFunc(GL_LEQUAL);

    
    
    //---------LOAD TEXTURES --------------
    
    
    
    glEnable (GL_FOG); //enable the fog
    glFogi (GL_FOG_MODE, GL_EXP2); //set the fog mode to GL_EXP2
    glFogfv (GL_FOG_COLOR, fogColor); //set the fog color toour color chosen above
    glFogf (GL_FOG_DENSITY, density); //set the density to the value above
    glHint (GL_FOG_HINT, GL_NICEST); // set the fog to look the nicest, may slow down on older cards
    
    
    setup_lights();
    
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




void special_keyboard_callback( int key, int x, int y ){
    player.specialKeyboardInput(key, x, y);
}
// keyboard callback

void keyboard_callback( unsigned char key, int x, int y ){
    camera.CallBackKeyboardFunc(key, x, y);
    
    player.keyboardInput(key, x, y);
    
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

void drawOrientationLines() {
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
    glColor3f(1.0, 1.0, 1.0);
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
    
    camera.Update(hField.getHeight(camera.camera_pos.x, camera.camera_pos.z));
    
    
    glPushMatrix();
    
    glColor3f(1.0, 1.0, 1.0);
    
    hField.Render();
    
    sbox.Render(camera.camera_pos.x,camera.camera_pos.y,camera.camera_pos.z,1024,1024,1024);
    
    scene.RenderObjects();
    
    player.setHeight(hField.getHeight(player.getPosition()[0], player.getPosition()[2]));
    player.Render();
    
    glPopMatrix();
    drawOrientationLines();
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
    scene.UpdateObjects();
    
    // set the currently active window to the mothership and
    // request a redisplay
    glutSetWindow( mother_window );
    glutPostRedisplay();
    
    // set a timer to call this function again after the
    // required number of milliseconds
    glutTimerFunc( dt, idle, 0 );
}

void mouseMovement(int x, int y) {
    camera.CallBackMotionFunc(x, y);
}

void mouseFunc(int button, int state, int x, int y) {
    camera.CallBackMouseFunc(button, state, x, y);
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

    glutDisplayFunc( display_callback );
    glutReshapeFunc( resize_callback );
    
    
    glutKeyboardFunc( keyboard_callback );
    glutSpecialFunc(special_keyboard_callback);
    
    glutPassiveMotionFunc(mouseMovement); //check for mouse movement
    glutMouseFunc(mouseFunc);
    
    glutSetWindow( mother_window );
    init();
    
    // start the idle on a fixed timer callback
    idle( 0 );
    
    // start the blug main loop
    glutMainLoop();
    
    return 0;
}