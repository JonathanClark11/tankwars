#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "vector.h"
#include "gameobject.h"
#include "texloader.h"

const int ParticleCount = 500;

typedef struct
{
    double Xpos;
    double Ypos;
    double Zpos;
    double Xmov;
    double Zmov;
    double Red;
    double Green;
    double Blue;
    double Direction;
    double Acceleration;
    double Deceleration;
    double Scalez;
    bool Visible;
}PARTICLES;

class Particle : public GameObject {
private:
    GLuint texture[10];
    PARTICLES Particles[ParticleCount];
public:

    Particle(Vec3 pos) : GameObject(0, PARTICLE, Vec3(pos[0], pos[1], pos[2] + 25)) {
        texture[0] = LoadTextureRAW( "Data/particles/particle_mask.raw",256,256
                                    ); //load our texture
        texture[1] = LoadTextureRAW( "Data/particles/particle.raw",256,256);
        //load our texture
        createParticles();
        
    };
    void createParticles();
    void FreeTexture( GLuint texture );
    GLuint LoadTextureRAW( const char * filename, int width,
                          int height );
    void Render();
    void drawSquare();
    void drawCube();
    void Update();
};
#endif