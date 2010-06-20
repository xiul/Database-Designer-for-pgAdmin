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
#include "dd/draw/tools/ddSelectAreaTool.h"
#include "dd/draw/tools/ddAbstractTool.h"


ddSelectAreaTool::ddSelectAreaTool(ddDrawingEditor *editor)
:ddAbstractTool(editor){
	view = editor->view();
}

ddSelectAreaTool::~ddSelectAreaTool(){
}

//DD-TODO: fix bug select good from left to righ but no from right to left
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
	selectionRect.SetBottomRight(wxPoint(x,y));
	drawSelectionRect();
}

void ddSelectAreaTool::selectFiguresOnRect(bool shiftPressed){
	ddIFigure *figure;
	ddIteratorBase *iterator = getDrawingEditor()->model()->figuresInverseEnumerator();
	while(iterator->HasNext())
	{
		figure=(ddIFigure *)iterator->Next();
		if(selectionRect.Contains(figure->displayBox())){
			if(shiftPressed){
				view->toggleSelection(figure);
			}
			else
			{
				view->addToSelection(figure);
			}
		}
	}
	delete iterator;
}

void ddSelectAreaTool::drawSelectionRect(){
	view->setSelRect(selectionRect);
}

