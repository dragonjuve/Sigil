#include"Map.h"
//#include <wx/wx.h>
//#include<string.h>

Map::Map(int row, int col) {
	(*this).row = row;
	(*this).col = col;
	grids = new Grid*[row];
	for (int i = 0; i < row; i++)
		grids[i] = new Grid[col];

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			grids[i][j].setRowCol(i, j);
		}
	}
}

Map::~Map() {
	for (int i = 0; i < row; i++) {
		delete[] grids[i];
	}
	delete[] grids;
}

void Map::draw() {
	LineMeshVbo* line = dynamic_cast<LineMeshVbo*> (GLRendererEditor::getInstance()->getShape("Line"));
	//glm::mat4 projection = glm::ortho(0.f, (float)col, 0.f, (float)row);
	GLRendererEditor::getInstance()->setProjectionMat(row, col);
	for (int i = 1; i < row; i++) {
		glm::mat4 modelMatrix = glm::mat4(1.f);
		modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3((float)col / 2.f, i, 0));
		modelMatrix = modelMatrix * glm::scale(glm::mat4(1.f), glm::vec3(col, 1, 1));
		
		//glm::mat4 transform = projection * modelMatrix;
		glm::mat4 transform = GLRendererEditor::getInstance()->getProjection() * modelMatrix;
		GLRendererEditor::getInstance()->setShaderMode(0);
		GLRendererEditor::getInstance()->setShaderModelMat(transform);
		line->render();
	}

	for (int i = 1; i < col; i++) {
		glm::mat4 modelMatrix = glm::mat4(1.f);
		modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3(i, (float)row/2.f, 0));
		
		modelMatrix = modelMatrix * glm::scale(glm::mat4(1.f), glm::vec3(1, row, 1));
		modelMatrix = modelMatrix * glm::rotate(glm::mat4(1.f), 22.f/14.f, glm::vec3(0, 0, 1));
		glm::mat4 transform = GLRendererEditor::getInstance()->getProjection() * modelMatrix;
		//glm::mat4 transform = projection * modelMatrix;
		GLRendererEditor::getInstance()->setShaderMode(0);
		GLRendererEditor::getInstance()->setShaderModelMat(transform);
		line->render();
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (grids[i][j].getGridType().compare("") != 0 ) {
				if (grids[i][j].getGridType().compare("A") == 0) {
					GLRendererEditor::getInstance()->setRenderTex(0);
				}
				else if (grids[i][j].getGridType().compare("B") == 0) {
					GLRendererEditor::getInstance()->setRenderTex(1);
				}
				grids[i][j].draw();
			}
			
		}
	}
}

int Map::getRow() {
	return row;
}
int Map::getCol() {
	return col;
}
void Map::setRow(int row) {
	(*this).row = row;
}
void Map::setCol(int col) {
	(*this).col = col;
}

Grid* Map::getGridAt(int row, int col) {
	return &grids[row][col];
}