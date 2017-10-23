#pragma once
#include "MeshVbo.h"
class TriangleMeshVbo :
  public MeshVbo
{
protected:
  virtual void loadData();
public:
  TriangleMeshVbo();
  ~TriangleMeshVbo();
  virtual string getMeshName();
  virtual void render();
};

