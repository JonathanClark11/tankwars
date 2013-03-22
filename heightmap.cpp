#include "heightmap.h"

// Loads The .RAW File And Stores It In pHeightMap
void HeightMap::loadRawFile()
{
    int nSize = MAP_SIZE * MAP_SIZE;
    char* pHeightMap = g_HeightMap;
	
    FILE *pFile = NULL;
	pFile = fopen( "Data/map.RAW", "rb" );
    
	// Check To See If We Found The File And Could Open It
	if ( pFile == NULL )
	{
		// Display Error Message And Stop The Function
			
		return;
	}
	// Here We Load The .RAW File Into Our pHeightMap Data Array
	// We Are Only Reading In '1', And The Size Is (Width * Height)
	fread( pHeightMap, 1, nSize, pFile );
	// After We Read The Data, It's A Good Idea To Check If Everything Read Fine
	int result = ferror( pFile );
	// Check If We Received An Error
	if (result)
	{
			
	}
	fclose(pFile);
}

int HeightMap::Height(char *pHeightMap, int X, int Y)          // This Returns The Height From A Height Map Index
{
	int x = X % MAP_SIZE;                   // Error Check Our x Value
	int y = Y % MAP_SIZE;                   // Error Check Our y Value
    
	if(!pHeightMap) return 0;               // Make Sure Our Data Is Valid
	return pHeightMap[x + (y * MAP_SIZE)];          // Index Into Our Height Array And Return The Height
}

void HeightMap::SetVertexColor(char *pHeightMap, int x, int y)     // This Sets The Color Value For A Particular Index
{                               // Depending On The Height Index
	if(!pHeightMap) return;                 // Make Sure Our Height Data Is Valid
    
	float fColor = -0.15f + (Height(pHeightMap, x, y ) / 256.0f);
    
	// Assign This Blue Shade To The Current Vertex
	glColor3f(0.0f, 0.0f, fColor );
}

void HeightMap::RenderHeightMap()             // This Renders The Height Map As Quads
{
    char pHeightMap[];
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
			y = Height(pHeightMap, X, Y );
			z = Y;
            
			// Set The Color Value Of The Current Vertex
			SetVertexColor(pHeightMap, x, z);
            
			glVertex3i(x, y, z);            // Send This Vertex To OpenGL To Be Rendered
            
			// Get The (X, Y, Z) Value For The Top Left Vertex
			x = X;
			y = Height(pHeightMap, X, Y + STEP_SIZE );
			z = Y + STEP_SIZE ;
            
			// Set The Color Value Of The Current Vertex
			SetVertexColor(pHeightMap, x, z);
            
			glVertex3i(x, y, z);            // Send This Vertex To OpenGL To Be Rendered
            
			// Get The (X, Y, Z) Value For The Top Right Vertex
			x = X + STEP_SIZE;
			y = Height(pHeightMap, X + STEP_SIZE, Y + STEP_SIZE );
			z = Y + STEP_SIZE ;
            
			// Set The Color Value Of The Current Vertex
			SetVertexColor(pHeightMap, x, z);
            
			glVertex3i(x, y, z);            // Send This Vertex To OpenGL To Be Rendered
            
			// Get The (X, Y, Z) Value For The Bottom Right Vertex
			x = X + STEP_SIZE;
			y = Height(pHeightMap, X + STEP_SIZE, Y );
			z = Y;
            
			// Set The Color Value Of The Current Vertex
			SetVertexColor(pHeightMap, x, z);
            
			glVertex3i(x, y, z);            // Send This Vertex To OpenGL To Be Rendered
		}
	glEnd();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);          // Reset The Color
}








//int DrawGLScene(GLvoid)                     // Here's Where We Do All The Drawing
//{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear The Screen And The Depth Buffer
//    glLoadIdentity();                   // Reset The Matrix
//    
//    //    Position   View       Up Vector
//    gluLookAt(212, 60, 194,  186, 55, 171,  0, 1, 0);   // This Determines The Camera's Position And View
//    glScalef(scaleValue, scaleValue * HEIGHT_RATIO, scaleValue);
//
//    RenderHeightMap(g_HeightMap);               // Render The Height Map
//    
//    return TRUE;                        // Keep Going
//}
