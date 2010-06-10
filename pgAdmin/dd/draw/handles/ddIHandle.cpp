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
#include "dd/draw/handles/ddIHandle.h"
#include "dd/draw/utilities/ddPoint.h"

ddIHandle::ddIHandle(ddIFigure *owner){
	figureOwner=owner;
}
ddIHandle::~ddIHandle(){

}

ddIFigure* ddIHandle::getOwner(){
	return figureOwner;
}

ddRect& ddIHandle::getDisplayBox(){
	ddPoint *p = locate();
	displayBox.width=0;
	displayBox.height=0;
	displayBox.SetPosition(*p);
	displayBox.Inflate(size,size);
	return displayBox;
/*
				PointD p = Locate ();
				RectangleD rect = new RectangleD (p, p);
				rect.Inflate (Size, Size);
				rect.OffsetDot5 ();
				return rect;
*/

}

bool ddIHandle::containsPoint(int x, int y){
	return getDisplayBox().Contains(x,y);
}

//Al methods and properties at ddIHandle.h
