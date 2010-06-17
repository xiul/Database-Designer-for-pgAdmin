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
#include "dd/draw/figures/ddPolyLineFigure.h"

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
	//DD-TODO: set graphic style
	double middle=getDisplayBox().width/2;
	context.DrawCircle(
						wxPoint(getDisplayBox().x+middle,getDisplayBox().y+middle),
						wxCoord(middle)
						);
	//DD-TODO: improve this draw
}


/*ddPoint* ddPolyLineHandle::locate()
{
	return NULL;
}
*/

void ddPolyLineHandle::invokeStep(int x, int y, ddDrawingView *view)
{
	((ddPolyLineFigure*) getOwner())->setPointAt(indx,x,y);
}


wxCursor& ddPolyLineHandle::createCursor()
{
	return wxCursor(wxCURSOR_CROSS);
	//DD-TODO:  Should I use reference or a pointer here?
}

int ddPolyLineHandle::getIndex()
{
	return indx;
}

void ddPolyLineHandle::setIndex(int index)
{
	indx=index;
}