#pragma once

#include <GL\glew.h>
#include <string>

using namespace std;

class MeshVbo {
protected:
  GLuint posVboId=-1;
  GLuint colorVboId =-1;
  GLuint posAttribId = -1;
  GLuint colorAttribId = -1;

public:
  MeshVbo();
  virtual void loadData() = 0;
  virtual string getMeshName() = 0;
  GLuint getPosId();
  GLuint getColorId();
  virtual void render() =0;
  virtual void setAttribId(GLuint posId, GLuint colorId);

};