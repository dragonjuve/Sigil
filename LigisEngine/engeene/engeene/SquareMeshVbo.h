#pragma once
#include "MeshVbo.h"
#include "GLRendererEditor.h"

class SquareMeshVbo : public MeshVbo {
protected:
  virtual void loadData();
  GLuint texVboId = -1;
public:
  SquareMeshVbo();
  virtual string getMeshName();
  virtual void render();
};