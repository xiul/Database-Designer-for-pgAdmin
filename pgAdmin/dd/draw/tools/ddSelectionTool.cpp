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
#include "dd/draw/tools/ddITool.h"
#include "dd/draw/tools/ddSelectionTool.h"
#include "dd/draw/main/ddDrawingView.h"
#include "dd/draw/main/ddDrawingEditor.h"
#include "dd/draw/tools/ddHandleTrackerTool.h"
#include "dd/draw/tools/ddDragTrackerTool.h"
#include "dd/draw/tools/ddSelectAreaTool.h"


//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


class ddDrawingView;
class ddDrawingEditor;

ddSelectionTool::ddSelectionTool(ddDrawingEditor *owner):
ddAbstractTool(owner){
	_delegateTool=NULL;
}

ddSelectionTool::~ddSelectionTool(){
	if(_delegateTool)
		delete _delegateTool;
}

void ddSelectionTool::mouseDown(ddMouseEvent& event){
	ddITool::mouseDown(event);

	ddDrawingView *view=getDrawingEditor()->view();
	int x=event.GetPosition().x, y=event.GetPosition().y;

	ddIHandle *handle = view->findHandle(x,y);
	if(handle){
		setDelegateTool(new ddHandleTrackerTool(getDrawingEditor(),handle));
	}
	else
	{
//		if(event.LeftDown())
//		{
			ddIFigure *figure = view->getDrawing()->findFigure(x,y);
			if(figure)
			{
				setDelegateTool(figure->CreateFigureTool(getDrawingEditor(),new ddDragTrackerTool(getDrawingEditor(),figure)));
			}
			else
			{
				setDelegateTool(new ddSelectAreaTool(getDrawingEditor()));
			}
//		}
/*		else
		{
			setDelegateTool(NULL);
		}*/
	}

	ddITool *delegateTool = getDelegateTool();
	if (delegateTool) { 
			delegateTool->mouseDown(event);
	}
}

void ddSelectionTool::mouseUp(ddMouseEvent& event){
	ddAbstractTool::mouseUp(event);
	ddITool *delegateTool = getDelegateTool();
	if (delegateTool) { 
			delegateTool->mouseUp(event);
	}
}

void ddSelectionTool::mouseMove(ddMouseEvent& event){
	ddAbstractTool::mouseMove(event);
	ddDrawingView *view=getDrawingEditor()->view();
	int x=event.GetPosition().x, y=event.GetPosition().y;
	ddIHandle *handle = view->findHandle(x,y);

	if(handle){
		//DD-TODO: widget.GdkWindow.Cursor = handle.CreateCursor ();
		//view->SetCursor(wxCursor(wxCURSOR_MIDDLE_BUTTON));
		
		view->SetCursor(handle->createCursor());
		//view->SetCursor(wxCursor(wxCURSOR_SIZENS));
	}
	else
	{
		ddIFigure *figure = view->getDrawing()->findFigure(x,y);
		if(figure)
		{
			//DD-TODO: change cursor for a nice one
			view->SetCursor(wxCursor(wxCURSOR_HAND));
		}
		else
		{
			view->SetCursor(wxCursor(wxCURSOR_ARROW));
		}
	}
}

void ddSelectionTool::mouseDrag(ddMouseEvent& event){
	ddAbstractTool::mouseDrag(event);
	ddITool *delegateTool = getDelegateTool();
	if (delegateTool) { 
			delegateTool->mouseDrag(event);
	}
}

void ddSelectionTool::keyDown(wxKeyEvent& event){
	if(getDelegateTool()){
		getDelegateTool()->keyDown(event);
	}
	if(event.GetKeyCode() == WXK_DELETE){
		deleteFigures(getDrawingEditor()->view());
	}
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
		delete _delegateTool;
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
	view->clearSelection();
	view->getDrawing()->deleteFigures();
}
