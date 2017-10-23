#pragma once
#include "GLRenderer.h"
class GLRendererColor :
  public GLRenderer
{
protected:
  int gColorLocation;
  virtual void setMeshAttribId(MeshVbo * shape);
  virtual bool initialize(string vertexShaderFile, string fragmentShaderFile);

public:
  GLRendererColor(int w, int h);
  ~GLRendererColor();
};

