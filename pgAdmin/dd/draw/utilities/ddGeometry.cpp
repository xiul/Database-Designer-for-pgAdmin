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

bool ddGeometry::lineContainsPoint(int x1, int y1, int x2, int y2, int px, int py){
	ddRect r = ddRect(ddPoint(x1,y1));
	r.add(x2,y2);
	r.Inflate(2,2);
	if(!r.Contains(px,py)){
		return false;
	}

	int a, b, x, y;

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

int ddGeometry::min(int a, int b){
	return(a<=b)?a:b;
}

int ddGeometry::max(int a, int b){
	return(a>=b)?a:b;
}
