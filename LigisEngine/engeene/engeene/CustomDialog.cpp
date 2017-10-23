#include "CustomDialog.h"

CustomDialog::CustomDialog(wxWindow* parent)
	: wxDialog(parent, wxID_ANY, wxT("Input size of grid"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE)
{
	wxPanel* mainPanel = new wxPanel(this, -1);
	wxBoxSizer* mainLayout = new wxBoxSizer(wxVERTICAL);

	wxStaticText *sizeR = new wxStaticText(mainPanel, wxID_ANY, wxT("ROW:"));
	wxStaticText *sizeC = new wxStaticText(mainPanel, wxID_ANY, wxT("COL:"));
	TextR = new wxTextCtrl(mainPanel, wxID_ANY);
	TextC = new wxTextCtrl(mainPanel, wxID_ANY);

	wxButton * b = new wxButton(mainPanel, wxID_OK, _("OK"));

	wxBoxSizer* rBox = new wxBoxSizer(wxHORIZONTAL);
	rBox->Add(sizeR, 1);
	rBox->Add(TextR, 3);
	mainLayout->Add(rBox, 0, wxEXPAND | wxRIGHT | wxLEFT | wxUP, 10);

	wxBoxSizer* cBox = new wxBoxSizer(wxHORIZONTAL);
	cBox->Add(sizeC, 1);
	cBox->Add(TextC, 3);
	mainLayout->Add(cBox, 0, wxEXPAND | wxRIGHT | wxLEFT | wxUP, 10);

	mainLayout->Add(b, 0,wxALIGN_RIGHT| wxRIGHT| wxBOTTOM | wxUP,5);

	mainPanel->SetSizer(mainLayout);
}

wxString CustomDialog::GetTextRow() {
	return TextR->GetValue();
}
wxString CustomDialog::GetTextCol() {
	return TextC->GetValue();
}