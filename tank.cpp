//
//  tank.cpp
//  cs314 p2
//
//  Created by Jonathan Clark on 2013-03-22.
//
//

#include "tank.h"
static const float modelYOffset = 0.68f;
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

void Tank::drawTank() {
    glPushMatrix();
    
    GLfloat mat_specular[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat mat_shininess[] = { 10.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    
    glTranslatef(position[0], position[1], position[2]);
    drawOrientationLines();
    glTranslatef(0, modelYOffset, 0);
	model.displayObj();
    glPopMatrix();
}
void Tank::setColour(float r, float g, float b) {
	color.r = r;
	color.g = g;
	color.b = b;
}

void Tank::setPosition(Vec3 newPos) {
    position = newPos;
}
Vec3 Tank::getPosition() {
    return position;
}