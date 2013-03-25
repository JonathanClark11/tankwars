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

#include <iostream.h>
#include <fstream>
#include "heightfield.h"
#include "texloader.h"

bool HeightMap::Create(char *texturePath, const int hWidth, const int hHeight){
	hmHeight = hHeight;
	hmWidth = hWidth;
    
	ResetPlane();
    TexID = TextureLoader::LoadTexture(texturePath);
	return true;
}

bool HeightMap::Create(char *hFileName, char *texturePath, const int hWidth, const int hHeight){	
	hmHeight = hHeight;
	hmWidth = hWidth;
	FILE *fp;
    cout<<hFileName<<", "<<hWidth<<", "<<hHeight<<endl;

    fp = fopen(hFileName, "rb");
    if (fp) {
//        cout<<"File Exists"<<endl;
        fread(hHeightField, 1, hWidth * hHeight, fp);
    } else {
        cout<<"File Doesn't Exist"<<endl;
    }
    
    
	fclose(fp);
    TexID = TextureLoader::LoadTexture(texturePath);
	return true;
}

void HeightMap::Render(void){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, TexID);
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

char HeightMap::getHeight(int x, int z) {
    return hHeightField[x][z];
}

void HeightMap::ResetPlane() {
    for (int hMapX = 0; hMapX < hmWidth; hMapX++){
        for (int hMapZ = 0; hMapZ < hmHeight; hMapZ++){
            hHeightField[hMapX][hMapZ] = 0;
        }
    }
}