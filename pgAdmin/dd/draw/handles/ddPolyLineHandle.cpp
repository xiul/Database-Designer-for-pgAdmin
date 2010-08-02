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
#include "dd/draw/locators/ddPolyLineLocator.h"
#include "dd/draw/main/ddDrawingView.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddPolyLineHandle::ddPolyLineHandle(ddPolyLineFigure *figure, ddILocator *loc, int index):
ddLocatorHandle((ddIFigure *)figure,loc)
{
	indx=index;
}

ddPolyLineHandle::~ddPolyLineHandle()
{
	//DD-TODO: delete locator here?
}

void ddPolyLineHandle::draw(wxBufferedDC& context, ddDrawingView *view)
{
	//DD-TODO: set graphic style
	ddRect copy = getDisplayBox();
	view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);

	double middle=copy.width/2;
	context.DrawCircle(
						wxPoint(copy.x+middle,copy.y+middle),
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


wxCursor ddPolyLineHandle::createCursor()
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
	ddPolyLineLocator *l = (ddPolyLineLocator*) locator();
	l->setIndex(index);
}