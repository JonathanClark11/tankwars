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

#include "objreader.h"
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
    Vec3 position;
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
public:

    
    Tank() : position(0, 0, 0), rotation(0, 0, 0) { }
	Tank(char* modelFilepath, char* texturePath, float size) : position(0, 0, 0),rotation(0,0,0){
		model.loadObj(modelFilepath);
		model.centerObject(); //center model around origin
		model.resizeObject(); //resize model, coordinates scaled to [-1,1]x[-1,1]x[-1x1]};
        scale = size;
        
        health = 100;
	}

    void CheckCollision(GameObject *obj);
    void Render();
    void Update();
    
    void drawOrientationLines();

    void setColour(float r, float g, float b);
    void setRotation(Vec3 newRotation);
    Vec3 getRotation();
    void setPosition(Vec3 newPos);
    Vec3 getPosition();
    void setHeight(float h);
    
    void keyboardInput(unsigned char key, int x, int y);
    void specialKeyboardInput(int key, int x, int y);
    void keyboardInputUp(unsigned char key, int x, int y);
    void specialKeyboardInputUp(int key, int x, int y);
    void handleKeyboard();
    
    //gameplay functions
    void shoot(Vec3 direction, ObjectManager *objManager);
};
