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
#include "dd/draw/handles/ddButtonHandle.h"
#include "dd/draw/utilities/ddPoint.h"
#include "dd/draw/main/ddDrawingView.h"




//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddButtonHandle::ddButtonHandle(ddIFigure *owner, ddILocator *buttonLocator ,wxBitmap &buttonImage, wxSize &size):
ddIHandle(owner)
{
	//buttonIcon=buttonImage; FOR TEST REASON USE DEFAULT ONE UNCOMMENT THIS FOR FINAL VERSION
	buttonIcon = buttonImage;
	clicked=false;
	bLocator = buttonLocator;
	displayBox.SetSize(size);
}

ddButtonHandle::~ddButtonHandle()
{
	if(bLocator)
		delete bLocator;
}

wxCursor& ddButtonHandle::createCursor()
{
	//DD-TODO:  Should I use reference or a pointer here?
	return wxCursor(wxCURSOR_PENCIL);
}

//DD-TODO: avoid this memory leak throught every call to locate()
ddRect& ddButtonHandle::getDisplayBox()
{
	ddPoint p = locate();
	displayBox.SetPosition(p);
	return displayBox;
}

void ddButtonHandle::draw(wxBufferedDC& context, ddDrawingView *view)
{
	wxPoint copy = getDisplayBox().GetPosition();
	view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);
	if(buttonIcon.IsOk())
		context.DrawBitmap(buttonIcon,copy.x,copy.y,true);
}


ddPoint& ddButtonHandle::locate()
{
	if(bLocator)
		return bLocator->locate(getOwner());
	else
		return ddPoint(0,0);
}
