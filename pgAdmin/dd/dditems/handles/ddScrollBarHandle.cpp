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
#include "dd/dditems/handles/ddScrollBarHandle.h"
#include "dd/draw/utilities/ddPoint.h"
#include "dd/draw/main/ddDrawingView.h"




//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddScrollBarHandle::ddScrollBarHandle(ddTableFigure *owner, ddILocator *scrollBarLocator , wxSize &size):
ddIHandle(owner)
{
	table=owner;
	scrollLocator = scrollBarLocator;
	displayBox.SetSize(size);
}

ddScrollBarHandle::~ddScrollBarHandle()
{
	if(scrollLocator)
		delete scrollLocator;
}


wxCursor& ddScrollBarHandle::createCursor()
{
	return wxCursor(wxCURSOR_HAND);
}

//avoid to use inflate on this handle
ddRect& ddScrollBarHandle::getDisplayBox(){
	ddPoint p = locate();
	displayBox.width=0;
	displayBox.height=0;
	displayBox.SetPosition(p);
	return displayBox;
}

void ddScrollBarHandle::draw(wxBufferedDC& context, ddDrawingView *view)
{
	wxPoint copy = getDisplayBox().GetPosition();
	view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);
	context.DrawLine(copy.x,copy.y,copy.x,copy.y+100);
/*	if(buttonIcon.IsOk())
		context.DrawBitmap(buttonIcon,copy.x,copy.y,true);*/
}

void ddScrollBarHandle::invokeStart(int x, int y, ddDrawingView *view)
{
}

void ddScrollBarHandle::invokeStep(int x, int y, ddDrawingView *view)
{
}

void ddScrollBarHandle::invokeEnd(int x, int y, ddDrawingView *view)
{
}

ddPoint& ddScrollBarHandle::locate()
{
	if(scrollLocator)
		return scrollLocator->locate(getOwner());
	else
		return ddPoint(0,0);
}