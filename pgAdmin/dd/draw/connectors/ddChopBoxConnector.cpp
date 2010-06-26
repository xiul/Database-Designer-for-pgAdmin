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

ddPoint ddChopBoxConnector::findStart()
{
	return getDisplayBox().center();
}

ddPoint ddChopBoxConnector::findEnd()
{
	return getDisplayBox().center();

}
//	IConnectionFigure
	
	/*
				if (connection == null) {
				return DisplayBox.Center;
			}

			IFigure end = connection.EndConnector.Owner;
			PointD point = connection.PointAt (connection.PointCount - 2);

			return Chop (end, point);
	*/

