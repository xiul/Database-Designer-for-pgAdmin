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

ddRect::ddRect(){
}

ddRect::ddRect(int xx, int yy, int ww, int hh):
wxRect(xx,yy,ww,hh){
}

ddRect::ddRect(wxPoint topLeft, wxPoint bottomRight):
wxRect(topLeft, bottomRight){
}

void ddRect::add (ddRect& newRect) {
	int x1 = min(this->x,newRect.x);
	int x2 = max(this->x+this->width,newRect.x);
	int y1 = min(this->y,newRect.y);
	int y2 = max(this->y+this->height,newRect.y);

	this->SetX(x1);
	this->SetWidth(x2-x1);
	this->SetY(y1);
	this->SetHeight(y2-y1);
	//DD-TODO: check this operations are well done
}

 
int ddRect::min(int a, int b){
	return(a<=b)?a:b;
}

int ddRect::max(int a, int b){
	return(a>=b)?a:b;
}

