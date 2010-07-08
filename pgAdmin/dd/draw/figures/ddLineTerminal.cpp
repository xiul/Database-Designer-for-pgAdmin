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
#include "dd/draw/main/ddDrawingView.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddLineTerminal::ddLineTerminal(){
	middle = ddPoint(0,0);
}

ddLineTerminal::~ddLineTerminal(){

}

//DD-TODO: this need this ddDrawingView *view ??? or just avoid this and always pass calcscrolled points
ddPoint& ddLineTerminal::draw (wxBufferedDC& context, ddPoint& a, ddPoint& b, ddDrawingView *view){
	ddPoint copyA = ddPoint (a);
	view->CalcScrolledPosition(copyA.x,copyA.y,&copyA.x,&copyA.y);
	ddPoint copyB = ddPoint (b);
	view->CalcScrolledPosition(copyB.x,copyB.y,&copyB.x,&copyB.y);
	context.DrawLine(copyA, copyB);
	//DD-TODO: improve this function is bad just for testing, fix memory leak
	middle = ddPoint(copyA.x+abs(copyA.x - copyB.x),copyA.y+abs(copyA.y - copyB.y));
	//context.DrawCircle(*middle,10);
	context.DrawRectangle(wxRect(copyA.x,copyA.y,10,10));
	context.DrawCircle(copyA,10);
	return middle;
}

