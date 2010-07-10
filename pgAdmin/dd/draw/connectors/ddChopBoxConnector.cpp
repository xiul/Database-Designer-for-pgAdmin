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
#include "dd/draw/connectors/ddChopBoxConnector.h"
#include "dd/draw/utilities/ddGeometry.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks

ddChopBoxConnector::ddChopBoxConnector(ddIFigure *owner):
ddIConnector(owner)
{
}

ddChopBoxConnector::~ddChopBoxConnector()
{
}

//DD-TODO: change to reference ddPoint&
ddPoint ddChopBoxConnector::chop(ddIFigure *target, ddPoint point){
	
	if(target && target->containsPoint(point.x, point.y))
	{
		return target->displayBox().center();
	}
	else if(!target)
	{
		return ddPoint(0,0);
	}
	
	ddGeometry g;
	
	double angle = g.angleFromPoint(getDisplayBox(), point);
	return g.edgePointFromAngle(getDisplayBox(), angle);
}

ddPoint ddChopBoxConnector::findStart(ddLineConnection *connFigure)
{
	if(!connFigure)
	{
		return getDisplayBox().center();
	}
	
	if(connFigure->pointCount()<2)
	{
		return getDisplayBox().center();
	}

	ddIFigure *start = connFigure->getStartConnector()->getOwner();
	ddPoint point = connFigure->pointAt(1);
	return chop(start,point);
}

ddPoint ddChopBoxConnector::findEnd(ddLineConnection *connFigure)
{
	if(!connFigure)
	{
		return getDisplayBox().center();
	}
	ddIFigure *end = connFigure->getEndConnector()->getOwner();
	ddPoint point = connFigure->pointAt(connFigure->pointCount()-2);
	return chop(end,point);
}
