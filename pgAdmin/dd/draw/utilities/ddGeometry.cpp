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

double ddGeometry::lineSize (ddPoint p1, ddPoint p2)
{
	int w = p1.x - p2.x;
	int h = p1.y - p2.y;
	
	double perimeter = w*w + h*h;
	return sqrt (perimeter);
}


bool ddGeometry::intersection(ddPoint p1, ddPoint p2, ddPoint p3, ddPoint p4)
{
    // Store the values for fast access and easy
    // equations-to-code conversion
    float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
    float y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;
 
    float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    // If d is zero, there is no intersection
    if (d == 0) return NULL;
 
    // Get the x and y
    float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
    // point of intersection
	float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
    float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;
 
    // Check if the x and y coordinates are within both lines
    if ( x < min(x1, x2) || x > max(x1, x2) || x < min(x3, x4) || x > max(x3, x4) )
		return false;
    if ( y < min(y1, y2) || y > max(y1, y2) || y < min(y3, y4) || y > max(y3, y4) ) 
		return false;

	return true;
}


/*
	// Theory at: http://local.wasp.uwa.edu.au/~pbourke/geometry/pointline/
	// This method gets (p) and (m) from (a), (b), lineDistance and pointDistance

void ddGeometry::arrowPoints(ddPoint a, ddPoint b, int lineDistance, int pointDistance,	ddPoint *p, ddPoint *p2, ddPoint *m)
{
	ddPoint ab_vector = ddPoint(b.x - a.x,b.y - a.y);
	double length = lineSize(a,b);

	if(length == 0)
	{
		*p = a;
		*m = *p;
	}

	double pd = pointDistance;

	double proportion = pd / length;

	ddPoint normal = ddPoint(0,0);
	normal.x = -ab_vector.y / length;
	normal.y = ab_vector.x / length;

	ddPoint mTemp = ddPoint(0,0);
	mTemp.x = a.x + proportion * ab_vector.x;
	mTemp.y = a.y + proportion * ab_vector.x;
	*m=mTemp;
	
	ddPoint pTemp = ddPoint(0,0);
	pTemp.x = mTemp.x + normal.y * lineDistance;
	pTemp.y = mTemp.y + normal.y * lineDistance;
	*p=pTemp;
	
	ddPoint p2Temp = ddPoint(0,0);
	p2Temp.x = mTemp.x + normal.x * lineDistance * -1.0;
	p2Temp.y = mTemp.y + normal.y * lineDistance * -1.0;
	*p2=p2Temp;

}
*/