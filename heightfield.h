

class HeightMap {
private:
	int hmHeight;
	int hmWidth;
    
    unsigned int tID[2];
public:
	bool Create(char *hFileName, const int hWidth, const int hHeight);
	void Render(void);
	char hHeightField[1024][1024];
    void ResetPlane();
};