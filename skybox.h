// call Draw_Skybox(0,0,0,100,100,100);	// Draw the Skybox in render function
class SkyBox {
private:
    GLuint textures[6];

public:
    bool Create(char *texturePath[6]);
	void Render(float x, float y, float z, float width, float height, float length);
};