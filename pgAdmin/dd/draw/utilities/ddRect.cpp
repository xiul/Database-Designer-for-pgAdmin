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
#include "dd/draw/utilities/ddRect.h"

ddRect::ddRect()
{
}

ddRect::ddRect(int xx, int yy, int ww, int hh):
wxRect(xx,yy,ww,hh)
{
}

ddRect::ddRect(ddPoint *topLeft, ddPoint *bottomRight):
wxRect(*topLeft, *bottomRight)
{
}

ddRect::ddRect(ddPoint *point):
wxRect(point->x,point->y,0,0)
{
}

ddRect::ddRect(ddPoint& point):
wxRect(point.x,point.y,0,0)
{
}

void ddRect::add (int newX, int newY) {

	int x1 = min(x , newX);
	int x2 = max(x+width , newX);
	int y1 = min(y , newY);
	int y2 = max(y+height , newY);

	SetX(x1);
	SetWidth(x2-x1);
	SetY(y1);
	SetHeight(y2-y1);
}


void ddRect::add (ddRect *newRect){
	add(newRect->GetTopLeft().x , newRect->GetTopLeft().y);
	add(newRect->GetBottomRight().x , newRect->GetBottomRight().y);
}

void ddRect::add (ddRect& newRect){
	add(newRect.GetTopLeft().x , newRect.GetTopLeft().y);
	add(newRect.GetBottomRight().x , newRect.GetBottomRight().y);
}

void ddRect::add(ddPoint *p){
	add(p->x,p->y);
}

int ddRect::min(int a, int b){
	return(a<=b)?a:b;
}

int ddRect::max(int a, int b){
	return(a>=b)?a:b;
}


