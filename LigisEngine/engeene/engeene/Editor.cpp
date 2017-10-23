#include "Editor.h"



Editor::Editor()
{
	map = nullptr;
	currentGrid = nullptr;
}


Editor::~Editor()
{
	if (map != nullptr) {
		delete map;
	}
	if (currentGrid != nullptr) {
		delete currentGrid;
	}
}

void Editor::createNewMap(int row, int col)
{
	if (map != nullptr) {
		delete map;
	}
	map = new Map(row, col);
	GLRendererEditor::getInstance()->setProjectionMat(row, col);
}

void Editor::setCurrentGrid(int row, int col)
{
	currentGrid = map->getGridAt(row, col);
}

Map* Editor::getMap() {
	return map;
}

Grid* Editor::getCurrentGrid() {
	return currentGrid;
}

Grid* Editor::getGridFrom(int row, int col) {
	return (*map).getGridAt(row, col);
}