#pragma once
#include "MeshVbo.h"
#include "glm\glm.hpp"

class MapMeshVbo : public MeshVbo {
protected:
	virtual void loadData();
	GLuint textureId = -1;
	GLuint textureAttribId = -1;

public:
	MapMeshVbo();
	MapMeshVbo(int sizeRow, int sizeCol);
	virtual string getMeshName();
	virtual void render();
	void gridRender();
	glm::vec4 ** color;
	void setColor(int x, int y, glm::vec3 color);
	void setTexture(int x, int y, GLuint textureId);
	virtual void setAttribId(GLuint posId, GLuint textureId);
};