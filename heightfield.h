const int MAX_MAP_SIZE = 1024;
const float MAP_SCALE = 0.2f;

class HeightMap {
private:
	int hmHeight;
	int hmWidth;
    GLuint TexID;

    unsigned int tID[2];
    bool fexists(const char *filename);

public:
    bool Create(char *texturePath, const int hWidth, const int hHeight);
	bool Create(char *hFileName, char *texturePath, const int hWidth, const int hHeight);
	void Render(void);
    char getHeight(int x, int z);
	char hHeightField[MAX_MAP_SIZE][MAX_MAP_SIZE];
    void ResetPlane();
};