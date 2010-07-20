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
#include "dd/dditems/handles/ddAddFkButtonHandle.h"
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/dditems/utilities/ddDataType.h"
#include "dd/draw/tools/ddConnectionCreationTool.h"
#include "dd/draw/utilities/ddMouseEvent.h"


//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddAddFkButtonHandle::ddAddFkButtonHandle(ddIFigure *owner, ddILocator *buttonLocator ,wxBitmap &buttonImage, wxSize &size):
ddButtonHandle(owner,buttonLocator,buttonImage,size)
{
}

ddAddFkButtonHandle::~ddAddFkButtonHandle(){
}

void ddAddFkButtonHandle::invokeStart(int x, int y, ddDrawingView *view)
{
	if(getOwner()->ms_classInfo.IsKindOf(&ddTableFigure::ms_classInfo)){
		ddTableFigure *table = (ddTableFigure*) getOwner();
		ddLineConnection *fkConnection = new ddLineConnection();
		fkConnection->setStartTerminal(new ddLineTerminal());
		fkConnection->setEndTerminal(new ddLineTerminal());
		ddConnectionCreationTool *conn = new ddConnectionCreationTool(view->editor(),fkConnection);
		view->editor()->setTool(conn);
		// Simulate button down to start connection of foreign key
		wxMouseEvent e(wxEVT_LEFT_DOWN);
		e.m_x=x;
		e.m_y=y;
		e.SetEventObject(view);
		ddMouseEvent evento(e,view);
		conn->mouseDown(evento);
	}
}

void ddAddFkButtonHandle::invokeStep(int x, int y, ddDrawingView *view)
{
	ddTableFigure *table = (ddTableFigure*) getOwner();
	table->canConnect();
}

void ddAddFkButtonHandle::invokeEnd(int x, int y, ddDrawingView *view)
{
	ddTableFigure *table = (ddTableFigure*) getOwner();
	table->canConnect();}

//debo hacer que la figura tabla tenga el handle y añadirselo :D