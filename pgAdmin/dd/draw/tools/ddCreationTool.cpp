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
#include "dd/draw/tools/ddCreationTool.h"
#include "dd/draw/tools/ddSelectionTool.h"


//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddCreationTool::ddCreationTool(ddDrawingEditor *editor, ddIFigure *prototype):
ddAbstractTool(editor){
	figurePrototype=prototype;
}

ddCreationTool::~ddCreationTool(){
}

void ddCreationTool::mouseDown(ddMouseEvent& event){
	ddAbstractTool::mouseDown(event);
	getDrawingEditor()->view()->getDrawing()->add(figurePrototype);
	int x=event.GetPosition().x, y=event.GetPosition().y;
	figurePrototype->moveTo(x,y);
	getDrawingEditor()->view()->clearSelection();
	getDrawingEditor()->view()->addToSelection(figurePrototype);
}

void ddCreationTool::mouseUp(ddMouseEvent& event){
	ddAbstractTool::mouseUp(event);
	//DD-TODO: delete tool before overwrite??
	getDrawingEditor()->setTool(new ddSelectionTool(getDrawingEditor()));
}

void ddCreationTool::activate()
{
	ddAbstractTool::activate();
	getDrawingEditor()->view()->SetCursor(wxCursor(wxCURSOR_CROSS));
}

void ddCreationTool::deactivate()
{
	ddAbstractTool::deactivate();
	getDrawingEditor()->view()->SetCursor(wxCursor(wxCURSOR_ARROW));
}

void ddCreationTool::setPrototype(ddIFigure *prototype)
{
	figurePrototype=prototype;
}

ddIFigure* ddCreationTool::getPrototype()
{
	return figurePrototype;
}