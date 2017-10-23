/**
This file serves as a main program which will load a main SDL2 windows 
and create other rendering objects.

*/
//Must include glew.h first thing even though we donot
//use openGL function in the main to avoid compilation error

#include <GL\glew.h>

// SDL headers
#include <SDL_main.h>
#include <SDL.h>
#include <SDL_opengl.h>


#include <iostream>
#include <string>
#include "GLRenderer.h"
#include "GLRendererColor.h"
#include "GLRendererEditor.h"
#include "SquareMeshVbo.h"
#include "TrangleMeshVbo.h"
#include "CircleMeshVbo.h"
#include "MapMeshVbo.h"

using namespace std;
bool quit;

SDL_Window* window;
SDL_GLContext glContext;
SDL_Event sdlEvent;
GLRenderer *renderer = nullptr;
GLRendererEditor *editorRenderer = nullptr;

string windowTitle;
int width = 600, height = 600, mapSizeR = 9, mapSizeC = 9;

int main(int argc, char *argv[])
{
  windowTitle = "Hello World";
  quit = false;

  //Use OpenGL 3.1 core
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  // Initialize video subsystem
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    // Display error message
    cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
    return false;
  }
  else
  {
    // Create window
    window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
      // Display error message
      cout << "Window could not be created! SDL_Error" << SDL_GetError() << endl;
      return false;
    }
    else
    {
      //If window is created successfully, create OpenGL context

      glContext = SDL_GL_CreateContext(window);

      if (glContext == NULL)
      {
        // Display error message
        cout << "OpenGL context could not be created! SDL Error: " << SDL_GetError() << endl;
        return false;
      }
      else
      {
        if (SDL_GL_SetSwapInterval(1) < 0)
        {
          cout << "Warning: Unable to set VSync! SDL Error: " << SDL_GetError() << endl;
        }

        //renderer = new GLRenderer(width,height);
        //renderer->initGL("shaders/basic/vertext.shd", "shaders/basic/fragment.shd");

        //renderer = new GLRendererColor(width,height);
        //renderer->initGL("shaders/color/vertext.shd", "shaders/color/fragment.shd");

		renderer = new GLRendererEditor(width, height);
		renderer->initGL("shaders/basic/vertext.shd", "shaders/basic/fragment.shd");
		editorRenderer = dynamic_cast<GLRendererEditor*>(renderer);
		editorRenderer->setMapSize(mapSizeR,mapSizeC);
		//editorRenderer->initTexture();
		editorRenderer->initTex("texture/prinny.jpg");
		editorRenderer->initTex("texture/tile.jpg");

		MeshVbo *mapVbo = new MapMeshVbo(mapSizeR, mapSizeC);
		mapVbo->loadData();
		renderer->addShape(mapVbo->getMeshName(), mapVbo);

		MeshVbo *circleV = new CircleMeshVbo();
		circleV->loadData();
		renderer->addShape(circleV->getMeshName(),circleV);

        /*MeshVbo *squareVbo = new SquareMeshVbo();
        squareVbo->loadData();
        renderer->addShape(squareVbo->getMeshName(),squareVbo);
        MeshVbo *triangleVbo = new TriangleMeshVbo();
        triangleVbo->loadData();
        renderer->addShape(triangleVbo->getMeshName(), triangleVbo);*/

      }
    }
  }

  // Game loop
  while (!quit)
  {
    while (SDL_PollEvent(&sdlEvent) != 0)
    {
      // Esc button is pressed
      if (sdlEvent.type == SDL_QUIT)
      {
        quit = true;
      }
	  else if (sdlEvent.button.state == SDL_PRESSED)
	  {
		  cout << "X:" << sdlEvent.button.x;
	  }
      else if (sdlEvent.type == SDL_KEYDOWN) {
        switch (sdlEvent.key.keysym.sym)
        {
          case SDLK_LEFT: editorRenderer->moveGrid(3); break;
          case SDLK_RIGHT:editorRenderer->moveGrid(2); break;
		  case SDLK_UP:   editorRenderer->moveGrid(0); break;
		  case SDLK_DOWN: editorRenderer->moveGrid(1); break;
		  case SDLK_SPACE:editorRenderer->changeMapColor(); break;
		  case SDLK_1:	  editorRenderer->setCurrentColor(0); break;
		  case SDLK_2:	  editorRenderer->setCurrentColor(1); break;
		  case SDLK_3:	  editorRenderer->setCurrentColor(2); break;
		  case SDLK_4:	  editorRenderer->setCurrentColor(3); break;
		  case SDLK_5:	  editorRenderer->setCurrentColor(4); break;
		  case SDLK_6:	  editorRenderer->setCurrentTexture(1); break;
		  case SDLK_7:	  editorRenderer->setCurrentTexture(2); break;
		  case SDLK_k: editorRenderer->saveMap();
		  case SDLK_o: editorRenderer->loadMap();
        }
      }
    }
    renderer->render();

    SDL_GL_SwapWindow(window);
  }

  //Destroy window
  SDL_DestroyWindow(window);
  window = NULL;

  //Quit SDL subsystems
  SDL_Quit();

  return 0;
}