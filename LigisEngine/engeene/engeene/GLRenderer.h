#pragma once

#include <iostream>
#include <GL\glew.h>
#include "Shader.h"
#include <map>
#include <string>
#include "MeshVbo.h"
#include "glm\glm.hpp"

using namespace std;

class GLRenderer
{
protected:
  int winWidth;
  int winHeight;
  glm::mat4 projectionMatrix;
  glm::mat4 modelMatrix;
  GLuint matrixId;
  int trianglePos = 0;

  GLuint gProgramId;
  int gVertexPos2DLocation;
  void printProgramLog(GLuint program);
  virtual bool initialize(string vertexShaderFile, string fragmentShaderFile);
  Shader *vertexShader;
  Shader *fragmentShader;
  map <string, MeshVbo*> shapes;
  virtual void setMeshAttribId(MeshVbo * shape);
  
public:
  GLRenderer(int w,int h);
  bool initGL(string vertexShaderFile, string fragmentShaderFile);
  virtual void render();
  void addShape(string name, MeshVbo* shape);
  MeshVbo* getShape(string name);
  ~GLRenderer();
  void move(int distance);
  void setViewport(int w, int h);
  void setWH(int w, int h);
};

//class GLRendererEx2 :public GLRenderer{
//protected:
//  virtual bool initialize(string vertexShaderFile, string fragmentShaderFile);
//public:
//  GLRendererEx2();
//  virtual void render();
//};
