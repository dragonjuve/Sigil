#pragma once
#include <string>
#include"SquareMeshVbo.h"
#include"WallMeshVbo.h"
#include"GLRendererEditor.h"
using namespace std;

class Grid
{
	bool wallTop;
	bool wallBottom;
	bool wallLeft;
	bool wallRight;
	string gridType;
	int row;
	int col;

public:
	Grid();
	~Grid();
	void draw();
	void setWallTop(bool value);
	void setWallBottom(bool value);
	void setWallLeft(bool value);
	void setWallRight(bool value);
	void setGridType(string type);
	void setRowCol(int row,int col);
	bool getWallTop();
	bool getWallBottom();
	bool getWallLeft();
	bool getWallRight();
	string getGridType();
	int getRow();
	int getCol();
	void drawWall();
};

