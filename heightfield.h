const int MAP_SIZE = 256;
const float MAP_SCALE = 0.2f;

class HeightMap {
private:
	int hmHeight;
	int hmWidth;
    GLuint TexID;

    unsigned int tID[2];
    bool fexists(const char *filename);

public:
    bool Create(char *texturePath);
	bool Create(char *hFileName, char *texturePath);
	void Render(void);
    int getHeight(int x, int z);
	char hHeightField[MAP_SIZE * MAP_SIZE];
    void ResetPlane();
};