#pragma once
#include"GLRendererEditor.h"
#include"LineMeshVbo.h"
#include"SquareMeshVbo.h"
#include"CircleMeshVbo.h"
#include"Grid.h"

class Map {
	private:
		int row;
		int col;
		Grid** grids;
	public:
		Map(int row, int col);
		~Map();
		void draw();
		int getRow();
		int getCol();
		void setRow(int row);
		void setCol(int col);
		Grid* getGridAt(int row, int col);
};