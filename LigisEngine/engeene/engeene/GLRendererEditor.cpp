#include "GLRendererEditor.h"
#include "MapMeshVbo.h"
#include "CircleMeshVbo.h"
#include "LineMeshVbo.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include<string>
#include<fstream>

GLRendererEditor* GLRendererEditor::instance = nullptr;

GLRendererEditor * GLRendererEditor::getInstance()
{
	if (instance == nullptr)
		instance = new GLRendererEditor();
	return instance;
}

GLRendererEditor::GLRendererEditor() :GLRenderer(800, 600)
{
	this->winWidth = 800;
	this->winHeight = 600;
	this->gridX = 0;
	this->gridY = 0;
	//projectionMatrix = glm::ortho(-10.f, 10.f, -10.f, 10.f);
	projectionMatrix = glm::ortho(-2.f, 2.f, -2.f, 2.f);
	for (unsigned int i = 0; i < 16; i++) {
		textureId[i] = -1;
	}
}

GLRendererEditor::~GLRendererEditor()
{
}

bool GLRendererEditor::initialize(string vertexShaderFile, string fragmentShaderFile)
{
	bool loadShader = GLRenderer::initialize(vertexShaderFile, fragmentShaderFile);
	if (!loadShader) {
		return false;
	}

	//Setting color attribute id
	//Get vertex attribute location
	textureLocation = glGetAttribLocation(gProgramId, "inTexCoord");
	if (textureLocation == -1)
	{
		cout << "inTexCoord is not a valid glsl program variable" << endl;
		return false;
	}

	glEnableVertexAttribArray(textureLocation);
	return true;
}

void GLRendererEditor::initTex(string textureName) {
	if (idCount < 16) {
		glGenTextures(1, &textureId[idCount]);
		glBindTexture(GL_TEXTURE_2D, textureId[idCount]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		const char* textN = textureName.c_str();
		unsigned char *data = stbi_load(textN, &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			//std::cout << "OK load texture" << std::endl;
			idCount++;
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);

	}
}

void GLRendererEditor::initTexture()
{
	glGenTextures(1, &texturePrinnyId);
	glBindTexture(GL_TEXTURE_2D, texturePrinnyId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("D:/LigisEngine2/engeene/engeene/texture/prinny.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "OK load texture" << std::endl;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	glGenTextures(1, &textureTileId);
	glBindTexture(GL_TEXTURE_2D, textureTileId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	data = stbi_load("D:/LigisEngine2/engeene/engeene/texture/tile.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		std::cout << "OK load texture" << std::endl;
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

void GLRendererEditor::setMeshAttribId(MeshVbo * shape)
{
	shape->setAttribId(gVertexPos2DLocation, textureLocation);
}

void GLRendererEditor::render()
{
	// Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Update window with OpenGL rendering
	glUseProgram(gProgramId);
	//Set up matrix uniform
	matrixId = glGetUniformLocation(gProgramId, "mMatrix");
	colorId = glGetUniformLocation(gProgramId, "colorVec");
	modeId = glGetUniformLocation(gProgramId, "mode");

	drawGrid();
	//MapMeshVbo * map = dynamic_cast<MapMeshVbo*>(shapes["Map"]);
	//CircleMeshVbo * cir = dynamic_cast<CircleMeshVbo*>(shapes["Circle"]);
	//map->setColor(3, 3, glm::vec3(1.0f));
	

	/*glUniform1i(modeId, 0);
	for (int x = 0; x < this->mapSizeCol; x++)
	{
		for (int y = 0; y < this->mapSizeRow; y++)
		{
			modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3(x - (this->mapSizeCol/2), (this->mapSizeRow / 2) - y, 0));
			glm::mat4 transform = projectionMatrix* modelMatrix;
			glUniformMatrix4fv(matrixId, 1, GL_FALSE, glm::value_ptr(transform));
			if (map->color[x][y].w == -1)
			{
				glUniform3fv(colorId, 1, glm::value_ptr(glm::vec3(map->color[x][y].x, map->color[x][y].y, map->color[x][y].z)));
				glUniform1i(modeId, 0);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, map->color[x][y].w);
				glUniform1i(modeId, 1);
			}
			map->render();
		}
	}

	glUniform1i(modeId, 0);
	modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3(gridX, gridY, 0));
	glm::mat4 transform = projectionMatrix* modelMatrix;
	glUniformMatrix4fv(matrixId, 1, GL_FALSE, glm::value_ptr(transform));
	glUniform3fv(colorId, 1, glm::value_ptr(glm::vec3(0.0f)));
	glLineWidth(1.0f);
	map->gridRender();

	for (int i = 0; i < 5; i++) {
		modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3((-mapSizeRow / 2)+(2.5*i), (-mapSizeCol / 2) - 2, 0));
		transform = projectionMatrix* modelMatrix;

		glUniformMatrix4fv(matrixId, 1, GL_FALSE, glm::value_ptr(transform));
		glUniform3fv(colorId, 1, glm::value_ptr(colorList[i]));
		shapes["Circle"]->render();
	}

	modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3((-mapSizeRow / 2) + (2.5*currentColor), (-mapSizeCol / 2) - 2, 0));
	transform = projectionMatrix* modelMatrix;
	glUniformMatrix4fv(matrixId, 1, GL_FALSE, glm::value_ptr(transform));
	glUniform3fv(colorId, 1, glm::value_ptr(glm::vec3(0.0f)));
	glLineWidth(10.0f);
	cir->gridRender();

	glUniform1i(modeId, 1);
	modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3((-mapSizeRow / 2) + (2.5*5), (-mapSizeCol / 2) - 2, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(2, 2, 0));
	transform = projectionMatrix* modelMatrix;
	glUniformMatrix4fv(matrixId, 1, GL_FALSE, glm::value_ptr(transform));
	glBindTexture(GL_TEXTURE_2D, textureId[0]);
	shapes["Map"]->render();

	modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3((-mapSizeRow / 2) + (2.5 * 6), (-mapSizeCol / 2) - 2, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(2, 2, 0));
	transform = projectionMatrix* modelMatrix;
	glUniformMatrix4fv(matrixId, 1, GL_FALSE, glm::value_ptr(transform));
	glBindTexture(GL_TEXTURE_2D, textureId[1]);
	shapes["Map"]->render();*/

	//Unbind program
	glUseProgram(NULL);
}

void GLRendererEditor::setWH(int w, int h)
{
	this->winWidth = w;
	this->winHeight = h;
	GLRenderer::setWH(w, h);
}

//void GLRendererEditor::saveMap() {
//	ofstream mapOut("save.txt");
//	if (mapOut.is_open()) {
//		MapMeshVbo * map = dynamic_cast<MapMeshVbo*>(shapes["Map"]);
//		mapOut << mapSizeRow << " " << mapSizeCol << endl;
//		for (int i = 0; i < this->mapSizeRow; i++) {
//			for (int j = 0; j < this->mapSizeCol; j++) {
//				if (map->color[i][j].w == -1)
//				{
//					mapOut << '0' << " " << map->color[i][j].r << " " << map->color[i][j].g << " " << map->color[i][j].b << " # " ;
//				}
//				
//			}
//			mapOut << endl;
//		}
//		mapOut.close();
//	}
//	else {
//
//	}
//}

//void GLRendererEditor::loadMap() {
//	ifstream mapIn("save.txt");
//	if (mapIn.is_open()) {
//		MapMeshVbo * map = dynamic_cast<MapMeshVbo*>(shapes["Map"]);
//		string texco,r,g,b;
//		mapIn >> texco;
//		mapSizeRow = stoi(texco);
//		mapIn >> texco;
//		mapSizeCol = stoi(texco);
//		for (int i = 0; i < this->mapSizeRow; i++) {
//			for (int j = 0; j < this->mapSizeCol; j++) {
//				mapIn >> texco;
//				if (stoi(texco) == 0) {
//					mapIn >> r >> g >> b;
//					map->color[i][j].x = stof(r);
//					map->color[i][j].y = stof(g);
//					map->color[i][j].z = stof(b);
//					map->color[i][j].w = -1;
//				}
//				mapIn >> texco;
//			}
//			
//		}
//		mapIn.close();
//	}
//	else {
//
//	}
//}

void GLRendererEditor::initRender()
{
	// Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Update window with OpenGL rendering
	glUseProgram(gProgramId);
	//Set up matrix uniform
	matrixId = glGetUniformLocation(gProgramId, "mMatrix");
	colorId = glGetUniformLocation(gProgramId, "colorVec");
	modeId = glGetUniformLocation(gProgramId, "mode");
	glUniform1i(modeId, 0);
	modelMatrix = glm::scale(glm::mat4(1.f), glm::vec3(4, 1, 0)) ;
	glm::mat4 transform = projectionMatrix* modelMatrix;
	glUniformMatrix4fv(matrixId, 1, GL_FALSE, glm::value_ptr(transform));
	//glLineWidth(1.0f);


}

void GLRendererEditor::setRenderColor(glm::vec3 clr)
{
	glUniform3fv(colorId, 1, glm::value_ptr(clr));
}

void GLRendererEditor::setRenderTex(int index)
{
	glBindTexture(GL_TEXTURE_2D, textureId[index]);
}




void GLRendererEditor::endRender()
{
	glUseProgram(NULL);
}

void GLRendererEditor::setMapSize(int row,int col)
{
	this->mapSizeRow = row;
	this->mapSizeCol = col;
}

void GLRendererEditor::setProjectionMat(int row, int col)
{
	projectionMatrix = glm::ortho(0.f, (float)col, 0.f, (float)row);
}

glm::mat4 GLRendererEditor::getProjection() {
	return projectionMatrix;
}

void GLRendererEditor::moveGrid(int direction)
{
	if (direction == 0)
	{
		if (gridY < this->mapSizeRow / 2)
		{
			gridY++;
		}
	}
	else if (direction == 1)
	{
		if (gridY > -(this->mapSizeRow / 2))
		{
			gridY--;
		}
	}
	else if (direction == 2)
	{
		if (gridX < this->mapSizeCol / 2)
		{
			gridX++;
		}
	}
	else
	{
		if (gridX > -(this->mapSizeCol / 2))
		{
			gridX--;
		}
	}
}

void GLRendererEditor::changeMapColor()
{
	int x = (this->mapSizeCol / 2) + gridX;
	int y = (this->mapSizeRow / 2) - gridY;
	MapMeshVbo * map = dynamic_cast<MapMeshVbo*>(shapes["Map"]);
	if (this->currentColor != -1)
	{
		map->setColor(x, y, this->colorList[this->currentColor]);
	}
	else
	{
		map->setTexture(x, y, this->currentTexture);
	}
}

void GLRendererEditor::setCurrentColor(int color)
{
	this->currentColor = color;
	this->currentSelect = color;
}

void GLRendererEditor::setCurrentTexture(int texture)
{
	this->currentColor = -1;
	if (texture == 1)
	{
		this->currentTexture = textureId[0];
		this->currentSelect = 5;
	}
	else
	{
		this->currentTexture = textureId[1];
		this->currentSelect = 6;
	}

}

void GLRendererEditor::drawGrid() {
	/*for (int i = 1; i < mapSizeRow; i++) {
		LineMeshVbo * line = dynamic_cast<LineMeshVbo*>(shapes["Line"]);
		glUniform1i(modeId, 0);
		modelMatrix = glm::scale(glm::mat4(1.f),glm::vec3(winWidth,1,0)) * glm::translate(glm::mat4(1.f), glm::vec3(0, (-winHeight/2)+(i*winHeight/mapSizeRow), 0));
		glm::mat4 transform = projectionMatrix* modelMatrix;
		glUniformMatrix4fv(matrixId, 1, GL_FALSE, glm::value_ptr(transform));
		glLineWidth(1.0f);
		line->render();
	}*/

	/*for (int i = 1; i < mapSizeCol; i++) {
		LineMeshVbo * line = dynamic_cast<LineMeshVbo*>(shapes["Line"]);
		glUniform1i(modeId, 0);
		modelMatrix = glm::scale(glm::mat4(1.f), glm::vec3(winWidth, 1, 0)) * glm::translate(glm::mat4(1.f), glm::vec3((-winWidth / 2) + (i*winWidth / mapSizeCol), 0, 0));
		glm::mat4 transform = projectionMatrix* modelMatrix;
		glUniformMatrix4fv(matrixId, 1, GL_FALSE, glm::value_ptr(transform));
		glLineWidth(1.0f);
		line->render();
	}*/
}

void GLRendererEditor::setShaderMode(int mode) {
	glUniform1i(modeId, mode);
}



void GLRendererEditor::setShaderModelMat(glm::mat4 mat)
{
	glUniformMatrix4fv(matrixId, 1, GL_FALSE, glm::value_ptr(mat));
}

//Make a uniform color function.