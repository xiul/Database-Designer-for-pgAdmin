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
#include "dd/draw/handles/ddLocatorHandle.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddLocatorHandle::ddLocatorHandle(ddIFigure *owner, ddILocator *locator):
ddIHandle(owner)
{
	loc=locator;
}
ddLocatorHandle::~ddLocatorHandle()
{
	if(loc)
		delete loc;
}

ddPoint& ddLocatorHandle::locate(){
	return loc==NULL ? ddPoint(0,0) : loc->locate(getOwner()) ;
}

ddILocator* ddLocatorHandle::locator()
{
	return loc;
}

void ddLocatorHandle::invokeStart(ddMouseEvent& event, ddDrawingView *view){
}

void ddLocatorHandle::invokeStep(ddMouseEvent& event, ddDrawingView *view){
}

void ddLocatorHandle::invokeEnd(ddMouseEvent& event, ddDrawingView *view){
}