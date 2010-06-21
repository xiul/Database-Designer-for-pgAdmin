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
#include <wx/dcbuffer.h>

// App headers
#include "dd/draw/figures/ddLineTerminal.h"
#include "dd/draw/utilities/ddPoint.h"
#include "dd/draw/utilities/ddRect.h"

ddLineTerminal::ddLineTerminal(){
	
}

ddLineTerminal::~ddLineTerminal(){

}

ddPoint* ddLineTerminal::draw (wxBufferedDC& context, ddPoint *a, ddPoint *b){
	context.DrawLine(*a, *b);
	//DD-TODO: improve this function is bad just for testing, fix memory leak
	ddPoint *middle = new ddPoint(a->x+abs(a->x - b->x),a->y+abs(a->y - b->y));
	//context.DrawCircle(*middle,10);
	context.DrawRectangle(wxRect(a->x,a->y,10,10));
	context.DrawCircle(*a,10);
	return middle;
}

