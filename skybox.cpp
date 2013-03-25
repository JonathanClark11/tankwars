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

#include "skybox.h"
#include "texloader.h"

#define SKYFRONT 0						// Give Front ID = 0
#define SKYBACK  1						// Give Back  ID = 1
#define SKYLEFT  2						// Give Left  ID = 2
#define SKYRIGHT 3						// Give Right ID = 3
#define SKYUP    4						// Give Up    ID = 4
#define SKYDOWN  5						// Give Down  ID = 5

bool SkyBox::Create(char *texturePath[6]){
    for (int i = 0; i < 6; i++) {
        textures[i] = TextureLoader::LoadTexture(texturePath[i]);
    }
	return true;
}

void SkyBox::Render(float x, float y, float z, float width, float height, float length) {
	// Center the Skybox around the given x,y,z position
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;
    glEnable(GL_TEXTURE_2D);
    
    //front
    glBindTexture(GL_TEXTURE_2D, textures[SKYFRONT]);
	glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y,		z+length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y+height, z+length);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z+length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z+length);
	glEnd();
    
    // Draw Up side
	glBindTexture(GL_TEXTURE_2D, textures[SKYUP]);
	glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z+length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z+length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
	glEnd();
    
	// Draw left side
    glBindTexture(GL_TEXTURE_2D, textures[SKYLEFT]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z+length);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height,	z+length);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height,	z);
    glEnd();
    
    // Draw Right side
	glBindTexture(GL_TEXTURE_2D, textures[SKYRIGHT]);
	glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y+height,	z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y+height,	z+length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y,		z+length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y,		z);
	glEnd();
    
    // Draw Back side
	glBindTexture(GL_TEXTURE_2D, textures[SKYBACK]);
	glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y+height,	z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y,		z);
	glEnd();
    
    // Draw Down side
	glBindTexture(GL_TEXTURE_2D, textures[SKYDOWN]);
	glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z+length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z);
	glEnd();
    
    glDisable(GL_TEXTURE_2D);
}