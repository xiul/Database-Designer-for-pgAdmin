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
#include "dd/draw/figures/ddBitmapFigure.h"
#include "dd/draw/main/ddDrawingView.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks



ddBitmapFigure::ddBitmapFigure(wxBitmap image){
	imageToDraw=image;
	this->getBasicDisplayBox().width=imageToDraw.GetWidth();
	this->getBasicDisplayBox().height=imageToDraw.GetHeight();
}

ddBitmapFigure::~ddBitmapFigure(){
}



void ddBitmapFigure::basicDraw(wxBufferedDC& context, ddDrawingView *view)
{
	ddRect copy = displayBox();
	view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);
	context.DrawBitmap(imageToDraw,copy.GetPosition(),true);
}

void ddBitmapFigure::basicDrawSelected(wxBufferedDC& context, ddDrawingView *view)
{
	basicDraw(context,view);
}

void ddBitmapFigure::changeBitmap(wxBitmap image)
{
	imageToDraw=image;
	this->getBasicDisplayBox().width=imageToDraw.GetWidth();
	this->getBasicDisplayBox().height=imageToDraw.GetHeight();
}

int ddBitmapFigure::getWidth()
{
	return imageToDraw.GetWidth();
}

int ddBitmapFigure::getHeight()
{
	return imageToDraw.GetHeight();
}