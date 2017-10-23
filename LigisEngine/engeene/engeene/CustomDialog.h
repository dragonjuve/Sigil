#pragma once
#include<wx/wx.h>
class CustomDialog : public wxDialog
{
public:
	CustomDialog(wxWindow* parent);
	wxTextCtrl * TextR;
	wxTextCtrl * TextC;
	wxString GetTextRow();
	wxString GetTextCol();

};
