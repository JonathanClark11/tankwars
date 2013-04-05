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

//#include <iostream>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <time.h>
#include <sstream>

#include "objectmanager.h"
#include "quaternion.h"
#include "tank.h"
#include "skybox.h"
#include "crate.h"
#include "particle.h"
#include "font.h"

#include "heightfield.h"
using namespace std;

float dt = 1000.0f*1.0f/30.0f;
bool quit = false;
int mother_window;
int disp_width=800, disp_height=600;

//PICKING + CAMERA
enum RENDERMODE { NORMAL, SELECT };
OpenGLCamera camera(real3(0,0,0), real3(1, 1, 1), real3(0, 1, 0), 1);
RENDERMODE rmode = NORMAL;
GLuint selectBuf[1024];
GLint hits;
int cursorX,cursorY;
static GLint display_list;

bool wireframe = false;
HeightMap hField;           //our terrain (map)
SkyBox sbox;                //skybox
Tank *tanks[5];
Tank *player;                //player's tank
bool shoot = false;
//Projectile bullets[100];     //max 100 bullets on the map.
ObjectManager *scene;         //manager for scene. all objects should be added to this (exception: player and heightmap)

GLfloat density = 0.00125; //set the density to 0.3 which is acctually quite thick
GLfloat fogColor[4] = {0.5f, 0.5f, 0.5f, 1.0f}; //set the for color to grey

Font *text[4];

//TIMER
time_t timer;
float framesPerSecond    = 0.0f;
float frameCounter = 0.0f;

bool gameOver;

/*
    Config
 */
char* heightmapFile = "Data/maps/heightmap_result.raw";
char* heightmapTexture = "Data/textures/texture.tga";
char* tankmodelFile = "Data/models/m5/m5.obj";
char* tanktextureFile = "Data/models/m5/m5.tga";
char* turretmodelFile = "Data/models/turret/turret.obj";
char* turrettextureFile = "Data/models/turret/turret.tga";

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

void SetupScene() {
    //hField.Create(heightmapFile, heightmapTexture, 256, 256);
    hField.Create(heightmapTexture);
    
    char* SkyBoxTextures[6] = {"Data/textures/skybox/front.tga", "Data/textures/skybox/back.tga", "Data/textures/skybox/left.tga", "Data/textures/skybox/right.tga", "Data/textures/skybox/up.tga", "Data/textures/skybox/down.tga" };
    sbox.Create(SkyBoxTextures);
    
    
    camera = OpenGLCamera(real3(50,10,10), real3(50, 1, 20), real3(0, 1, 0),0.5);
    
    //create enemy tanks
    for (int i = 0; i < 4; i++) {
        tanks[i] = new Tank(turretmodelFile, turrettextureFile, 2, Vec3(30+(10*i), 0, 50));
        tanks[i]->setRotation(Vec3(0, 270, 0));
        scene->AddObject(tanks[i]);
    }
    
    Crate *crates[50];
    for (int i = 0; i < 15; i++) {
        crates[i] = new Crate(Vec3(65, 1, 30+(2*i)), Vec3(0, 0, 0));
        scene->AddObject(crates[i]);
    }
    for (int i = 15; i < 30; i++) {
        crates[i] = new Crate(Vec3(25, 1, (2*i)), Vec3(0, 0, 0));
        scene->AddObject(crates[i]);
    }
    for (int i = 30; i < 50; i++) {
        crates[i] = new Crate(Vec3((2*i)-34, 1, 61), Vec3(0, 0, 0));
        scene->AddObject(crates[i]);
    }
    
    
    //player setup
    player = new Tank(tankmodelFile, tanktextureFile, 2, Vec3(50, 0, 25));
    player->setPlayer();
    player->initKeyboard();
    scene->AddObject(player);
    
    //setup hud
    text[0] = new Font("Health: ", Vec3(50, 20, 0));
    text[1] = new Font("Score: ", Vec3(650, 20, 0));
    text[2] = new Font("FPS: ", Vec3(50, 550, 0));
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
}

GLuint createDL() {
	GLuint snowManDL;
    
	// Create the id for the list
	snowManDL = glGenLists(1);
    
	glNewList(snowManDL,GL_COMPILE);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    // Draw Body
	glTranslatef(10.0f ,0.75f, 8.0f);
	glutSolidSphere(0.75f,20,20);
    
	glEndList();
    
	return(snowManDL);
}


void CalculateFPS()
{
    time_t t2;
    time(&t2);
    ++frameCounter;
    
    if( t2 - timer > 1.0f )
    {
        framesPerSecond = frameCounter;
        time(&timer);
        frameCounter = 0;
    }
}

void init(){
    scene = new ObjectManager();
    gameOver = false;
    SetupScene();
    
    glViewport( 0, 0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT) );
    glEnable(GL_CULL_FACE);
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_NORMALIZE );
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    
    
    display_list = createDL();
    
    
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

void changeRenderMode() {
	if (rmode == NORMAL) {
		rmode = SELECT;
	} else {
		rmode = NORMAL;
	}
}




void special_keyboard_callback( int key, int x, int y ){
    player->specialKeyboardInput(key, x, y);
}
void special_keyboard_up_callback( int key, int x, int y ){
    player->specialKeyboardInputUp(key, x, y);
}

// keyboard callback

void keyboard_callback( unsigned char key, int x, int y ){
    camera.CallBackKeyboardFunc(key, x, y);
    
    player->keyboardInput(key, x, y);
    
    switch( key ){
        case 27:
            quit = true;
            break;
        case 9:				//TAB	(wireframe/fill)
			changeGLMode();
			break;
        case 'p':
            changeRenderMode();
            break;
        case 32:    //space (shoot)
            shoot = true;
        default:
            break;
    }
}
void keyboard_up_callback( unsigned char key, int x, int y ){
    player->keyboardInputUp(key, x, y);
    if (key == 32) {
        shoot = false;
    }
}

void mouseMovement(int x, int y) {
    camera.CallBackMotionFunc(x, y);
}

void mouseFunc(int button, int state, int x, int y) {
    camera.CallBackMouseFunc(button, state, x, y);
    
    //pick
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        cursorX = x;
        cursorY = y;
        rmode = SELECT;
    }
}

//PICKING

void startPicking() {
	GLint viewport[4];
	float ratio;
	glSelectBuffer(1024,selectBuf);
	glGetIntegerv(GL_VIEWPORT,viewport);
	glRenderMode(GL_SELECT);
	glInitNames();
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
    
	gluPickMatrix(cursorX,viewport[3]-cursorY,5,5,viewport);
	ratio = (viewport[2]+0.0) / viewport[3];
	gluPerspective(45,ratio,0.1,1000);
	glMatrixMode(GL_MODELVIEW);
}
void processHits2 (GLint hits, GLuint buffer[], int sw)
{
    GLint i, j, numberOfNames;
    GLuint names, *ptr, minZ,*ptrNames;
    
    ptr = (GLuint *) buffer;
    minZ = 0xffffffff;
    for (i = 0; i < hits; i++) {
        names = *ptr;
        ptr++;
        if (*ptr < minZ) {
            numberOfNames = names;
            minZ = *ptr;
            ptrNames = ptr+2;
        }
        
        ptr += names+2;
	}
    if (numberOfNames > 0) {
        printf ("You picked object  ");
        ptr = ptrNames;
        for (j = 0; j < numberOfNames; j++,ptr++) {
            printf ("%d ", *ptr);
        }
	}
    else
        printf("You didn't click a pickable object!");
    printf ("\n");
    
}
void stopPicking() {
    
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();
	hits = glRenderMode(GL_RENDER);
	if (hits != 0){
		processHits2(hits,selectBuf,0);
	}
	rmode = NORMAL;
}

void drawGameOver(){
    //render HUD
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    text[3]->Render();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glutSwapBuffers();
}
void drawHUD() {
    //Update Health
    int hp = player->getHealth();
    stringstream ss;
    ss<<"Health: "<<hp;
    string str = ss.str();
    text[0]->setText(str.c_str());
    
    //Update Score
    int score = PlayerStats::points;
    ss.str("");
    ss<<"Score: "<<score;
    str = ss.str();
    text[1]->setText(str.c_str());
    
    //Update FPS
    ss.str("");
    ss<<"FPS: "<<framesPerSecond;
    str = ss.str();
    text[2]->setText(str.c_str());
    
    //render HUD
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    for (int i = 0; i < 3; i++) {
        text[i]->Render();
    }
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

// display callback
void display_callback( void ){
    
    if (gameOver == true){
        drawGameOver();
    }
    
    CalculateFPS();
    if (shoot == true) {
        player->shoot(player->getRotation());
    }
    int current_window;
    
    // retrieve the currently active window
    current_window = glutGetWindow();
    
    // clear the color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if (rmode == SELECT) {
		startPicking();
	}
    
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
    
    scene->RenderObjects();
    
    //player->setHeight(hField.getHeight(player.getPosition()[0], player.getPosition()[2]));
    player->Render();
    
    glPopMatrix();
    
    // swap the front and back buffers to display the scene
    glutSetWindow( current_window );
    //PICKING
    
//    for(int i = 0; i < 2; i++) {
//		for(int j = 0; j < 2; j++) {
//			glPushMatrix();
//			glPushName(i*2+j);
//			glTranslatef(i*3.0,0,-j * 3.0);
//			glCallList(display_list);
//			glPopName();
//			glPopMatrix();
//		}
//    }
    
    //draw HUD
    
    drawHUD();
    
    if (rmode == SELECT) {
		stopPicking();
    }
	else {
        if (gameOver == false)
            glutSwapBuffers();
    }
}
void lose(){
    gameOver = true;
    text[3] = new Font("You Lose! Press Escape to Quit", Vec3(325, 300, 0));
}
void win() {
    gameOver = true;
    text[3] = new Font("You Win! Press Escape to Quit", Vec3(325, 300, 0));
}

void idle( int value ){
    if (player->getHealth() <= 0) {
        lose();
    }
    if (scene->countEnemies() <= 0) {
        win();
    }
    if( quit ){
        cleanup();
        exit(0);
    } 

    if (gameOver == false)
        scene->UpdateObjects();

    glutSetWindow( mother_window );
    glutPostRedisplay();

    glutTimerFunc( dt, idle, 0 );
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
    
    //glutIgnoreKeyRepeat(true);
    glutKeyboardFunc( keyboard_callback );
    glutKeyboardUpFunc( keyboard_up_callback );
    glutSpecialFunc(special_keyboard_callback);
    glutSpecialUpFunc(special_keyboard_up_callback);
    
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