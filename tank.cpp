//
//  tank.cpp
//  cs314 p2
//
//  Created by Jonathan Clark on 2013-03-22.
//
//

#include "tank.h"

//RENDERING
void Tank::drawTank() {
	model.displayObj();
}
void Tank::setColour(float r, float g, float b) {
	color.r = r;
	color.g = g;
	color.b = b;
}

void Tank::setPosition(Vec3 newPos) {
    position = newPos;
}