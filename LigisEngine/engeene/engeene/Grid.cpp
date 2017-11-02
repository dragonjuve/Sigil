#include "Grid.h"



Grid::Grid()
{
	wallTop = false;
	wallBottom = false;
	wallLeft = false;
	wallRight = false;
	gridType = "";
}


Grid::~Grid()
{
}

void Grid::draw() {
	SquareMeshVbo* square = dynamic_cast<SquareMeshVbo*> (GLRendererEditor::getInstance()->getShape("Square"));
	glm::mat4 modelMatrix = glm::mat4(1.f);
	modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3((float)col, (float)row, 0.f));

	//glm::mat4 transform = projection * modelMatrix;
	glm::mat4 transform = GLRendererEditor::getInstance()->getProjection() * modelMatrix;
	GLRendererEditor::getInstance()->setShaderMode(1);
	GLRendererEditor::getInstance()->setShaderModelMat(transform);
	//GLRendererEditor::getInstance()->setRenderTex(0);
	square->render();
	drawWall();
	//implement draw just like map
	//for now just change the color
	//วาดตัวแหน่งไหนขึ้นอยู่กับrow col
	//วาดโดยการtranslate
}

void Grid::setWallTop(bool value) {
	wallTop = value;
}

void Grid::setWallBottom(bool value) {
	wallBottom = value;
}

void Grid::setWallLeft(bool value){
	wallLeft = value;
}

void Grid::setWallRight(bool value){
	wallRight = value;
}

void Grid::setGridType(string type)
{
	gridType = type;
}

void Grid::setRowCol(int row, int col)
{
	this->row = row;
	this->col = col;
}

bool Grid::getWallTop()
{
	return wallTop;
}

bool Grid::getWallBottom()
{
	return wallBottom;
}

bool Grid::getWallLeft()
{
	return wallLeft;
}

bool Grid::getWallRight()
{
	return wallRight;
}

string Grid::getGridType()
{
	return gridType;
}

int Grid::getRow()
{
	return row;
}

int Grid::getCol()
{
	return col;
}

void Grid::drawWall() {
	WallMeshVbo* wall = dynamic_cast<WallMeshVbo*> (GLRendererEditor::getInstance()->getShape("Wall"));
	GLRendererEditor::getInstance()->setShaderMode(0);
	//GLRendererEditor::getInstance()->setRenderColor(glm::vec3(0.647f, 0.165f, 0.165f));
	if (wallTop) {
		glm::mat4 modelMatrix = glm::mat4(1.f);
		modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3((float)col + 0.5f, (float)row + 0.9f, 0.f));
		modelMatrix = modelMatrix * glm::scale(glm::mat4(1.f), glm::vec3(1, 0.2, 1));
		glm::mat4 transform = GLRendererEditor::getInstance()->getProjection() * modelMatrix;
				
		GLRendererEditor::getInstance()->setShaderModelMat(transform);
		
		wall->render();
	}
	if (wallBottom) {
		glm::mat4 modelMatrix = glm::mat4(1.f);
		modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3((float)col + 0.5f, (float)row + 0.1f, 0.f));
		modelMatrix = modelMatrix * glm::scale(glm::mat4(1.f), glm::vec3(1, 0.2, 1));
		glm::mat4 transform = GLRendererEditor::getInstance()->getProjection() * modelMatrix;

		
		GLRendererEditor::getInstance()->setShaderModelMat(transform);
		
		wall->render();
	}
	if (wallLeft) {
		glm::mat4 modelMatrix = glm::mat4(1.f);
		modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3((float)col + 0.1f, (float)row + 0.5f, 0.f));
		modelMatrix = modelMatrix *  glm::rotate(glm::mat4(1.f), 22.f / 14.f, glm::vec3(0, 0, 1));
		modelMatrix = modelMatrix * glm::scale(glm::mat4(1.f), glm::vec3(1, 0.2, 1));
		glm::mat4 transform = GLRendererEditor::getInstance()->getProjection() * modelMatrix;

		
		GLRendererEditor::getInstance()->setShaderModelMat(transform);
		
		wall->render();
	}
	if (wallRight) {
		glm::mat4 modelMatrix = glm::mat4(1.f);
		modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3((float)col + 0.9f, (float)row + 0.5f, 0.f));
		modelMatrix = modelMatrix *  glm::rotate(glm::mat4(1.f), 22.f / 14.f, glm::vec3(0, 0, 1));
		modelMatrix = modelMatrix * glm::scale(glm::mat4(1.f), glm::vec3(1, 0.2, 1));
		glm::mat4 transform = GLRendererEditor::getInstance()->getProjection() * modelMatrix;

		
		GLRendererEditor::getInstance()->setShaderModelMat(transform);
		
		wall->render();
	}
}
