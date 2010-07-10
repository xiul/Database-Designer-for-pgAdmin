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
#include "dd/draw/tools/ddSimpleTextTool.h"
#include "dd/draw/figures/ddSimpleTextFigure.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


class ddDrawingEditor;

//Allow Edition of textTool (double click) or show a menu to modifiy in someway text (right click).
ddSimpleTextTool::ddSimpleTextTool(ddDrawingEditor *editor, ddIFigure *fig, ddITool *dt):
ddFigureTool(editor,fig,dt)
{
	showEdit = false;
	//DD-TODO: set this value: edit.SetFont();  and fix layout and fix ID of edit because it should be a constant
	txtFigure = ((ddSimpleTextFigure *)this->getFigure());
	editor->view()->setSimpleTextToolFigure(NULL);
	edit = getDrawingEditor()->view()->getSimpleTextToolEdit();
	calculateSizeEntry(editor->view());
}

ddSimpleTextTool::~ddSimpleTextTool()
{
}

void ddSimpleTextTool::calculateSizeEntry(ddDrawingView *view)
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
}

void ddSimpleTextTool::mouseDown(ddMouseEvent& event)
{	
	setAnchorCoords(event.GetPosition().x,event.GetPosition().y);

	

	if(txtFigure->menuEnabled() && event.RightDown())
	{
                wxMenu menu;
				getDrawingEditor()->view()->setSimpleTextToolFigure(txtFigure);
				getDrawingEditor()->view()->setTextPopUpList(txtFigure->popupStrings(),menu);
				ddPoint p=event.GetPosition();
				event.getView()->CalcScrolledPosition(p.x,p.y,&p.x,&p.y);
				getDrawingEditor()->view()->PopupMenu(&menu, p);
		return;
	}


	if(event.LeftDClick())
	{
		getDrawingEditor()->view()->setSimpleTextToolFigure(txtFigure);
		showEdit = true;
		edit->ChangeValue(txtFigure->getText()); //Same as SetValue but don't generated wxEVT_COMMAND_TEXT_UPDATED event
		calculateSizeEntry(event.getView());
		edit->SetFocus();
		edit->Show();
		return;
	}
	getDefaultTool()->mouseDown(event);
}

void ddSimpleTextTool::activate()
{
	showEdit = false;
	ddFigureTool::activate();
}

void ddSimpleTextTool::deactivate()
{
	if(edit)
	{
		edit->Hide();  //I can't delete it because view is the owner of this object
		getDrawingEditor()->view()->setSimpleTextToolFigure(NULL);
	}
	ddFigureTool::deactivate();
}

void ddSimpleTextTool::mouseDrag(ddMouseEvent& event)
{
	if(!showEdit)
	{
		getDefaultTool()->mouseDrag(event);
	}
}

void ddSimpleTextTool::OnTextPopupClick(wxCommandEvent& event)
{
	txtFigure->OnTextPopupClick(event);
}