#pragma once
#include "MeshVbo.h"
#include "glm\glm.hpp"

class LineMeshVbo : public MeshVbo {
protected:
	virtual void loadData();
	GLuint textureId = -1;
	GLuint textureAttribId = -1;

public:
	LineMeshVbo();
	//LineMeshVbo(int size);
	virtual string getMeshName();
	virtual void render();
	
}; 
