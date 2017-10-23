#pragma once
#include "MeshVbo.h"

class CircleMeshVbo : public MeshVbo {
protected:
	virtual void loadData();

public:
	CircleMeshVbo();
	virtual string getMeshName();
	virtual void render();
	void gridRender();
};