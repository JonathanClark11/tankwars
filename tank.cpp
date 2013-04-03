//
//  tank.cpp
//  cs314 p2
//
//  Created by Jonathan Clark on 2013-03-22.
//
//

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

void Tank::Update() {
        //ai and movement here.
}


void Tank::Render() {
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
    bbox = BoundingBox(position, -1, rotation);
    bbox.Render();
    //bullets[0].Render();
}


void Tank::setColour(float r, float g, float b) {
	color.r = r;
	color.g = g;
	color.b = b;
}
void Tank::specialKeyboardInput(int key, int x, int y) {
    switch( key ){
        case GLUT_KEY_LEFT:    //left
            rotation[1] += 3;
            break;
        case GLUT_KEY_RIGHT:	//right
            rotation[1] -= 3;
			break;
        case GLUT_KEY_UP:	//up
            position[2] += 0.2 * cos(rotation[1] * 3.14159265 / 180);
            position[0] += 0.2 * sin(rotation[1] * 3.14159265 / 180);
			break;
        case GLUT_KEY_DOWN:	//down
            position[2] -= 0.2 * cos(rotation[1] * 3.14159265 / 180);
            position[0] -= 0.2 * sin(rotation[1] * 3.14159265 / 180);
			break;
        default:
            break;
    }
}
void Tank::keyboardInput(unsigned char key, int x, int y) {
    //cout<<key<<endl;
    switch (key) {
        case 32:
            shoot(rotation);
            break;
            
    }
}
void Tank::setRotation(Vec3 newRotation) {
    rotation = newRotation;
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

void Tank::killTank() {
    //TODO: PARTICLE EMISSION
    //BLOWUP TANK
    //DESTROY
}
void Tank::shoot(Vec3 direction) {
    //create a bullet with the current rotation directory.
    Projectile bullet = Projectile(position, direction);
    bullets[0] = bullet;
}