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
#include "dd/dditems/handles/ddAddColButtonHandle.h"
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/dditems/utilities/ddDataType.h"


//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddAddColButtonHandle::ddAddColButtonHandle(ddIFigure *owner, ddILocator *buttonLocator ,wxBitmap &buttonImage, wxSize &size):
ddButtonHandle(owner,buttonLocator,buttonImage,size)
{
}

ddAddColButtonHandle::~ddAddColButtonHandle(){
}

void ddAddColButtonHandle::invokeStart(int x, int y, ddDrawingView *view)
{
	ddTableFigure *table = (ddTableFigure*) getOwner();
	table->addColumn(new ddColumnFigure(wxString(wxT("NewColumn"))));
}

void ddAddColButtonHandle::invokeStep(int x, int y, ddDrawingView *view)
{
}

void ddAddColButtonHandle::invokeEnd(int x, int y, ddDrawingView *view)
{
}

//debo hacer que la figura tabla tenga el handle y añadirselo :D