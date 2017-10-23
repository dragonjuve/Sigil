#include "GLRendererColor.h"



void GLRendererColor::setMeshAttribId(MeshVbo * shape)
{
  shape->setAttribId(gVertexPos2DLocation, gColorLocation);
}

bool GLRendererColor::initialize(string vertexShaderFile, string fragmentShaderFile)
{
  bool loadShader = GLRenderer::initialize(vertexShaderFile, fragmentShaderFile);
  if (!loadShader) {
    return false;
  }

  //Setting color attribute id
  //Get vertex attribute location
  gColorLocation = glGetAttribLocation(gProgramId, "VertexColor");
  if (gColorLocation == -1)
  {
    cout << "VertexColor is not a valid glsl program variable" << endl;
    return false;
  }

  glEnableVertexAttribArray(gColorLocation);
  return true;
}

GLRendererColor::GLRendererColor(int w, int h):GLRenderer(w,h)
{
}


GLRendererColor::~GLRendererColor()
{
}
