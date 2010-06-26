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
#include "dd/draw/utilities/ddGeometry.h"
#include "dd/draw/utilities/ddRect.h"
#include "dd/draw/utilities/ddPoint.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


//typecasting to avoid miscalculations, here need double values not int
bool ddGeometry::lineContainsPoint(double x1, double y1, double x2, double y2, double px, double py){

	ddRect r = ddRect(ddPoint(x1,y1));
	r.add(x2,y2);
	r.Inflate(2,2);
	if(!r.Contains(px,py)){
		return false;
	}

	double a, b, x, y;

	if( x1 == x2 )
	{
		return (abs(px - x1) < 3);
	}

	if( y1 == y2 )
	{
		return (abs(py - y1) < 3);
	}

	a = (y1 - y2) / (x1 - x2);
	b = y1 - a * x1;
	x = (py - b) / a;
	y = a * px + b;

	return (min( abs(x-px), abs(y-py)) < 4);
}

int ddGeometry::min(double a, double b){
	return(a<=b)?a:b;
}

int ddGeometry::max(double a, double b){
	return(a>=b)?a:b;
}

double ddGeometry::angleFromPoint(ddRect r, ddPoint point)
{
	double rx = point.x - r.center().x;
	double ry = point.y - r.center().y;
	return atan2 (ry * r.width, rx * r.height);
}

ddPoint ddGeometry::edgePointFromAngle(ddRect r, double angle)
{
	double sinv = sin(angle);
	double cosv = cos(angle);
	double e = 0.0001;
	double x = 0.0;
	double y = 0.0;

	if( abs(sinv) > e )
	{
		x = (1.0 + cosv / abs (sinv)) / 2.0 * r.width;
		x = range(0.0,r.width,x);
	}
	else if ( cosv >= 0.0 )
	{
		x = r.width;
	}

	if ( abs(cosv) > e )
	{
		y = (1.0 + sinv / abs (cosv)) / 2.0 * r.height;
		y = range (0.0, r.height, y);
	}
	else if ( sinv >= 0.0 )
	{
		y = r.height;
	}

	return ddPoint(r.x + x, r.y + y);
}

double ddGeometry::range(double min, double max, double num)
{
	return num < min ? min : (num > max ? max: num);
}


