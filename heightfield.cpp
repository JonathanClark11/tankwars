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

#include <fstream>
#include "heightfield.h"
#include "texloader.h"


#include <iostream.h>
#define     STEP_SIZE   8


bool HeightMap::Create(char *texturePath){
	ResetPlane();
    TexID = TextureLoader::LoadTexture(texturePath);
	return true;
}

bool HeightMap::Create(char *hFileName, char *texturePath){	
	FILE *fp;

    fp = fopen(hFileName, "rb");
    if (fp) {
        fread(hHeightField, 1, MAP_SIZE * MAP_SIZE, fp);
    }
    
	fclose(fp);
    TexID = TextureLoader::LoadTexture(texturePath);
	return true;
}

void HeightMap::Render(void){
    int X, Z;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, TexID);
    glBegin( GL_QUADS );                // Render Polygons

    for ( X = 0; X < (MAP_SIZE-STEP_SIZE); X += STEP_SIZE )
        for ( Z = 0; Z < (MAP_SIZE-STEP_SIZE); Z += STEP_SIZE )
        {
            glTexCoord2f((float)X / MAP_SIZE, (float)Z / MAP_SIZE);
            glVertex3i(X, getHeight(X,Z), Z);            // Send This Vertex To OpenGL To Be Rendered

            glTexCoord2f((float)X / MAP_SIZE, (float)(Z + STEP_SIZE) / MAP_SIZE) ;
            glVertex3i(X, getHeight(X,Z+STEP_SIZE), Z + STEP_SIZE);            // Send This Vertex To OpenGL To Be Rendered
            
            glTexCoord2f((float)(X + STEP_SIZE) / MAP_SIZE, (float)(Z+ STEP_SIZE) / MAP_SIZE);
            glVertex3i(X+STEP_SIZE, getHeight(X+STEP_SIZE,Z+STEP_SIZE), Z+STEP_SIZE);            // Send This Vertex To OpenGL To Be Rendered

            glTexCoord2f((float)(X + STEP_SIZE) / MAP_SIZE, (float)Z / MAP_SIZE);
            glVertex3i(X+STEP_SIZE, getHeight(X+STEP_SIZE,Z), Z);            // Send This Vertex To OpenGL To Be Rendered
        }
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

int HeightMap::getHeight(int x, int z) {
    int X = x % MAP_SIZE;                   // Error Check Our x Value
    int Z = z % MAP_SIZE;                   // Error Check Our y Value
    
    if(!hHeightField) return 0;               // Make Sure Our Data Is Valid
    int height = hHeightField[X + (Z * MAP_SIZE)];
    if (height < 0) return 0;
    //cout<<hHeightField[X + (Z * MAP_SIZE)]<<" : "<<height<<endl;
    return height;
}

void HeightMap::ResetPlane() {
    for (int i = 0; i < MAP_SIZE; i++){
        hHeightField[i] = 0;
    }
}