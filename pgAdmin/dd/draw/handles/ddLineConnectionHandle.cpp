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
#include "dd/draw/handles/ddLineConnectionHandle.h"
#include "dd/draw/figures/ddPolyLineFigure.h"
#include "dd/draw/utilities/ddPoint.h"
#include "dd/draw/utilities/ddGeometry.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddLineConnectionHandle::ddLineConnectionHandle(ddPolyLineFigure *figure, ddILocator *loc, int index):
ddPolyLineHandle(figure,loc,index)
{
}

void ddLineConnectionHandle::invokeEnd(int x, int y, ddDrawingView *view)
{
	ddPolyLineFigure *figure = (ddPolyLineFigure *) getOwner();
	//eliminate all handles in the middle of a straight line
	
	//DD-TODO: verify index are well defined here and it's doing what is suppossed to do
	if( figure->pointCount() > 2 && getIndex() != 0 && getIndex() != (figure->pointCount()-1) )
	{
		ddPoint p1 = figure->pointAt(getIndex()-1);
		ddPoint p2 = figure->pointAt(getIndex()+1);
		ddGeometry g;
		if(g.lineContainsPoint(p1.x, p1.y, p2.x, p2.y, x, y))
		{
			figure->removePointAt(getIndex());
		}
	}
}
