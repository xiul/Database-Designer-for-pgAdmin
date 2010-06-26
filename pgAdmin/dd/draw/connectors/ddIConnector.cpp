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
//#include "dd/draw/figures/ddIFigure.h"
#include "dd/draw/figures/ddLineConnection.h"
#include "dd/draw/connectors/ddIConnector.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


class ddLineConnection;  //HACK-FIX to circular reference
class ddIFigure;

ddIConnector::ddIConnector(ddIFigure *owner):
ddObject()
{
	figureOwner = owner;
}

ddIConnector::~ddIConnector()
{
}

ddIFigure* ddIConnector::getOwner()
{
	return figureOwner;

}

void ddIConnector::setOwner(ddIFigure *owner)
{
	figureOwner=owner;
}

void ddIConnector::draw(wxBufferedDC& context)
{

}

ddRect& ddIConnector::getDisplayBox()
{
	return figureOwner->displayBox();
}

bool ddIConnector::containsPoint(int x, int y)
{
	return figureOwner->containsPoint(x,y);
}

ddPoint ddIConnector::findStart(ddLineConnection *connection)
{
	return getDisplayBox().center();
}

ddPoint ddIConnector::findEnd(ddLineConnection *connection)
{
	return getDisplayBox().center();
}
