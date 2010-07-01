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


//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddSelectAreaTool::ddSelectAreaTool(ddDrawingEditor *editor)
:ddAbstractTool(editor){
	view = editor->view();
}

ddSelectAreaTool::~ddSelectAreaTool(){
}

//DD-TODO: fix bug select good from left to righ but no from right to left
void ddSelectAreaTool::mouseDown(ddMouseEvent& event){
	ddAbstractTool::mouseDown(event);
	if(!event.ShiftDown()){
		view->clearSelection();
	}
	if(event.LeftDown())
	{
		int x=event.GetPosition().x, y=event.GetPosition().y;
		selectionRect.x=x;
		selectionRect.y=y;
		selectionRect.width=0;
		selectionRect.height=0;
		drawSelectionRect();
	}
}

void ddSelectAreaTool::mouseUp(ddMouseEvent& event){
	ddAbstractTool::mouseUp(event);
	//hack-fix for bug when selecting figures from right to left
	if(event.LeftUp())
	{
		if( selectionRect.width < 0 ) 
		{
			int tmp;
			tmp=selectionRect.width;
			selectionRect.x += tmp;
			selectionRect.width=abs(tmp);

		}
		if( selectionRect.height < 0 )
		{
			int tmp;
			tmp=selectionRect.height;
			selectionRect.y += tmp;
			selectionRect.height=abs(tmp);
		}
		//end hack-fix 
		drawSelectionRect();
		selectFiguresOnRect(event.ShiftDown());
		view->disableSelRectDraw();
	}
}

void ddSelectAreaTool::mouseDrag(ddMouseEvent& event){
	ddAbstractTool::mouseDrag(event);
	if(event.LeftIsDown())
	{
		drawSelectionRect();
		int x=event.GetPosition().x, y=event.GetPosition().y;
		selectionRect.x=anchorX;
		selectionRect.y=anchorY;
		selectionRect.SetBottomRight(wxPoint(x,y));
		drawSelectionRect();
	}
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

