#include "MyGLCanvas.h"

MyGLCanvas::MyGLCanvas(wxPanel* parent, Editor *editor) :
	wxGLCanvas(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, wxT("GLCanvas"))
{
	m_context = new wxGLContext(this);
	int argc = 1;
	char* argv[1] = { wxString((wxTheApp->argv)[0]).char_str() };
	wxGLCanvas::SetCurrent(*m_context);

	mainPanel = parent;

	wxSize si = parent->GetSize();

	std::cout << si.GetWidth() << " " << si.GetHeight() << "\n";

	renderer = GLRendererEditor::getInstance();
	GLRendererEditor::getInstance()->setWH(si.GetWidth(), si.GetHeight());
	renderer->initGL("shaders/basic/vertext.shd", "shaders/basic/fragment.shd");
	editorRenderer = dynamic_cast<GLRendererEditor*>(renderer);
	editorRenderer->setMapSize(mapSizeR, mapSizeC);
	//editorRenderer->initTexture();
	editorRenderer->initTex("texture/tilefloor_old.png",1);
	editorRenderer->initTex("texture/tile_old.jpg",0);

	(*this).editor = editor;

	/*MeshVbo *mapVbo = new MapMeshVbo(mapSizeR, mapSizeC);
	mapVbo->loadData();
	renderer->addShape(mapVbo->getMeshName(), mapVbo);*/

	MeshVbo *circleV = new CircleMeshVbo();
	circleV->loadData();
	GLRendererEditor::getInstance()->addShape(circleV->getMeshName(), circleV);

	MeshVbo *line = new LineMeshVbo();
	line->loadData();
	GLRendererEditor::getInstance()->addShape(line->getMeshName(), line);

	MeshVbo *square = new SquareMeshVbo();
	square->loadData();
	GLRendererEditor::getInstance()->addShape(square->getMeshName(), square);

	MeshVbo *wall = new WallMeshVbo();
	wall->loadData();
	GLRendererEditor::getInstance()->addShape(wall->getMeshName(), wall);

}


void MyGLCanvas::render(wxPaintEvent& evt)
{
	
	wxPaintDC(this);
	
	//renderer->render();
	GLRendererEditor::getInstance()->initRender();
	if((*editor).getMap() != nullptr)
		(*editor).getMap()->draw();
	GLRendererEditor::getInstance()->endRender();

	SwapBuffers();
	
}

void MyGLCanvas::setViewport(wxSizeEvent& evt)
{
	wxSize si = this->GetSize();
	GLRendererEditor::getInstance()->setViewport(si.GetWidth(), si.GetHeight());
	this->Refresh();
}

void MyGLCanvas::OnMouseClick(wxMouseEvent &evt) {
	wxPoint pt = wxGetMousePosition();
	int x = pt.x - (*this).GetScreenPosition().x;
	int y = pt.y - (*this).GetScreenPosition().y;
	wxSize si = this->GetSize();
	int row = (*editor).getMap()->getRow();
	int col = (*editor).getMap()->getCol();
	int gridWidth = si.GetWidth() / col;
	int gridHeight = si.GetHeight() / row;
	int colNumber = x/ gridWidth;
	int rowNumber = (si.GetHeight()-y)/ gridHeight;
	//wxLogMessage("Juve %d %d", rowNumber, colNumber);
	(*editor).setCurrentGrid(rowNumber, colNumber);
	parentFrame->chB1->SetValue(editor->getCurrentGrid()->getWallTop());
	parentFrame->chB2->SetValue(editor->getCurrentGrid()->getWallBottom());
	parentFrame->chB3->SetValue(editor->getCurrentGrid()->getWallLeft());
	parentFrame->chB4->SetValue(editor->getCurrentGrid()->getWallRight());
	this->Refresh();
	//call setcurrentgrid at editor, send row and col, and refresh
}


void MyGLCanvas::pKey(int code) {
	switch (code)
	{
	case WXK_LEFT:
		editorRenderer->moveGrid(3);
	case WXK_RIGHT:
		editorRenderer->moveGrid(2);
		break;
	case WXK_UP:
		editorRenderer->moveGrid(0);
		break;
	case WXK_DOWN:
		editorRenderer->moveGrid(1);
		break;
	default:
		break;
	}
	
}

void MyGLCanvas::setRC(int r, int c) {
	mapSizeR = r;
	mapSizeC = c;
}

void MyGLCanvas::setParentFrame(Align* parent)
{
	parentFrame = parent;
}

Align * MyGLCanvas::getParentFrame()
{
	return parentFrame;
}
