#pragma once
#include "MeshVbo.h"

class WallMeshVbo : public MeshVbo {
protected:
	virtual void loadData();

public:
	WallMeshVbo();
	~WallMeshVbo();
	virtual string getMeshName();
	virtual void render();
};

