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
#include <wx/scrolwin.h>
#include <wx/pen.h>

// App headers
#include "dd/draw/ddSelectAreaTool.h"
#include "dd/draw/ddAbstractTool.h"


ddSelectAreaTool::ddSelectAreaTool(ddDrawingEditor *editor)
:ddAbstractTool(editor){
	view = editor->view();
}

ddSelectAreaTool::~ddSelectAreaTool(){
}

void ddSelectAreaTool::mouseDown(wxMouseEvent& event){
	ddAbstractTool::mouseDown(event);
	if(!event.ShiftDown()){
		view->clearSelection();
	}
	int x=event.GetPosition().x, y=event.GetPosition().y;
	selectionRect.x=x;
	selectionRect.y=y;
	selectionRect.width=0;
	selectionRect.height=0;
	drawSelectionRect();
}

void ddSelectAreaTool::mouseUp(wxMouseEvent& event){
	ddAbstractTool::mouseUp(event);
	drawSelectionRect();
	selectFiguresOnRect(event.ShiftDown());
	view->disableSelRectDraw();
}

void ddSelectAreaTool::mouseDrag(wxMouseEvent& event){
	ddAbstractTool::mouseDrag(event);
	drawSelectionRect();
	int x=event.GetPosition().x, y=event.GetPosition().y;
	selectionRect.x=anchorX;
	selectionRect.y=anchorY;
	//selectionRect.width=abs(anchorX-x);
	//selectionRect.height=(anchorY-y);
	selectionRect.SetBottomRight(wxPoint(x,y));
	drawSelectionRect();
}

void ddSelectAreaTool::selectFiguresOnRect(bool shiftPressed){
	//DD-TODO: implement this function
}

void ddSelectAreaTool::drawSelectionRect(){
	view->setSelRect(selectionRect);
}

