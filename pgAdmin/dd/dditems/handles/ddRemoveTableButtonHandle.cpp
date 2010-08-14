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
#include "dd/dditems/handles/ddRemoveTableButtonHandle.h"
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/dditems/figures/ddRelationshipFigure.h"
#include "dd/dditems/utilities/ddDataType.h"
#include "dd/draw/main/ddDrawingView.h"


//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddRemoveTableButtonHandle::ddRemoveTableButtonHandle(ddIFigure *owner, ddILocator *buttonLocator ,wxBitmap &buttonImage, wxSize &size):
ddButtonHandle(owner,buttonLocator,buttonImage,size)
{
}

ddRemoveTableButtonHandle::~ddRemoveTableButtonHandle(){
}

void ddRemoveTableButtonHandle::invokeStart(ddMouseEvent &event, ddDrawingView *view)
{
}

void ddRemoveTableButtonHandle::invokeStep(ddMouseEvent &event, ddDrawingView *view)
{
}

void ddRemoveTableButtonHandle::invokeEnd(ddMouseEvent &event, ddDrawingView *view)
{

	if(view && getOwner())
	{
		ddTableFigure *table = (ddTableFigure*) getOwner();	
		//unselect table
		if(view->isFigureSelected(table))
		{
			view->removeFromSelection(table);
		}
		table->processDeleteAlert(view);
		//drop table
		view->remove(table);
		if(table)
		{
			delete table;
		}
	}
}