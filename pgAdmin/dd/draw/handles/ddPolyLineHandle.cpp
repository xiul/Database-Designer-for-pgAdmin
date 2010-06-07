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

// App headers
#include "dd/draw/handles/ddPolyLineHandle.h"

ddPolyLineHandle::ddPolyLineHandle(ddPolyLineFigure *figure, ddILocator *loc, int index):
ddLocatorHandle((ddIFigure *)figure,loc)
{
	indx=index;
}

ddPolyLineHandle::~ddPolyLineHandle()
{
}

void ddPolyLineHandle::draw(wxBufferedDC& context)
{
	double middle=getDisplayBox().width/2;
	context.DrawCircle(
						wxPoint(getDisplayBox().x+middle,getDisplayBox().y+middle),
						wxCoord(middle)
						);
	//DD-TODO: improve this draw
}

//HIGH-PRIORITY-FINISH-THIS finish this

ddPoint* ddPolyLineHandle::locate()
{
	return NULL;
}



void ddPolyLineHandle::invokeStart(int x, int y, ddDrawingView *view)
{
}

void ddPolyLineHandle::invokeStep(int x, int y, ddDrawingView *view)
{
	//DD-TODO: HIGH-PRIORITY-FINISH-THIS add code here
}

void ddPolyLineHandle::invokeEnd(int x, int y, ddDrawingView *view)
{
}

wxCursor& ddPolyLineHandle::createCursor()
{
	return NULL;
		//wxCursor(wxCURSOR_CROSS);
	//DD-TODO: HIGH-PRIORITY-FINISH-THIS Should I use reference or a pointer here?
}

