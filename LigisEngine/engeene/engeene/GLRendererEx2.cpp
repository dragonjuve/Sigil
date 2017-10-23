#include "GLRenderer.h"

GLRendererEx2::GLRendererEx2()
{
}

bool GLRendererEx2::initialize(string vertexShaderFile, string fragmentShaderFile)
{
  //Success flag
  bool success = true;

  //Generate program
  gProgramId = glCreateProgram();

  //Create vertex shader
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

  //Get vertex source
  const GLchar* vertexShaderSource[] =
  {
    "#version 330\n in vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
  };

  //Set vertex source
  glShaderSource(vertexShader, 1, vertexShaderSource, NULL);

  //Compile vertex source
  glCompileShader(vertexShader);

  //Check vertex shader for errors
  GLint vShaderCompiled = GL_FALSE;
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
  if (vShaderCompiled != GL_TRUE)
  {
    printf("Unable to compile vertex shader %d!\n", vertexShader);
    //printShaderLog(vertexShader);
    success = false;
  }
  else
  {
    //Attach vertex shader to program
    glAttachShader(gProgramId, vertexShader);


    //Create fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    //Get fragment source
    const GLchar* fragmentShaderSource[] =
    {
      "#version 330\n out vec4 LFragment; void main() { LFragment = vec4( 0.0, 0.5, 1.0, 1.0 ); }"

    };

    //Set fragment source
    glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);

    //Compile fragment source
    glCompileShader(fragmentShader);

    //Check fragment shader for errors
    GLint fShaderCompiled = GL_FALSE;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
    if (fShaderCompiled != GL_TRUE)
    {
      printf("Unable to compile fragment shader %d!\n", fragmentShader);
      //printShaderLog(fragmentShader);
      success = false;
    }
    else
    {
      //Attach fragment shader to program
      glAttachShader(gProgramId, fragmentShader);


      //Link program
      glLinkProgram(gProgramId);

      //Check for errors
      GLint programSuccess = GL_TRUE;
      glGetProgramiv(gProgramId, GL_LINK_STATUS, &programSuccess);
      if (programSuccess != GL_TRUE)
      {
        printf("Error linking program %d!\n", gProgramId);
        printProgramLog(gProgramId);
        success = false;
      }
      else
      {
        //Get vertex attribute location
        gVertexPos2DLocation = glGetAttribLocation(gProgramId, "LVertexPos2D");
        if (gVertexPos2DLocation == -1)
        {
          printf("LVertexPos2D is not a valid glsl program variable!\n");
          success = false;
        }
        else
        {
          //Initialize clear color
          glClearColor(0.f, 0.f, 0.f, 1.f);

          //VBO data
          GLfloat vertexData[] =
          {
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f,  0.5f,
            -0.5f,  0.5f
          };


          //Create VBO
          glGenBuffers(1, &gVBO);
          glBindBuffer(GL_ARRAY_BUFFER, gVBO);
          glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

          glEnableVertexAttribArray(gVertexPos2DLocation);
          glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);
          glUseProgram(gProgramId);

          // Set background color as cornflower blue
          glClearColor(0.39f, 0.58f, 0.93f, 1.f);

        }
      }
    }
  }

  return success;

}

void GLRendererEx2::render()
{

  // Clear color buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // Update window with OpenGL rendering
  

  glDrawArrays(GL_TRIANGLES, 0, 3);



}