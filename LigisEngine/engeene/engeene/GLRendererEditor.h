#pragma once
#include "GLRenderer.h"
#include "glm/gtc/matrix_transform.hpp"

class GLRendererEditor : public GLRenderer
{
protected:
	static GLRendererEditor* instance;
	GLuint colorId;
	GLuint modeId;
	GLuint texturePrinnyId = -1;
	GLuint textureTileId = -1;
	GLuint textureId[16];
	int idCount = 0;
	int mapSizeRow;
	int mapSizeCol;
	int gridX;
	int gridY;
	glm::vec3 * colorList;
	int currentColor;
	GLuint currentTexture;
	int currentSelect;
	int textureLocation;
	virtual bool initialize(string vertexShaderFile, string fragmentShaderFile);
	virtual void setMeshAttribId(MeshVbo * shape);
	void drawGrid();
	GLRendererEditor();

public:
	static GLRendererEditor* getInstance();
	//GLRendererEditor(int w, int h);
	~GLRendererEditor();
	virtual void render();
	void setWH(int w, int h);
	void setMapSize(int row,int col);
	void setProjectionMat(int row, int col);
	glm::mat4 getProjection();
	void moveGrid(int direction);
	void changeMapColor();
	void setCurrentColor(int color);
	void setCurrentTexture(int texture);
	void initTexture();
	void initTex(string textureName);
	//void saveMap();
	//void loadMap();
	void initRender();
	
	void endRender();
	void setShaderMode(int mode);
	void setShaderModelMat(glm::mat4 mat);
	void setRenderColor(glm::vec3 clr);
	void setRenderTex(int index);
	
};
