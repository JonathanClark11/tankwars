//
//  tank.cpp
//  cs314 p4
//
//  Created by Jonathan Clark on 2013-03-22.
//
//

//#include <iostream.h>

#include "tank.h"
#include "math.h"
#include "particle.h"
static const float modelYOffset = 0.3f;
static const float modelZOffset = -0.0f;
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
    //cout<<keyboard[0]<<keyboard[1]<<keyboard[2]<<keyboard[3]<<endl;
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
}

void Tank::Update() {
    if (ToDelete() == 1) return;
    //ai and movement here.
}

void Tank::Render() {
    if (ToDelete() == 1) return;
    //glColor3f(1.0, 0.0, 0.0);
    if (isPlayer == true) {
        handleKeyboard();
        //glColor3f(0.0, 0.0, 1.0);
    }
    glPushMatrix();
    
    GLfloat mat_specular[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat mat_shininess[] = { 10.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    
    glTranslatef(position[0], position[1], position[2]);
    glRotatef(rotation[1], 0, 1, 0);
    
    //drawOrientationLines();
    
    glScalef(scale, scale, scale);
    float turretOffset = 0;
    if (IsPlayer() == false) { turretOffset = 0.35f;}
    glTranslatef(0, modelYOffset + turretOffset, modelZOffset);   //do after scaling so it's always the correct height
	
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    model.displayObj();
    glDisable(GL_TEXTURE_2D);
    
    glPopMatrix();
    float bboxScale;
    if (IsPlayer() == true)
        bboxScale = 1.0;
    else
        bboxScale = 1.5;
    bbox = BoundingBox(position, bboxScale, rotation);
    bbox.Render();
    glColor3f(1.0, 1.0, 1.0);
}


void Tank::setColour(float r, float g, float b) {
	color.r = r;
	color.g = g;
	color.b = b;
}


/*
 -----------KEYBOARD INPUT-----------
 */
void Tank::initKeyboard() {
    keyboard[LEFT] = 0;
    keyboard[RIGHT] = 0;
    keyboard[UP] = 0;
    keyboard[DOWN] = 0;
    keyboard[SPACE] = 0;
}
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
    //cout<<key<<endl;
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
void Tank::setHeight(float h) {
    position[1] = h;
}
void Tank::setPlayer() {
    health = 3500;
    isPlayer = true;
}

void Tank::shoot(Vec3 direction) {
    //create a bullet with the current rotation directory.
    int sec = difftime(time(NULL), shootTimer);
    if (sec * 3 > waitShootTime) {
        Projectile *bullet = new Projectile(position, direction, this);
        bullet->setOwner(this);
        objManager->AddObject(bullet);
        time(&shootTimer);  //update shoot timer
    }
}

void Tank::CheckCollision(GameObject *obj) {
    if (ToDelete() == 1) return;
    if (bbox.collision(obj->bbox)) { //tank collided with something
        
        //if bullet vs tank, check whether it's our tank that shot it
        if (obj->owner != this) {
            //cout<<"real hit"<<endl;
            health -= PlayerStats::bulletDamage;
        }
            
            //only subtract health if not owner
            //health -= PlayerStats::bulletDamage;
        //cout<<health<<endl;
        if (health <= 0) {
            Particle *p = new Particle(position);
            objManager->AddObject(p);
            destroy();
        }
    }
}

void Tank::informAI(GameObject *user) {
    //we have the user's info, now lets aim at him!
    //cout<<"----------------------"<<endl;
    Vec3 uPos = user->getPosition();
    //cout<<"uPos:"<<uPos[0]<<","<<uPos[1]<<","<<uPos[2]<<endl;
    //cout<<"Pos:"<<position[0]<<","<<position[1]<<","<<position[2]<<endl;
    Vec3 aimVector = Vec3(uPos[0] - position[0],  uPos[1] - position[1] ,uPos[2] - position[2] );
    aimVector.normalize();
    Vec3 z = Vec3(0, 0, 1);
    
    double rotationVec = z.dot(aimVector);
    
    Vec3 newAim = Vec3(0, acos(rotationVec) * 180 / 3.14159265, 0);
    if (aimVector[0] < 0)
        newAim[1] = -newAim[1];

    //aimVector.normalize();
    //cout<<"aim:"<<newAim[0]<<","<<newAim[1]<<","<<newAim[2]<<endl;
    //cout<<"rot:"<<newAim[1]<<endl;
    
    //rotation[1] = rotationVec;
    shoot(newAim);
    //cout<<"----------------------"<<endl<<endl<<endl;
}

int Tank::getHealth() {
    return health;
}