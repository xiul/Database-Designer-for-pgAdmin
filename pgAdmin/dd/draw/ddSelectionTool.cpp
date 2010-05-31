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

// App headers
#include "dd/draw/ddITool.h"
#include "dd/draw/ddSelectionTool.h"
#include "dd/draw/ddDrawingView.h"
#include "dd/draw/ddDrawingEditor.h"

ddSelectionTool::ddSelectionTool(ddDrawingEditor *owner):
ddAbstractTool(owner){
}

ddSelectionTool::~ddSelectionTool(){
}

void ddSelectionTool::mouseDown(wxMouseEvent& event){
	ddITool::mouseDown(event);
	
	ddDrawingView *view=getDrawingEditor()->view();
	int x=event.GetPosition().x, y=event.GetPosition().y;

	ddIHandle *handle = view->findHandle(x,y);
	if(handle){
		//DD-TODO: finish this after finish ddHandleTrackerTool
		//delegateTool = new ddHandleTrackerTool(owner,handle);
	}
	/* DD-TODO: selection and createfiguretool
			if (handle != null) {
				DelegateTool = new HandleTracker (Editor, handle);
			}
			else {
				IFigure figure = view.Drawing.FindFigure (ev.X, ev.Y);
				if (figure != null) {
					DelegateTool = figure.CreateFigureTool (Editor, new DragTracker (Editor, figure));
				} else {
					DelegateTool = new SelectAreaTracker (Editor);
				}
			}
	*/
	ddITool *delegateTool = getDelegateTool();
	if (delegateTool) { 
			delegateTool->mouseDown(event);
	}
}

void ddSelectionTool::mouseUp(wxMouseEvent& event){
}

void ddSelectionTool::mouseMove(wxMouseEvent& event){
}

void ddSelectionTool::mouseDrag(wxMouseEvent& event){
}

void ddSelectionTool::keyDown(wxKeyEvent& event){
	setAnchorCoords(event.GetPosition().x,event.GetPosition().y);
}

void ddSelectionTool::keyUp(wxKeyEvent& event)
{
}

void ddSelectionTool::setDelegateTool(ddITool *tool){
	if(_delegateTool){
		_delegateTool->deactivate();
	}
	_delegateTool = tool;
	
	if(_delegateTool){
		_delegateTool->activate();
	}
}

ddITool* ddSelectionTool::getDelegateTool(){
	return _delegateTool;
}

void ddSelectionTool::deleteFigures(ddDrawingView *view){
//DD-TODO: implement this
}
