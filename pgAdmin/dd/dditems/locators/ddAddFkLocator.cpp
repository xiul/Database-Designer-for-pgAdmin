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
#include "dd/dditems/locators/ddAddFkLocator.h"
#include "dd/dditems/figures/ddTableFigure.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddAddFkLocator::ddAddFkLocator()
{
}

ddAddFkLocator::~ddAddFkLocator()
{
}

ddPoint* ddAddFkLocator::locate(ddIFigure *owner)
{
	if(owner)
	{
		ddTableFigure *table = (ddTableFigure*) owner;
		int x = table->displayBox().x + table->displayBox().width - 10; //(8+2)
		int y = table->displayBox().y + 6;
		return new ddPoint(x,y);
	}
	return new ddPoint(0,0);
}
