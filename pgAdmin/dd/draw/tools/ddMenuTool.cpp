//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbView.cpp 8268 2010-04-15 21:49:27Z xiul $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// ddDrawing.cpp - Container for figures that send changed events to Listeners whenever 
//	a part of its area was invalidated. Using the design pattern observer to decouple the
//	Drawing from its views and to enable multiple views .
//
//////////////////////////////////////////////////////////////////////////

#include "pgAdmin3.h"

// wxWindows headers
#include <wx/wx.h>
#include <wx/textctrl.h>
#include <wx/choicdlg.h>

// App headers
#include "dd/draw/tools/ddMenuTool.h"
#include "dd/draw/figures/ddIFigure.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


class ddDrawingEditor;

//Allow Edition of textTool (double click) or show a menu to modifiy in someway text (right click).
ddMenuTool::ddMenuTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt):
ddFigureTool(editor,fig,dt)
{
	menuFigure = (ddAbstractMenuFigure*) this->getFigure();
	editor->view()->setMenuToolFigure(NULL);
}

ddMenuTool::~ddMenuTool()
{
}

/*void ddSimpleTextTool::calculateSizeEntry(ddDrawingView *view)
{
	if(edit)
	{
	//	edit->SetPosition(txtFigure->displayBox().GetPosition());
		ddPoint p=txtFigure->displayBox().GetPosition();
		view->CalcScrolledPosition(p.x,p.y,&p.x,&p.y);
		edit->SetPosition(p);
		edit->SetSize(txtFigure->displayBox().GetSize());
		//DD-TODO: avoid in a future twin function in DrawingView because tool hack
	}
}*/

void ddMenuTool::mouseDown(ddMouseEvent& event)
{	
	setAnchorCoords(event.GetPosition().x,event.GetPosition().y);

	

	if(menuFigure->menuEnabled() && event.RightDown())
	{
                wxMenu menu;
				getDrawingEditor()->view()->setMenuToolFigure(menuFigure);
				getDrawingEditor()->view()->setTextPopUpList(menuFigure->popupStrings(),menu);
				ddPoint p=event.GetPosition();
				event.getView()->CalcScrolledPosition(p.x,p.y,&p.x,&p.y);
				getDrawingEditor()->view()->PopupMenu(&menu, p);
		return;
	}


/*	if(event.LeftDClick())
	{
		getDrawingEditor()->view()->setMenuToolFigure(menuFigure);
		showEdit = true;
		edit->ChangeValue(txtFigure->getText()); //Same as SetValue but don't generated wxEVT_COMMAND_TEXT_UPDATED event
		calculateSizeEntry(event.getView());
		edit->SetFocus();
		edit->Show();
		return;
	}*/
	getDefaultTool()->mouseDown(event);
}

void ddMenuTool::activate()
{
	ddFigureTool::activate();
}

void ddMenuTool::deactivate()
{
	//getDrawingEditor()->view()->setSimpleTextToolFigure(NULL);
	ddFigureTool::deactivate();
}

void ddMenuTool::mouseDrag(ddMouseEvent& event)
{
		getDefaultTool()->mouseDrag(event);
}

void ddMenuTool::OnTextPopupClick(wxCommandEvent& event)
{
	menuFigure->OnTextPopupClick(event);
}
