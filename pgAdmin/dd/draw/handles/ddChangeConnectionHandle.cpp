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
#include "dd/draw/handles/ddChangeConnectionHandle.h"
#include "dd/draw/figures/ddLineConnection.h"
#include "dd/draw/utilities/ddPoint.h"
#include "dd/draw/main/ddDrawingView.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddChangeConnectionHandle::ddChangeConnectionHandle(ddLineConnection *owner):
ddIHandle(owner)
{
	connection = owner;
	targetFigure = NULL;
	originalTarget = NULL;
}

ddChangeConnectionHandle::~ddChangeConnectionHandle(){
	
}

void ddChangeConnectionHandle::draw(wxBufferedDC& context, ddDrawingView *view)
{

	ddPoint points[5];
	ddRect copy = getDisplayBox();
	view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);

	copy.Deflate(2,2);
	context.SetPen(*wxGREEN_PEN);
	context.SetBrush(*wxGREEN_BRUSH);
	context.DrawRectangle(copy);
}

wxCursor ddChangeConnectionHandle::createCursor()
{
	return wxCursor(wxCURSOR_CROSS);
}

void ddChangeConnectionHandle::invokeStart(int x, int y, ddDrawingView *view)
{
	originalTarget = target();
	disconnect();
}

void ddChangeConnectionHandle::invokeStep(int x, int y, ddDrawingView *view)
{
	ddPoint p = ddPoint(x,y);
	ddIFigure *figure = findConnectableFigure(x,y,view->getDrawing());
	targetFigure = figure;
	ddIConnector *target = findConnectionTarget(x,y,view->getDrawing());
	if(target)
	{
		p = target->getDisplayBox().center();
	}
	setPoint(p); 
	connection->updateConnection();
}

void ddChangeConnectionHandle::invokeEnd(int x, int y, ddDrawingView *view)
{
	ddIConnector *target = findConnectionTarget(x,y,view->getDrawing()); 
		if(!target)
		{
			target=originalTarget;
		}
	ddPoint p = ddPoint(x,y);
	connect(target);
	connection->updateConnection();
}


ddIFigure* ddChangeConnectionHandle::findConnectableFigure (int x, int y, ddDrawing *drawing)
{
	ddIFigure *out=NULL;
	ddIteratorBase *iterator=drawing->figuresInverseEnumerator();
	while(iterator->HasNext())
	{
		ddIFigure *figure = (ddIFigure*) iterator->Next();
		if(figure->containsPoint(x,y) && isConnectionPossible(figure))
		{
			out=figure;
			break;
		}
	}
	delete iterator;
	return out;
}
ddIConnector* ddChangeConnectionHandle::findConnectionTarget(int x, int y, ddDrawing *drawing)
{
	ddIFigure *target = findConnectableFigure(x,y,drawing);
	if(target)
		return target->connectorAt(x,y);
	else
		return NULL;
}
