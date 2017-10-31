#pragma once
#include <wx/wx.h>
#include "Editor.h"
class MyGLCanvas;
class Align : public wxFrame
{
public:
	Align(const wxString& title);
	void OnExit(wxCommandEvent & evt);
	void OnNew(wxCommandEvent & evt);
	void OnSave(wxCommandEvent & evt);
	void OnOpen(wxCommandEvent & evt);
	void OnGridChange(wxCommandEvent &evt);
	void OnWallChange(wxCommandEvent &evt);
	wxCheckBox *chB1;
	wxCheckBox *chB2;
	wxCheckBox *chB3;
	wxCheckBox *chB4;
	int rowMax;
	int colMax;
	DECLARE_EVENT_TABLE()
private:
	wxMenuBar* pMenuBar;
	wxMenu* pFileMenu;
	wxMenu* pHelpMenu;
	MyGLCanvas *glcanvas = nullptr;
	Editor *editor;
	GLRendererEditor *rendererEditor;
	
};

enum {
	ID_BUTTON_A = wxID_HIGHEST + 1,
	ID_BUTTON_B,
	ID_BUTTON_TOP,
	ID_BUTTON_BOTTOM,
	ID_BUTTON_LEFT,
	ID_BUTTON_RIGHT,
};
