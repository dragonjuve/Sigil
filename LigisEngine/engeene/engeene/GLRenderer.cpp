#include "GLRenderer.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;



GLRenderer::GLRenderer(int w, int h)
{
  this->winWidth = w;
  this->winHeight = h;
  projectionMatrix = glm::ortho(-2.f,2.f,-2.f,2.f);
  
 
}

bool GLRenderer::initGL(string vertexShaderFile, string fragmentShaderFile)
{
  // Initialize glew
  GLenum glewError = glewInit();
  if (glewError != GLEW_OK)
  {
    cout << "Error initializing GLEW! " << glewGetErrorString(glewError) << endl;
    return false;
  }


  //Initialize OpenGL
  if (!initialize(vertexShaderFile, fragmentShaderFile))
  {
    cout << "Unable to initialize OpenGL! " << endl;
    return false;
  }
  return true;
}

void GLRenderer::render()
{
  // Clear color buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Update window with OpenGL rendering
  glUseProgram(gProgramId);
  //Set up matrix uniform
  matrixId = glGetUniformLocation(gProgramId, "mMatrix");
  glUniformMatrix4fv(matrixId, 1, GL_FALSE, glm::value_ptr(this->projectionMatrix));

  
  shapes["Square"]->render();
  modelMatrix = glm::translate(glm::mat4(1.f), glm::vec3(trianglePos,0,0));
  glm::mat4 transform = projectionMatrix* modelMatrix;
  glUniformMatrix4fv(matrixId, 1, GL_FALSE, glm::value_ptr(transform));

  shapes["Triangle"]->render();


  //Unbind program
  glUseProgram(NULL);
}

void GLRenderer::setMeshAttribId(MeshVbo * shape)
{
  shape->setAttribId(gVertexPos2DLocation, -1);
}

void GLRenderer::addShape(string name, MeshVbo * shape)
{
  setMeshAttribId( shape);
  shapes[name] = shape;
}
MeshVbo * GLRenderer::getShape(string name)
{
	if (shapes.find(name) == shapes.end()) {
		return nullptr;
	}
	return shapes[name];
}
void GLRenderer::printProgramLog(GLuint program)
{
  //Make sure name is shader
  if (glIsProgram(program))
  {
    //Program log length
    int infoLogLength = 0;
    int maxLength = infoLogLength;

    //Get info string length
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

    //Allocate string
    char* infoLog = new char[maxLength];

    //Get info log
    glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
    if (infoLogLength > 0)
    {
      //Print Log
      cout << infoLog << endl;
     
    }

    //Deallocate string
    delete[] infoLog;
  }
  else
  {
    printf("Name %d is not a program\n", program);
  }
}

bool GLRenderer::initialize(string vertexShaderFile, string fragmentShaderFile)
{
    //Success flag
    bool success = true;

    //Generate program
    gProgramId = glCreateProgram();
    vertexShader = new Shader(vertexShaderFile,GL_VERTEX_SHADER);
    if (!vertexShader->loadSource()) {
      return false;
    }
    fragmentShader = new Shader(fragmentShaderFile, GL_FRAGMENT_SHADER);
    if (!fragmentShader->loadSource()) {
      return false;
    }
    glAttachShader(gProgramId, vertexShader->getShaderId());
    glAttachShader(gProgramId, fragmentShader->getShaderId());


    //Link program
    glLinkProgram(gProgramId);

    //Check for errors
    GLint programSuccess = GL_TRUE;
    glGetProgramiv(gProgramId, GL_LINK_STATUS, &programSuccess);
    if (programSuccess != GL_TRUE)
    {
      cout << "Error linking program " << gProgramId << endl;
      printProgramLog(gProgramId);
      return false;
    }

    //Get vertex attribute location
    gVertexPos2DLocation = glGetAttribLocation(gProgramId, "LVertexPos2D");
    if (gVertexPos2DLocation == -1)
    {
      cout << "LVertexPos2D is not a valid glsl program variable" << endl;
      return false;
    }

    glEnableVertexAttribArray(gVertexPos2DLocation);
    glViewport(0, 0, this->winWidth, this->winHeight);

    //Initialize clear color
    glClearColor(1.0f, 1.0f, 1.0f, 1.f);

    return true;
  
}

GLRenderer::~GLRenderer()
{
  if (gVertexPos2DLocation != -1) {
    glDisableVertexAttribArray(gVertexPos2DLocation);
  }
}

void GLRenderer::move(int distance)
{
  trianglePos = trianglePos + distance;
}

void GLRenderer::setViewport(int w, int h)
{
	glViewport(0, 0, w, h);
}

void GLRenderer::setWH(int w, int h)
{
	this->winWidth = w;
	this->winHeight = h;
}
