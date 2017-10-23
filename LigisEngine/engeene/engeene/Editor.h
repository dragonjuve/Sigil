#pragma once
#include "Map.h"
class Editor
{
	Map *map;
	Grid *currentGrid;

public:
	Editor();
	~Editor();
	void createNewMap(int row, int col);
	void setCurrentGrid(int row, int col);
	Grid* getCurrentGrid();
	Map* getMap();
	Grid* getGridFrom(int row, int col);
};

