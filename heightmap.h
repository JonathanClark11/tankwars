#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#include <iostream>
#include <string>
using namespace std;

#define     MAP_SIZE    256        // Size Of Our .RAW Height Map ( NEW )
#define     STEP_SIZE   16          // Width And Height Of Each Quad ( NEW )
#define     HEIGHT_RATIO    0.5f    // Ratio That The Y Is Scaled According To The X And Z ( NEW )

class HeightMap {
private:
	char g_HeightMap[MAP_SIZE*MAP_SIZE];        // Holds The Height Map Data 
	float scaleValue;							// Scale Value For The Terrain 

public:
    HeightMap() {
        ResetHeights();
        scaleValue = 0.15f;
    }
    HeightMap(string filename) {
        loadRawFile(filename);
        scaleValue=0.15f;
    }
    ~HeightMap(){}
    void ResetHeights();
    void loadRawFile(string filename);
	int Height(int X, int Y);
	void SetVertexColor(char *pHeightMap, int x, int y);
    void RenderHeightMap();
    
};