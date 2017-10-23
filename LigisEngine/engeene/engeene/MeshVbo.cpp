#include "MeshVbo.h"


MeshVbo::MeshVbo()
{
}

GLuint MeshVbo::getPosId()
{
  return this->posVboId;
}

GLuint MeshVbo::getColorId()
{
  return this->colorVboId;
}

void MeshVbo::setAttribId(GLuint posId, GLuint colorId)
{
  this->posAttribId = posId;
  this -> colorAttribId = colorId;
}
