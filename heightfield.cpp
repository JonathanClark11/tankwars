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
#include "jpeg.h"
#include "heightfield.h"

bool HeightMap::Create(char *hFileName, const int hWidth, const int hHeight){	
	hmHeight = hHeight;
	hmWidth = hWidth;

	FILE *fp;
	fp = fopen(hFileName, "rb");
	fread(hHeightField, 1, hWidth * hHeight, fp);
	fclose(fp);
    
    SwiftTextureJpeg(tID, "texture.jpg", 0);
	return true;
}

void HeightMap::Render(void){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tID[0]);
    for (int hMapX = 0; hMapX < hmWidth; hMapX++){
        for (int hMapZ = 0; hMapZ < hmHeight; hMapZ++){
            glBegin(GL_TRIANGLE_STRIP);
            glTexCoord2f((float)hMapX / hmWidth, (float)hMapZ / hmHeight);
            glVertex3f(hMapX, hHeightField[hMapX][hMapZ], hMapZ);
            glTexCoord2f((float)hMapX / hmWidth, (float)(hMapZ + 1) / hmHeight) ;
            glVertex3f(hMapX, hHeightField[hMapX][hMapZ + 1], hMapZ + 1);
            glTexCoord2f((float)(hMapX + 1) / hmWidth, (float)hMapZ / hmHeight);
            glVertex3f(hMapX + 1, hHeightField[hMapX + 1][hMapZ], hMapZ);
            glTexCoord2f((float)(hMapX + 1) / hmWidth, (float)(hMapZ + 1) / hmHeight);
            glVertex3f(hMapX + 1, hHeightField[hMapX + 1][hMapZ + 1], hMapZ + 1);
            glEnd();
        }
    }
    glDisable(GL_TEXTURE_2D);
}

void HeightMap::ResetPlane() {
    for (int hMapX = 0; hMapX < hmWidth; hMapX++){
        for (int hMapZ = 0; hMapZ < hmHeight; hMapZ++){
            hHeightField[hMapX][hMapZ] = 0;
        }
    }
}