#include "Align.h"



class main_app : public wxApp
{
public:
	bool OnInit()
	{
		Align* frame = new Align("Editor");
		frame->Show();
		return true;
	}
};

IMPLEMENT_APP(main_app);



