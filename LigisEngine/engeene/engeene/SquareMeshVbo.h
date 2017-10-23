#pragma once
#include "MeshVbo.h"

class SquareMeshVbo : public MeshVbo {
protected:
  virtual void loadData();

public:
  SquareMeshVbo();
  virtual string getMeshName();
  virtual void render();
};