#pragma once
#include "wx/wx.h"
#include <GL\glew.h>
#include "wx/glcanvas.h"
#include "GLRenderer.h"
#include "GLRendererEditor.h"
#include "MapMeshVbo.h"
#include "CircleMeshVbo.h"
#include "LineMeshVbo.h"
#include "SquareMeshVbo.h"
#include "WallMeshVbo.h"
#include "Editor.h"
#include "Align.h"

class MyGLCanvas : public wxGLCanvas
{
	wxGLContext*	m_context;
	wxPanel* mainPanel;
	GLRenderer* renderer = nullptr;
	Editor* editor;
	Align* parentFrame;
	int mapSizeR = 3;
	int mapSizeC = 3;

public:
	MyGLCanvas(wxPanel* parent, Editor* editor);
	void render(wxPaintEvent& evt);
	void setViewport(wxSizeEvent& evt);
	void OnMouseClick(wxMouseEvent &evt);
	void pKey(int code);
	void setRC(int r,int c);
	void setParentFrame(Align* parent);
	Align* getParentFrame();
	GLRendererEditor* editorRenderer = nullptr;
	DECLARE_EVENT_TABLE()
};