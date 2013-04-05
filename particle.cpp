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

#include <stdio.h>
#include <math.h>

#include <iostream>
#include "particle.h"

void Particle::createParticles() {
    int i;
    for (i = 1; i < ParticleCount; i++)
    {
        Particles[i].Xpos = 0;
        Particles[i].Ypos = -5;
        Particles[i].Zpos = -5;
        Particles[i].Xmov = (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) *
                              rand()%11) + 1) * 0.005) - (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1
                                                             ) * rand()%11) + 1) * 0.005);
        Particles[i].Zmov = (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1) *
                              rand()%11) + 1) * 0.005) - (((((((2 - 1 + 1) * rand()%11) + 1) - 1 + 1
                                                             ) * rand()%11) + 1) * 0.005);
        Particles[i].Red = 1;
        Particles[i].Green = 1;
        Particles[i].Blue = 1;
        Particles[i].Scalez = 0.1;
        Particles[i].Direction = 0;
        Particles[i].Acceleration = ((((((8 - 5 + 2) * rand()%11) + 5
                                       ) - 1 + 1) * rand()%11) + 1) * 0.2;
        Particles[i].Deceleration = 0.0025;
    }
}
void Particle::Update() {
    int i;
    for (i = 1; i < ParticleCount; i++)
    {
        
        glColor3f (Particles[i].Red, Particles[i].Green,
                   Particles[i].Blue);
        
        Particles[i].Ypos = Particles[i].Ypos + Particles[i]
        .Acceleration - Particles[i].Deceleration;
        Particles[i].Deceleration = Particles[i].Deceleration +
        0.0025;
        
        Particles[i].Xpos = Particles[i].Xpos + Particles[i].Xmov;
        Particles[i].Zpos = Particles[i].Zpos + Particles[i].Zmov;
        
        Particles[i].Direction = Particles[i].Direction + ((((((int
                                                              )(0.5 - 0.1 + 0.1) * rand()%11) + 1) - 1 + 1) * rand()%11) + 1);
        
        if (Particles[i].Ypos < -5)
        {
            Particles[i].Xpos = 0;
            Particles[i].Ypos = -5;
            Particles[i].Zpos = -5;
            Particles[i].Red = 1;
            Particles[i].Green = 1;
            Particles[i].Blue = 1;
            Particles[i].Direction = 0;
            Particles[i].Acceleration = ((((((8 - 5 + 2) * rand()%11) + 5
                                           ) - 1 + 1) * rand()%11) + 1) * 0.02;
            Particles[i].Deceleration = 0.0025;
        }
        
    }
}

void Particle::drawSquare() {
    glBegin (GL_QUADS);
    glTexCoord2d (0, 0);
    glVertex3f (-1, -1, 0);
    glTexCoord2d (1, 0);
    glVertex3f (1, -1, 0);
    glTexCoord2d (1, 1);
    glVertex3f (1, 1, 0);
    glTexCoord2d (0, 1);
    glVertex3f (-1, 1, 0);
    glEnd();
}

void Particle::drawCube() {
    glBegin(GL_QUADS);
    // Front Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
    // Back Face
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
    // Top Face
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
    // Bottom Face
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    // Right face
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);  // Bottom Left Of The Texture and Quad
    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glEnd();

}
void Particle::Render() {
    glPushMatrix();
    //cout<<"rendering particle: "<<texture[0]<<","<<texture[1]<<endl;
    //glTranslatef(position[0], position[1], position[2]);
    glEnable( GL_TEXTURE_2D );
    glEnable(GL_DEPTH_TEST);
    int i;
    for (i = 1; i < ParticleCount; i++)
    {
        glPushMatrix();
        //cout<<position[0] + Particles[i].Xpos<<", "<<position[1] + Particles[i].Ypos<<", "<<position[2] + Particles[i].Zpos<<endl;
        
        glTranslatef (position[0] + Particles[i].Xpos, position[1] + Particles[i].Ypos, position[2] + Particles[i].Zpos);
        //glTranslatef (position[0] + Particles[i].Xpos, 1, position[2] + Particles[i].Zpos);
        glRotatef (Particles[i].Direction - 90, 0, 0, 1);
        
        glScalef (Particles[i].Scalez, Particles[i].Scalez, Particles[i].Scalez);
        
        glDisable (GL_DEPTH_TEST);
        glEnable (GL_BLEND);
        
        glBlendFunc (GL_DST_COLOR, GL_ZERO);
        glBindTexture (GL_TEXTURE_2D, texture[0]);
        
        drawCube();
        
        glBlendFunc (GL_ONE, GL_ONE);
        glBindTexture (GL_TEXTURE_2D, texture[1]);
        
        drawCube();
        
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);
        glPopMatrix();
        
    }
    glPopMatrix();
    glColor3f(1.0, 1.0, 1.0);
}

GLuint Particle::LoadTextureRAW( const char * filename, int width,
                      int height )
{
    GLuint texture;
    unsigned char * data;
    FILE * file;
    
    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;
    
    data = (unsigned char *)malloc( width * height * 3 );
    
    fread( data, width * height * 3, 1, file );
    fclose( file );
    
    glGenTextures(1, &texture );
    
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                     GL_REPEAT);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
                     GL_REPEAT);
    
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,
              GL_MODULATE );
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_NEAREST );
    
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                    GL_LINEAR );
    
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height,
                      GL_RGB, GL_UNSIGNED_BYTE, data);
    
    free( data );
    
    return texture;
}

void Particle::FreeTexture( GLuint texture )
{
    glDeleteTextures( 1, &texture );
}
