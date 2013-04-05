//
//  tank.h
//  cs314 p4
//
//  Created by Jonathan Clark on 2013-03-22.
//
//

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#include <iostream>
#include <math.h>
#include <string>
#include <time.h>

#include "objreader.h"
#include "texloader.h"
#include "vector.h"
#include "boundingbox.h"
#include "projectile.h"
#include "gameobject.h"
#include "objectmanager.h"

class Tank : public GameObject {
private:
    struct Colour {
        float r, g, b;				//Colour of tank
    };
    Vec3 rotation;
    
    objReader model;
    Colour color;
    
    void draw();		//draws the tank
    void loadModel();
    float scale;        //size of tank
    
    
    //keyboard input
    enum KEYS { LEFT, RIGHT, UP, DOWN, SPACE };
    int keyboard[5];
    
    
    //tank specific traits
    int health;
    GLuint texture;
    
    time_t shootTimer;  //timer for how fast the user can shoot
    #define waitShootTime 1  //shoot wait time
    
public:
    Tank() : GameObject(500, TANK, Vec3(0, 0, 0)), rotation(0, 0, 0) { }
	Tank(char* modelFilepath, char* texturePath, float size, Vec3 pos) : GameObject(500, TANK, Vec3(pos[0],pos[1],pos[2])), rotation(0,0,0){
		model.loadObj(modelFilepath);
		model.centerObject();
		model.resizeObject(); 
        scale = size;
        
        texture = TextureLoader::LoadTexture(texturePath);
        
        health = 100;
        isPlayer = false;
        time(&shootTimer);
	}

    void CheckCollision(GameObject *obj);
    void Render();
    void Update();
    
    void drawOrientationLines();

    void setColour(float r, float g, float b);
    void setRotation(Vec3 newRotation);
    Vec3 getRotation();
    void setHeight(float h);
    void setPlayer();
    int getHealth();
    
    void initKeyboard();
    void keyboardInput(unsigned char key, int x, int y);
    void specialKeyboardInput(int key, int x, int y);
    void keyboardInputUp(unsigned char key, int x, int y);
    void specialKeyboardInputUp(int key, int x, int y);
    void handleKeyboard();
    
    //gameplay functions
    void shoot(Vec3 direction);
    void informAI(GameObject *user);//, ObjectManager *objManager);
    

};
