#include "SquareMeshVbo.h"

void SquareMeshVbo::loadData()
{
  //VBO data
  GLfloat vertexData[] =
  {
	 0.0f, 0.0f,
    0.0f, 1.0f,
	1.0f,  1.0f,
    1.0f,  0.0f
    
  };

  GLfloat colorData[] =
  {
    0.0f, 0.0f, 1.0f,
    0.5f, 0.0f, 0.5f,
    0.0f, 0.5f, 0.5f,
    0.0f, 0.0f, 0.5f,
  };

  GLfloat texCoorData[] =
  {
	  0.0f,0.0f,
	  0.0f,1.0f,
	  1.0f,1.0f,
	  1.0f,0.0f
  };

  //Create VBO
  glGenBuffers(1, &(this->posVboId));
  glBindBuffer(GL_ARRAY_BUFFER, this->posVboId);
  glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

  glGenBuffers(1, &(this->colorVboId));
  glBindBuffer(GL_ARRAY_BUFFER, this->colorVboId);
  glBufferData(GL_ARRAY_BUFFER, 3 * 4 * sizeof(GLfloat), colorData, GL_STATIC_DRAW);



}

SquareMeshVbo::SquareMeshVbo()
{
}

string SquareMeshVbo::getMeshName()
{
  return "Square";
}

void SquareMeshVbo::render()
{
  if (this->posAttribId != -1) {
    glBindBuffer(GL_ARRAY_BUFFER, this->posVboId);
    glVertexAttribPointer(this->posAttribId, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
  }
  if (this->colorAttribId != -1) {
    glBindBuffer(GL_ARRAY_BUFFER, this->colorVboId);
    glVertexAttribPointer(this->colorAttribId, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), NULL);
  }
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}
