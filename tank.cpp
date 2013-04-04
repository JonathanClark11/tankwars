//
//  tank.cpp
//  cs314 p2
//
//  Created by Jonathan Clark on 2013-03-22.
//
//

#include <iostream.h>

#include "tank.h"
#include "math.h"
static const float modelYOffset = 0.68f;
static const float modelZOffset = -0.4f;
//RENDERING
void Tank::drawOrientationLines() {
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

void Tank::handleKeyboard() {
    if (keyboard[LEFT] == 1) {
        rotation[1] += 3;
    }
    if (keyboard[RIGHT] == 1) {
        rotation[1] -= 3;
    }
    if (keyboard[UP] == 1) {
        position[2] += 0.2 * cos(rotation[1] * 3.14159265 / 180);
        position[0] += 0.2 * sin(rotation[1] * 3.14159265 / 180);
    }
    if (keyboard[DOWN] == 1) {
        position[2] -= 0.2 * cos(rotation[1] * 3.14159265 / 180);
        position[0] -= 0.2 * sin(rotation[1] * 3.14159265 / 180);
    }
    if (keyboard[SPACE] == 1) {
        //shoot(rotation, objManager);
    }
}

void Tank::Update() {
    if (ToDelete() == 1) return;
    //ai and movement here.
}

void Tank::CheckCollision(GameObject *obj) {
    if (bbox.collision(obj->bbox)) { //tank collided with something
        health -= 15;
        cout<<health<<endl;
        if (health <= 0) {
            destroy();
        }
    }
}

void Tank::Render() {
    if (ToDelete() == 1) return;
    handleKeyboard();
    glPushMatrix();
    
    GLfloat mat_specular[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat mat_shininess[] = { 10.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    
    
    glTranslatef(position[0], position[1], position[2]);
    glRotatef(rotation[1], 0, 1, 0);
    
    drawOrientationLines();
    
    glScalef(scale, scale, scale);
    glTranslatef(0, modelYOffset, modelZOffset);   //do after scaling so it's always the correct height
	model.displayObj();
    
    
    glPopMatrix();
    bbox = BoundingBox(position, 0.7, rotation);
    bbox.Render();
}


void Tank::setColour(float r, float g, float b) {
	color.r = r;
	color.g = g;
	color.b = b;
}


/*
 -----------KEYBOARD INPUT-----------
 */
void Tank::specialKeyboardInput(int key, int x, int y) {
    switch( key ){
        case GLUT_KEY_LEFT:    //left
            keyboard[LEFT] = 1;
            break;
        case GLUT_KEY_RIGHT:	//right
            keyboard[RIGHT] = 1;
			break;
        case GLUT_KEY_UP:	//up
            keyboard[UP] = 1;
			break;
        case GLUT_KEY_DOWN:	//down
            keyboard[DOWN] = 1;
			break;
        default:
            break;
    }
}
void Tank::specialKeyboardInputUp(int key, int x, int y) {
    switch( key ){
        case GLUT_KEY_LEFT:    //left
            keyboard[LEFT] = 0;
            break;
        case GLUT_KEY_RIGHT:	//right
            keyboard[RIGHT] = 0;
			break;
        case GLUT_KEY_UP:	//up
            keyboard[UP] = 0;
			break;
        case GLUT_KEY_DOWN:	//down
            keyboard[DOWN] = 0;
			break;
        default:
            break;
    }
}
void Tank::keyboardInput(unsigned char key, int x, int y) {
    switch (key) {
        case 32:
            keyboard[SPACE] = 1;
            break;
    }
}
void Tank::keyboardInputUp(unsigned char key, int x, int y) {
    switch (key) {
        case 32:
            keyboard[SPACE] = 0;
            break;
    }
}

void Tank::setRotation(Vec3 newRotation) {
    rotation = newRotation;
}
Vec3 Tank::getRotation() {
    return rotation;
}
void Tank::setPosition(Vec3 newPos) {
    position = newPos;
}
void Tank::setHeight(float h) {
    position[1] = h;
}
Vec3 Tank::getPosition() {
    return position;
}

void Tank::shoot(Vec3 direction, ObjectManager *objManager) {
    //create a bullet with the current rotation directory.
    Projectile *bullet = new Projectile(position, direction);
    objManager->AddObject(bullet);
}