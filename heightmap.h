#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#include <iostream>
#include <string>
using namespace std;

#define     MAP_SIZE    45        // Size Of Our .RAW Height Map ( NEW )
#define     STEP_SIZE   16          // Width And Height Of Each Quad ( NEW )
#define     HEIGHT_RATIO    4.0f    // Ratio That The Y Is Scaled According To The X And Z ( NEW )

class HeightMap {
private:
	char g_HeightMap[MAP_SIZE*MAP_SIZE];        // Holds The Height Map Data 
	float scaleValue;							// Scale Value For The Terrain 

public:
    HeightMap() {
        ResetHeights();
        scaleValue = 0.15f;
    }
    
    void ResetHeights() {
        for (int i = 0; i < sizeof(g_HeightMap); i++) {
            g_HeightMap[i] = 0;
        }
    }
	
    void loadRawFile(char* filename) {
        int nSize = MAP_SIZE * MAP_SIZE;
        char* pHeightMap = g_HeightMap;
        FILE *pFile = NULL;
        pFile = fopen( "Data/maps/Terrain.RAW", "rb" );
        
        // Check To See If We Found The File And Could Open It
        if ( pFile == NULL )
        {
            // Display Error Message And Stop The Function
			
            return;
        }
        // Here We Load The .RAW File Into Our pHeightMap Data Array
        // We Are Only Reading In '1', And The Size Is (Width * Height)
        fread( g_HeightMap, 1, nSize, pFile );
        // After We Read The Data, It's A Good Idea To Check If Everything Read Fine
        int result = ferror( pFile );
        // Check If We Received An Error
        if (result)
        {
			
        }
        fclose(pFile);
        cout<<"--------------------HEIGHTMAP DATA-----------------------"<<endl;
        cout<<"Size: "<<sizeof(g_HeightMap)<<endl;
        cout<<g_HeightMap<<endl;
    }

	int Height(int X, int Y) {
        int x = X % MAP_SIZE;                   // Error Check Our x Value
        int y = Y % MAP_SIZE;                   // Error Check Our y Value
        
        if(!g_HeightMap) return 0;               // Make Sure Our Data Is Valid
        return g_HeightMap[x + (y * MAP_SIZE)] / 255;          // Index Into Our Height Array And Return The Height
    }

	void SetVertexColor(char *pHeightMap, int x, int y) {
        if(!pHeightMap) return;                 // Make Sure Our Height Data Is Valid
        
        float fColor = -0.15f + (Height(x, y ) / 256.0f);
        
        // Assign This Blue Shade To The Current Vertex
        glColor3f(1.0f, 1.0f, 1.0f );
    }
    
    void RenderHeightMap() {
        char* pHeightMap = g_HeightMap;
        int X = 0, Y = 0;                   // Create Some Variables To Walk The Array With.
        int x, y, z;                        // Create Some Variables For Readability
        
        if(!pHeightMap)
        {
            glutSolidCube(1);
            return;
        }                 // Make Sure Our Height Data Is Valid
        
        //if(bRender)                     // What We Want To Render
        //	glBegin( GL_QUADS );                // Render Polygons
        //else
		glBegin( GL_LINES );                // Render Lines Instead
        
        for ( X = 0; X < (MAP_SIZE-STEP_SIZE); X += STEP_SIZE )
            for ( Y = 0; Y < (MAP_SIZE-STEP_SIZE); Y += STEP_SIZE )
            {
                // Get The (X, Y, Z) Value For The Bottom Left Vertex
                x = X;
                y = Height(X, Y);
                z = Y;
                
                // Set The Color Value Of The Current Vertex
                SetVertexColor(pHeightMap, x, z);
                
                glVertex3i(x, y, z);            // Send This Vertex To OpenGL To Be Rendered
                
                // Get The (X, Y, Z) Value For The Top Left Vertex
                x = X;
                y = Height(X, Y + STEP_SIZE );
                z = Y + STEP_SIZE ;
                
                // Set The Color Value Of The Current Vertex
                SetVertexColor(pHeightMap, x, z);
                
                glVertex3i(x, y, z);            // Send This Vertex To OpenGL To Be Rendered
                
                // Get The (X, Y, Z) Value For The Top Right Vertex
                x = X + STEP_SIZE;
                y = Height(X + STEP_SIZE, Y + STEP_SIZE );
                z = Y + STEP_SIZE ;
                
                // Set The Color Value Of The Current Vertex
                SetVertexColor(pHeightMap, x, z);
                
                glVertex3i(x, y, z);            // Send This Vertex To OpenGL To Be Rendered
                
                // Get The (X, Y, Z) Value For The Bottom Right Vertex
                x = X + STEP_SIZE;
                y = Height(X + STEP_SIZE, Y );
                z = Y;
                
                // Set The Color Value Of The Current Vertex
                SetVertexColor(pHeightMap, x, z);
                
                glVertex3i(x, y, z);            // Send This Vertex To OpenGL To Be Rendered
            }
        glEnd();
        glColor4f(1.0f, 1.0f, 1.0f, 1.0f);          // Reset The Color
    }
    
};