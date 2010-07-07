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
#include "dd/dditems/locators/ddMoveColLocator.h"
#include "dd/dditems/figures/ddTableFigure.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddMoveColLocator::ddMoveColLocator()
{
}

ddMoveColLocator::~ddMoveColLocator()
{
}

ddPoint* ddMoveColLocator::locate(ddIFigure *owner)
{
	if(owner)
	{
		ddTableFigure *table = (ddTableFigure*) owner;
		int x = table->displayBox().x + table->displayBox().width - 40; //(8+2+8+2+8+2+8+2)
		int y = table->displayBox().y + 6;
		return new ddPoint(x,y);
	}
	return new ddPoint(0,0);
}

/*
			if (owner != null) {
				TableFigure ownerTable = (TableFigure)owner;
				return new PointD ((ownerTable.DisplayBox.X + ownerTable.DisplayBox.Width - 27),
				(ownerTable.DisplayBox.Y + 6));
			}
			return new PointD (0, 0);

*/