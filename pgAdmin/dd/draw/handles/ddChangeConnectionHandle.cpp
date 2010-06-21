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

ddChangeConnectionHandle::ddChangeConnectionHandle(ddLineConnection *owner):
ddIHandle(owner)
{
	connection = owner;
	targetFigure = NULL;
	originalTarget = NULL;
}

ddChangeConnectionHandle::~ddChangeConnectionHandle(){
	
}

void ddChangeConnectionHandle::draw(wxBufferedDC& context)
{

	ddPoint points[5];
	points[0].x = getDisplayBox().center().x;
	points[0].y = getDisplayBox().GetTop();
	points[1].x = getDisplayBox().GetRight();
	points[1].y = getDisplayBox().center().y;
	points[2].x = getDisplayBox().x;
	points[2].y = getDisplayBox().GetBottom();
	points[3].x = getDisplayBox().GetLeft();
	points[3].y = getDisplayBox().center().y;
	points[4].x = getDisplayBox().center().x;
	points[4].y = getDisplayBox().GetTop();

	context.DrawPolygon(5,points,0,0);
}

wxCursor& ddChangeConnectionHandle::createCursor()
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
