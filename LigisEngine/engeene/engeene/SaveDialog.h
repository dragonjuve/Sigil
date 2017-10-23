#pragma once
#include<wx/wx.h>
class SaveDialog : public wxDialog
{
public:
	SaveDialog(wxWindow* parent);
	wxTextCtrl * fileName;
	wxString GetFileName();

};