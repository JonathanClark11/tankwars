

class HeightMap {
private:
	int hmHeight;
	int hmWidth;
public:
	bool Create(char *hFileName, const int hWidth, const int hHeight);

	void Render(void);

	char hHeightField[1024][1024];
    
    void ResetPlane();
};