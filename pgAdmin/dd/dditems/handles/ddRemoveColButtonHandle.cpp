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
#include "dd/dditems/handles/ddRemoveColButtonHandle.h"
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/dditems/utilities/ddDataType.h"


//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddRemoveColButtonHandle::ddRemoveColButtonHandle(ddIFigure *owner, ddILocator *buttonLocator ,wxBitmap &buttonImage, wxSize &size):
ddButtonHandle(owner,buttonLocator,buttonImage,size)
{
}

ddRemoveColButtonHandle::~ddRemoveColButtonHandle(){
}

void ddRemoveColButtonHandle::invokeStart(int x, int y, ddDrawingView *view)
{
	ddTableFigure *table = (ddTableFigure*) getOwner();
	ddColumnFigure *column = (ddColumnFigure*) table->findFigure(x,y);
	//DD-TODO: Validate column belongs to table, what to do if other kind of figure selected???
	if(column)
			table->toggleColumnDeleteMode();
}

void ddRemoveColButtonHandle::invokeStep(int x, int y, ddDrawingView *view)
{
}

void ddRemoveColButtonHandle::invokeEnd(int x, int y, ddDrawingView *view)
{
}

//debo hacer que la figura tabla tenga el handle y añadirselo :D