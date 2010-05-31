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
#include "dd/draw/ddDragTrackerTool.h"
#include "dd/draw/ddAbstractTool.h"


ddDragTrackerTool::ddDragTrackerTool(ddDrawingEditor *editor, ddIFigure *anchor)
:ddAbstractTool(editor){
	hasMovedValue=false;
	view = editor->view();
	anchorFigure = anchor;
}

ddDragTrackerTool::~ddDragTrackerTool(){
}

void ddDragTrackerTool::setLastCoords(int x, int y){
}

void ddDragTrackerTool::mouseDown(wxMouseEvent& event){
	ddAbstractTool::mouseDown(event);
	int x=event.GetPosition().x, y=event.GetPosition().y;

	setLastCoords(x,y);

	//TODO: shift pressed and toggle selection

	if(view->isFigureSelected(anchorFigure)){
		view->clearSelection();
		view->addToSelection(anchorFigure);
	}
}

void ddDragTrackerTool::mouseUp(wxMouseEvent& event){
	//DD-TODO: need this?
}

void ddDragTrackerTool::mouseDrag(wxMouseEvent& event){
	int x=event.GetPosition().x, y=event.GetPosition().y;	

	hasMovedValue = (abs (x - anchorX) > 4 || abs (y - anchorX) > 4);

			if (hasMoved()) {
				ddIFigure *tmp=NULL;
				ddIteratorBase *iterator=view->selectionFigures();
				while(iterator->HasNext())
				{
					tmp=(ddIFigure *)iterator->Next();
					tmp->moveBy(x - lastX, y - lastY);
				}
			}
			setLastCoords (x, y);
}

bool ddDragTrackerTool::hasMoved(){
	return hasMovedValue;
}

/*
ddAbstractTool::ddAbstractTool(ddDrawingEditor *editor){
	anchorX=0;
	anchorY=0;
	ownerEditor=editor;
}

ddAbstractTool::~ddAbstractTool(){
}

void ddAbstractTool::mouseDown(wxMouseEvent& event){
}

void ddAbstractTool::mouseUp(wxMouseEvent& event){
}

void ddAbstractTool::mouseMove(wxMouseEvent& event){
}

void ddAbstractTool::mouseDrag(wxMouseEvent& event){
}

void ddAbstractTool::keyDown(wxKeyEvent& event){
	setAnchorCoords(event.GetPosition().x,event.GetPosition().y);
}

void ddAbstractTool::keyUp(wxKeyEvent& event)
{
}

void ddAbstractTool::setAnchorCoords(int x, int y){
	anchorX=x;
	anchorY=y;
}

ddDrawingEditor* ddAbstractTool::getDrawingEditor(){
	return ownerEditor;
}
*/
