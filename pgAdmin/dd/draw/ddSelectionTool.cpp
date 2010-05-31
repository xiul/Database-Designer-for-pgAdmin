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
#include "dd/draw/ddHandleTrackerTool.h"
#include "dd/draw/ddDragTrackerTool.h"


class ddDrawingView;
class ddDrawingEditor;

ddSelectionTool::ddSelectionTool(ddDrawingEditor *owner):
ddAbstractTool(owner){
	_delegateTool=NULL;
}

ddSelectionTool::~ddSelectionTool(){
}

void ddSelectionTool::mouseDown(wxMouseEvent& event){
	ddITool::mouseDown(event);

	ddDrawingView *view=getDrawingEditor()->view();
	int x=event.GetPosition().x, y=event.GetPosition().y;

	ddIHandle *handle = view->findHandle(x,y);
	if(handle){
		setDelegateTool(new ddHandleTrackerTool(ownerEditor,handle));
	}
	else
	{
		ddIFigure *figure = view->getDrawing()->findFigure(x,y);
		if(figure)
		{
			setDelegateTool(figure->CreateFigureTool(ownerEditor,new ddDragTrackerTool(getDrawingEditor(),figure)));
		}
		else
		{
			//DD-TODO: implement select tracker area
		}
	}

	ddITool *delegateTool = getDelegateTool();
	if (delegateTool) { 
			delegateTool->mouseDown(event);
	}
}

void ddSelectionTool::mouseUp(wxMouseEvent& event){
	ddITool *delegateTool = getDelegateTool();
	if (delegateTool) { 
			delegateTool->mouseUp(event);
	}
}

void ddSelectionTool::mouseMove(wxMouseEvent& event){
	
	ddDrawingView *view=getDrawingEditor()->view();
	int x=event.GetPosition().x, y=event.GetPosition().y;
	ddIHandle *handle = view->findHandle(x,y);

	if(handle){
		//DD-TODO: widget.GdkWindow.Cursor = handle.CreateCursor ();
	}
	else
	{
		ddIFigure *figure = view->getDrawing()->findFigure(x,y);
		if(figure)
		{
			//DD-TODO: widget.GdkWindow.Cursor = CursorFactory.GetCursorFromType (Gdk.CursorType.Fleur);
		}
		else
		{
			//DD-TODO: widget.GdkWindow.Cursor = null;
		}
	}
}

void ddSelectionTool::mouseDrag(wxMouseEvent& event){
	ddITool *delegateTool = getDelegateTool();
	if (delegateTool) { 
			delegateTool->mouseDrag(event);
	}
}

void ddSelectionTool::keyDown(wxKeyEvent& event){
	if(getDelegateTool()){
		getDelegateTool()->keyDown(event);
	}

	//DD-TODO: if (ev.Key == Gdk.Key.Delete) call deleteFigures
}

void ddSelectionTool::keyUp(wxKeyEvent& event)
{
	if(getDelegateTool()){
		getDelegateTool()->keyUp(event);
	}
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
