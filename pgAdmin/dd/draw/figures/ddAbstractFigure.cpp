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
#include <wx/dcbuffer.h>
#include <wx/pen.h>

// App headers
#include "dd/draw/figures/ddAbstractFigure.h"
#include "dd/draw/figures/ddIFigure.h"
#include "dd/draw/utilities/ddArrayCollection.h"

ddAbstractFigure::ddAbstractFigure(){

}

ddAbstractFigure::~ddAbstractFigure(){

}

bool ddAbstractFigure::canConnect (){
return true;
}

bool ddAbstractFigure::includes(ddIFigure figure){
	return false;	
	//DD-TODO: implement this return (this==figure);
}

void ddAbstractFigure::draw(wxBufferedDC& context){
	basicDraw(context);
}

void ddAbstractFigure::basicDraw(wxBufferedDC& context){
	context.SetPen(*wxGREEN_PEN);
	context.SetBrush(wxBrush (wxColour(208, 208, 208),wxSOLID));
	context.DrawRectangle(basicDisplayBox);
}

void ddAbstractFigure::drawSelected(wxBufferedDC& context){
		basicDrawSelected(context);
}

void ddAbstractFigure::basicDrawSelected(wxBufferedDC& context){
	context.SetPen(*wxRED_PEN);
	context.SetBrush(wxBrush (wxColour(133, 133, 133),wxSOLID));
	context.DrawRectangle(basicDisplayBox);
}


ddITool ddAbstractFigure::CreateFigureTool(ddITool *defaultTool){
return *defaultTool;
//DD-TODO: need IDrawingEditor as parameter?
}

//DD-TODO: HIGH-PRIORITY-FINISH-THIS: Add connection methods and others

void ddAbstractFigure::moveBy(int x, int y){
	willChange();
	basicMoveBy(x,y);
	changed();
}

void ddAbstractFigure::basicMoveBy(int x, int y){
		ddRect r = basicDisplayBox;
		r.x += x;
		r.y += y;
		basicDisplayBox = r;
}


void ddAbstractFigure::moveTo(int x, int y){
		ddRect r = basicDisplayBox;
		r.x = x;
		r.y = y;
		basicDisplayBox = r;
}

void ddAbstractFigure::willChange(){
}

void ddAbstractFigure::changed(){
			invalidate();
			//DD-TODO: OnFigureChanged (new FigureEventArgs (this, DisplayBox));
}

void ddAbstractFigure::invalidate(){
//DD-TODO: OnFigureInvalidated (new FigureEventArgs (this, InvalidateDisplayBox));
}

bool ddAbstractFigure::containsPoint(int x, int y){
	return basicDisplayBox.Contains(x,y);
}




/*
ConnectorAt
InvalidateDisplayBox
Visit ??? needed????

*/