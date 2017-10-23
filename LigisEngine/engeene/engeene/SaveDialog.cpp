#include"SaveDialog.h"

SaveDialog::SaveDialog(wxWindow* parent) : wxDialog(parent, wxID_ANY, wxT("Input the file name"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE) {
	wxPanel* mainPanel = new wxPanel(this, -1);
	wxBoxSizer* mainLayout = new wxBoxSizer(wxVERTICAL);

	wxStaticText *filepanel = new wxStaticText(mainPanel, wxID_ANY, wxT("Name:"));
	fileName = new wxTextCtrl(mainPanel, wxID_ANY);
	wxButton * ok = new wxButton(mainPanel, wxID_OK, _("OK"));

	wxBoxSizer* rBox = new wxBoxSizer(wxHORIZONTAL);
	rBox->Add(filepanel, 1);
	rBox->Add(fileName, 3);
	mainLayout->Add(rBox, 0, wxEXPAND | wxRIGHT | wxLEFT | wxUP, 10);

	mainLayout->Add(ok, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM | wxUP, 5);

	mainPanel->SetSizer(mainLayout);
}

wxString SaveDialog::GetFileName() {
	return (*fileName).GetValue();
}