#include "TrangleMeshVbo.h"



void TriangleMeshVbo::loadData()
{
  //VBO data
  GLfloat vertexData[] =
  {
    -0.5f, -0.5f,
    0.5f, -0.5f,
    0.0f,  0.5f,
  };

  GLfloat colorData[] =
  {
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
    0.0f, 0.0f, 1.0f,
  };

  //Create VBO
  glGenBuffers(1, &(this->posVboId));
  glBindBuffer(GL_ARRAY_BUFFER, this->posVboId);
  glBufferData(GL_ARRAY_BUFFER, 2 * 3 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

  glGenBuffers(1, &(this->colorVboId));
  glBindBuffer(GL_ARRAY_BUFFER, this->colorVboId);
  glBufferData(GL_ARRAY_BUFFER, 3 * 3 * sizeof(GLfloat), colorData, GL_STATIC_DRAW);
}

TriangleMeshVbo::TriangleMeshVbo()
{
}


TriangleMeshVbo::~TriangleMeshVbo()
{
}

string TriangleMeshVbo::getMeshName()
{
  return "Triangle";
}

void TriangleMeshVbo::render()
{
  if (this->posAttribId != -1) {
    glBindBuffer(GL_ARRAY_BUFFER, this->posVboId);
    glVertexAttribPointer(this->posAttribId, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
  }
  if (this->colorAttribId != -1) {
    glBindBuffer(GL_ARRAY_BUFFER, this->colorVboId);
    glVertexAttribPointer(this->colorAttribId, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
  }
  glDrawArrays(GL_TRIANGLES, 0, 3);
}
