#include "Align.h"
#include "CustomDialog.h"
#include "SaveDialog.h"
#include "MyGlCanvas.h"
#include <string>
Align::Align(const wxString& title)
	: wxFrame(NULL, -1, title, wxPoint(-1, -1), wxSize(800, 600))
{
	editor = new Editor();
	
	pMenuBar = new wxMenuBar();
	// File Menu
	pFileMenu = new wxMenu();
	pFileMenu->Append(wxID_NEW, _T("&New"), _T("New"));
	pFileMenu->Append(wxID_OPEN, _T("&Open"), _T("Opens an existing file"));
	pFileMenu->Append(wxID_SAVE, _T("&Save"), _T("Save the content"));
	pFileMenu->AppendSeparator();
	pFileMenu->Append(wxID_EXIT, _T("&Quit"), _T("Quit the application"));
	pMenuBar->Append(pFileMenu, _T("&File"));
	// About menu
	pHelpMenu = new wxMenu();
	pHelpMenu->Append(wxID_ABOUT, _T("&About"), _T("Shows information about the application"));
	pMenuBar->Append(pHelpMenu, _T("&Help"));

	SetMenuBar(pMenuBar);
	CreateStatusBar(3);
	SetStatusText(wxT("Ready"), 0);

	wxPanel* mainPanel = new wxPanel(this, -1);
	wxBoxSizer* mainLayout = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* propertyLayout = new wxBoxSizer(wxVERTICAL);
	wxStaticText *propertyLabel = new wxStaticText(mainPanel, wxID_ANY, wxT("Tile Property"));
	wxCheckBox * objectiveCheck = new wxCheckBox(mainPanel, wxID_ANY, "objective point");
	wxCheckBox * movableCheck = new wxCheckBox(mainPanel, wxID_ANY, "blocked grid");

	propertyLayout->Add(propertyLabel, 0, wxTOP, 10);
	propertyLayout->Add(objectiveCheck, 0, wxTOP, 10);
	propertyLayout->Add(movableCheck, 0, wxTOP, 10);


	mainLayout->Add(propertyLayout, 0, wxEXPAND | wxLEFT, 10);

	wxPanel* mPanel = new wxPanel(mainPanel, -1);
	mainLayout->Add(mPanel, 0, wxRIGHT, 10);

	wxBoxSizer* mid = new wxBoxSizer(wxVERTICAL);
	wxStaticText *screenLabel = new wxStaticText(mainPanel, wxID_ANY, wxT("Screen"));
	glcanvas = new MyGLCanvas(mainPanel, editor);
	glcanvas->setParentFrame(this);
	mid->Add(screenLabel, 0, wxTOP | wxLEFT, 10);
	mid->Add(glcanvas, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 10);
	mainLayout->Add(mid, 3, wxEXPAND, 0);
	mid->Layout();
	mainLayout->Layout();

	//glcanvas->setViewport();
	//mainLayout->Add(glcanvas, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP | wxBOTTOM, 10);

	wxBoxSizer* spriteLayout = new wxBoxSizer(wxVERTICAL);
	wxStaticText *spriteLabel = new wxStaticText(mainPanel, wxID_ANY, wxT("Grid"));
	wxPanel *spritePanel = new wxPanel();
	wxImage image;
	wxBitmap bitmap1;
	wxBitmap bitmap2;
	image.AddHandler(new wxPNGHandler);
	image.AddHandler(new wxJPEGHandler);
	//bitmap1.SetHandle(new wxPNGHandler);
	//bitmap2.SetHandle(new wxJPEGHandler);
	bitmap1.LoadFile("texture/tilefloor.png", wxBITMAP_TYPE_PNG);
	bitmap2.LoadFile("texture/tile.jpg", wxBITMAP_TYPE_JPEG);
	wxBitmapButton *b1 = new wxBitmapButton(mainPanel, ID_BUTTON_A, bitmap1, wxDefaultPosition, wxSize(50, 50));
	wxBitmapButton *b2 = new wxBitmapButton(mainPanel, ID_BUTTON_B, bitmap2, wxDefaultPosition, wxSize(50, 50));
	//wxButton *b1 = new wxButton(mainPanel, ID_BUTTON_A, wxT("A"));
	//wxButton *b2 = new wxButton(mainPanel, ID_BUTTON_B, wxT("B"));
	wxStaticText *wallLabel = new wxStaticText(mainPanel, wxID_ANY, wxT("Wall"));
	chB1 = new wxCheckBox(mainPanel, ID_BUTTON_TOP, "Top");
	chB2 = new wxCheckBox(mainPanel, ID_BUTTON_BOTTOM, "Bottom");
	chB3 = new wxCheckBox(mainPanel, ID_BUTTON_LEFT, "Left");
	chB4 = new wxCheckBox(mainPanel, ID_BUTTON_RIGHT, "Right");

	spriteLayout->Add(spriteLabel, 0, wxTOP, 10);
	spriteLayout->Add(b1, 0, wxTOP, 10);
	spriteLayout->Add(b2, 0, wxTOP, 10);
	spriteLayout->Add(wallLabel, 0, wxTOP, 30);
	spriteLayout->Add(chB1, 0, wxTOP, 10);
	spriteLayout->Add(chB2, 0, wxTOP, 10);
	spriteLayout->Add(chB3, 0, wxTOP, 10);
	spriteLayout->Add(chB4, 0, wxTOP, 10);
	mainLayout->Add(spriteLayout, 1, wxEXPAND | wxLEFT | wxRIGHT, 10);


	mainPanel->SetSizer(mainLayout);
	Centre();
	glcanvas->SetFocus();
}


void Align::OnExit(wxCommandEvent &evt) {
	Close();
}

void Align::OnSave(wxCommandEvent & evt) {
	
	SaveDialog sa(this);
	long save = sa.ShowModal();
	if (save == wxID_OK) {
		wxLogMessage("Save");
		FILE *fptr;
		fptr = fopen("D:/LigisEngine/LigisEngine/engeene/engeene/Save/save1.txt", "w");
		fprintf(fptr, "%d %d\n", rowMax, colMax);
		//grids[i][j].getGridType().compare("A") == 0
		for (int i = rowMax-1; i >= 0; i--) {
			for (int j = 0; j < colMax; j++) {
				if ((*editor).getGridFrom(i, j)->getGridType().compare("A") == 0) {
					fprintf(fptr, "%c", 'A');
				}
				else if ((*editor).getGridFrom(i, j)->getGridType().compare("B") == 0) {
					fprintf(fptr, "%c", 'B');
				}
				else {
					fprintf(fptr, "%c", 'C');//C means none
				}
			}
			fprintf(fptr, "\n");
		}
		/*for (int i = 0; i < rowMax; i++) {
			for (int j = 0; j < colMax; j++) {
				if ((*editor).getGridFrom(i, j)->getWallTop() == true) {
					fprintf(fptr, "T ");
				}
				if ((*editor).getGridFrom(i, j)->getWallBottom() == true) {
					fprintf(fptr, "B ");
				}
				if ((*editor).getGridFrom(i, j)->getWallLeft() == true) {
					fprintf(fptr, "L ");
				}
				if ((*editor).getGridFrom(i, j)->getWallRight() == true) {
					fprintf(fptr, "R ");
				}
			}
			fprintf(fptr, "\n");
		}*/
		fclose(fptr);
	}
}

void Align::OnOpen(wxCommandEvent & evt) {
	FILE *fptr, *fptr2;
	char alphabet;
	fptr = fopen("D:/LigisEngine/LigisEngine/engeene/engeene/Save/save1.txt", "r");
	fscanf(fptr, "%i", &rowMax);
	fscanf(fptr, "%i", &colMax);
	editor->createNewMap(rowMax, colMax);
	wxLogMessage("%i %i", rowMax, colMax);
	fscanf(fptr, "%c", &alphabet);
	for (int i = 0; i < rowMax; i++) {
		for (int j = 0; j < colMax; j++) {
			fscanf(fptr, "%c", &alphabet);
			if (alphabet == 'A') {
				(*editor).getGridFrom(i, j)->setGridType("A");
			}
			else if (alphabet == 'B') {
				(*editor).getGridFrom(i, j)->setGridType("B");
			}
		}
		fscanf(fptr, "%c", &alphabet);
	}
	this->Refresh();
	fclose(fptr);
}


void Align::OnNew(wxCommandEvent & evt) {
	CustomDialog di(this);
	long ok = di.ShowModal();
	if (ok == wxID_OK) {
		wxString r, c;
		r = di.GetTextRow();
		c = di.GetTextCol();
		rowMax = wxAtoi(r);
		colMax = wxAtoi(c);
		//glcanvas->setRC(wxAtoi(Y), wxAtoi(X));
		editor->createNewMap(wxAtoi(r), wxAtoi(c));
		this->Refresh();
	}
	
}

void Align::OnGridChange(wxCommandEvent &evt){
	if (evt.GetId() == ID_BUTTON_A) {
		(*editor).getCurrentGrid()->setGridType("A");
		this->Refresh();
	}
	else if (evt.GetId() == ID_BUTTON_B) {
		(*editor).getCurrentGrid()->setGridType("B");
		this->Refresh();
	}
	wxLogMessage("grid is %i %i type is type %s",(*editor).getCurrentGrid()->getRow(), (*editor).getCurrentGrid()->getCol(),(*editor).getCurrentGrid()->getGridType());
}

void Align::OnWallChange(wxCommandEvent &evt) {
	//GetCurrrentGridFromEditor and set property
	if (evt.GetId() == ID_BUTTON_TOP) {
		if (evt.IsChecked()) {
			(*editor).getCurrentGrid()->setWallTop(true);
			//wxLogMessage("Top checked");
		}
		else {
			(*editor).getCurrentGrid()->setWallTop(false);
			//wxLogMessage("Top unchecked");
		}
			

	}
	else if (evt.GetId() == ID_BUTTON_BOTTOM) {
		if (evt.IsChecked()) {
			(*editor).getCurrentGrid()->setWallBottom(true);
			//wxLogMessage("Bottom");
		}
		else {
			(*editor).getCurrentGrid()->setWallBottom(false);
		}

	}
	else if (evt.GetId() == ID_BUTTON_LEFT) {
		if (evt.IsChecked()) {
			(*editor).getCurrentGrid()->setWallLeft(true);
			//wxLogMessage("Left");
		}
		else {
			(*editor).getCurrentGrid()->setWallLeft(false);
		}
		

	}
	else if (evt.GetId() == ID_BUTTON_RIGHT) {
		if (evt.IsChecked()) {
			(*editor).getCurrentGrid()->setWallRight(true);
			//wxLogMessage("Right");
		}
		else {
			(*editor).getCurrentGrid()->setWallRight(false);
		}
		

	}
	Refresh();
}

BEGIN_EVENT_TABLE(Align, wxFrame)
EVT_MENU(wxID_EXIT, Align::OnExit)
EVT_MENU(wxID_NEW, Align::OnNew)
EVT_MENU(wxID_SAVE, Align::OnSave)
EVT_MENU(wxID_OPEN, Align::OnOpen)
EVT_BUTTON(ID_BUTTON_A, Align::OnGridChange)
EVT_BUTTON(ID_BUTTON_B, Align::OnGridChange)
EVT_CHECKBOX(ID_BUTTON_TOP, Align::OnWallChange)
EVT_CHECKBOX(ID_BUTTON_BOTTOM, Align::OnWallChange)
EVT_CHECKBOX(ID_BUTTON_LEFT, Align::OnWallChange)
EVT_CHECKBOX(ID_BUTTON_RIGHT, Align::OnWallChange)
END_EVENT_TABLE()
BEGIN_EVENT_TABLE(MyGLCanvas, wxGLCanvas)
EVT_SIZE(MyGLCanvas::setViewport)
EVT_PAINT(MyGLCanvas::render)
EVT_LEFT_DOWN(MyGLCanvas::OnMouseClick)

END_EVENT_TABLE()