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
#include "dd/draw/figures/ddRectangleFigure.h"
#include "dd/draw/main/ddDrawingView.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks



ddRectangleFigure::ddRectangleFigure(){
	
}

ddRectangleFigure::~ddRectangleFigure(){

}

void ddRectangleFigure::basicDraw(wxBufferedDC& context, ddDrawingView *view)
{
	ddRect copy = displayBox();
	view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);

	context.SetPen(*wxBLACK_PEN);
	context.SetBrush(wxBrush (wxColour(208, 208, 208),wxSOLID));
	context.DrawRectangle(copy);
}

void ddRectangleFigure::basicDrawSelected(wxBufferedDC& context, ddDrawingView *view)
{
	ddRect copy = displayBox();
	view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);
	
	context.SetPen(*wxRED_PEN);
	context.SetBrush(wxBrush (wxColour(73, 73, 73),wxSOLID));
	context.DrawRectangle(copy);
}

void ddRectangleFigure::setRectangle(ddRect& rect)
{
	basicDisplayBox=rect;
}

void ddRectangleFigure::setSize(wxSize& size)
{
	basicDisplayBox.SetSize(size);
}