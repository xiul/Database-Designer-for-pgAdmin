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
#include "dd/draw/main/ddDrawingView.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddAbstractFigure::ddAbstractFigure(){

}

ddAbstractFigure::~ddAbstractFigure(){

}

bool ddAbstractFigure::canConnect (){
return true;
}

bool ddAbstractFigure::includes(ddIFigure *figure){
	return (this==figure);	
}

void ddAbstractFigure::draw(wxBufferedDC& context, ddDrawingView *view){
	ddIFigure::draw(context,view);
	basicDraw(context,view);
}

void ddAbstractFigure::basicDraw(wxBufferedDC& context, ddDrawingView *view){
	ddRect copy = displayBox();
	view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);

	context.SetPen(*wxGREEN_PEN);
	context.SetBrush(wxBrush (wxColour(208, 208, 208),wxSOLID));
	context.DrawRectangle(copy);
}

void ddAbstractFigure::drawSelected(wxBufferedDC& context, ddDrawingView *view){
	ddIFigure::drawSelected(context,view);	
	basicDrawSelected(context,view);
}

void ddAbstractFigure::basicDrawSelected(wxBufferedDC& context, ddDrawingView *view){
	ddRect copy = displayBox();
	view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);
	
	context.SetPen(*wxRED_PEN);
	context.SetBrush(wxBrush (wxColour(133, 133, 133),wxSOLID));
	context.DrawRectangle(copy);
}


ddITool* ddAbstractFigure::CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool)
{
	return defaultTool;
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
	invalidate();

}

void ddAbstractFigure::changed(){
			invalidate();
			onFigureChanged(this);
			//DD-TODO: this is really needed
}

void ddAbstractFigure::invalidate(){
//DD-TODO: OnFigureInvalidated ( FigureEventArgs (this, InvalidateDisplayBox));
}

bool ddAbstractFigure::containsPoint(int x, int y){
	return basicDisplayBox.Contains(x,y);
}

void ddAbstractFigure::onFigureChanged(ddIFigure *figure)
{
	//go to ifigure procedure to alert observers of changes on this figure
	ddIFigure::onFigureChanged(figure);
}

/*
ConnectorAt
InvalidateDisplayBox
Visit ??? needed????

*/