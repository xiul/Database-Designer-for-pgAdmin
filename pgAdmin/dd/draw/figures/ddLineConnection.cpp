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
#include "dd/draw/figures/ddLineConnection.h"
#include "dd/draw/handles/ddChangeConnectionStartHandle.h"
#include "dd/draw/handles/ddChangeConnectionEndHandle.h"
#include "dd/draw/handles/ddLineConnectionHandle.h"
#include "dd/draw/locators/ddPolyLineLocator.h"
#include "dd/draw/utilities/ddArrayCollection.h"

ddLineConnection::ddLineConnection():
ddPolyLineFigure()
{
	startConnector = NULL;
	endConnector = NULL;
	connectionHandles = new ddCollection(new ddArrayCollection());
}

ddLineConnection::ddLineConnection(ddIFigure *figure1, ddIFigure *figure2):
ddPolyLineFigure()
{
	startConnector = NULL;
	endConnector = NULL;

	if(figure1)
	{
		connectStart(figure1->connectorAt(0,0));
	}

	if(figure2)
	{
		connectEnd(figure2->connectorAt(0,0));
	}
}

ddLineConnection::~ddLineConnection()
{
	//DD-TODO: destroy here created objects from others classes
}

ddIConnector* ddLineConnection::getStartConnector()
{
	return startConnector;
}

ddIConnector* ddLineConnection::getEndConnector()
{
	return endConnector;
}

void ddLineConnection::setStartConnector(ddIConnector* connector)
{
	startConnector = connector;
}

void ddLineConnection::setEndConnector(ddIConnector* connector)
{
	endConnector = connector;
}

void ddLineConnection::connectStart(ddIConnector *start)
{
	if(startConnector == start)
	{
		return;
	}
	
	disconnectStart();
	startConnector = start;
	connectFigure(startConnector);
}

void ddLineConnection::connectEnd(ddIConnector *end)
{
	if(endConnector == end)
	{
		return;
	}
	
	disconnectEnd();
	endConnector = end;
	connectFigure(endConnector);
}

void ddLineConnection::disconnectStart()
{
	disconnectFigure (startConnector);
	startConnector = NULL;
}

void ddLineConnection::disconnectEnd()
{
	disconnectFigure (endConnector);
	endConnector = NULL;
}

bool ddLineConnection::canConnectStart(ddIFigure *figure)
{
	return true;
}

bool ddLineConnection::canConnectEnd(ddIFigure *figure)
{
	return true;
}

ddIFigure* ddLineConnection::getStartFigure()
{
	if(startConnector)
	{
		return startConnector->getOwner();
	}

	return NULL;
}

ddIFigure* ddLineConnection::getEndFigure()
{
	if(endConnector)
	{
		return endConnector->getOwner();
	}

	return NULL;
}

void ddLineConnection::updateConnection(){
	//DD-TODO: avoid memory leak from thiw new ddPoint
	if(startConnector)
	{
		setStartPoint(new ddPoint(startConnector->findStart(this)));
	}
	if(endConnector)
	{
		setEndPoint(new ddPoint(endConnector->findEnd(this)));
	}
}

ddIHandle* ddLineConnection::getStartHandle()
{
	return new ddChangeConnectionStartHandle(this);
}

ddIHandle* ddLineConnection::getEndHandle()
{
	return new ddChangeConnectionEndHandle(this);
}

void ddLineConnection::basicMoveBy(int x, int y){
	ddPoint *newPoint;
	for(int i=1 ; i<points->count()-1 ; i++){
		newPoint = (ddPoint *) points->getItemAt(i);  //DD-TODO: replace and test with pointAt
		newPoint->x += x;
		newPoint->y += y;
		points->replaceAtIndex((ddObject *) newPoint,i); //DD-TODO: this is neede because I'm working with pointers??
	}
	updateConnection();
}

bool ddLineConnection::canConnect()
{
	return false;
}

void ddLineConnection::setPointAt (int index, int x, int y)
{
	ddPolyLineFigure::setPointAt(index,x,y);
	updateConnection();
}

ddCollection* ddLineConnection::handlesEnumerator(){
	//DD-TODO: HIGH-PRIORITY-FINISH-THIS optimize this, not create a new instance everytime invoke function
	connectionHandles->deleteAll();
	if( points->count()< 2 )
		return connectionHandles;  //return empty handle
	
	connectionHandles->addItem(getStartHandle());
	for(int i=0;i<points->count();i++){
		connectionHandles->addItem(new ddLineConnectionHandle(this, new ddPolyLineLocator(i), i));
	}
	connectionHandles->addItem(getEndHandle());

	return connectionHandles;
}


void ddLineConnection::connectFigure (ddIConnector *connector)
{
	if(connector)
	{
		//connector->getOwner()->figureChangedEvent ADD handler (observer pattern)
		//DD-TODO: HIGH-PRIORITY-FINISH-THIS observer pattern
		connector->getOwner()->onFigureChanged(reinterpret_cast<ddIFigure*>(this));
		connector->getOwner()->addDependentFigure(reinterpret_cast<ddIFigure*>(this));
	}
}

void ddLineConnection::disconnectFigure (ddIConnector *connector)
{
	if(connector)
	{
		//DD-TODO: HIGH-PRIORITY-FINISH-THIS observer pattern
		connector->getOwner()->onFigureChanged(this);
		connector->getOwner()->removeDependentFigure(this);
		//DD-TODO: is there any other option to reinterpret_cast?
	}
}

//DD-TODO: HIGH-PRIORITY-FINISH-THIS observer pattern
void ddLineConnection::onFigureChanged(ddIFigure *figure)
{
//		ddIConnectionFigure::onFigureChanged(figure);
		//666 BUGSISIMO updateConnection();
}

ddPoint* ddLineConnection::getStartPoint()
{
	return ddPolyLineFigure::getStartPoint();
}

void ddLineConnection::setStartPoint(ddPoint *point)
{
	ddPolyLineFigure::setStartPoint(point);
}

ddPoint* ddLineConnection::getEndPoint()
{
	return ddPolyLineFigure::getEndPoint();
}

void ddLineConnection::setEndPoint(ddPoint *point)
{
	ddPolyLineFigure::setEndPoint(point);
}

ddPoint* ddLineConnection::pointAt(int index)
{
	return ddPolyLineFigure::pointAt(index);
}

void ddLineConnection::splitSegment(int x, int y)
{
	ddPolyLineFigure::splitSegment(x,y);
}

int ddLineConnection::pointCount()
{
	return ddPolyLineFigure::pointCount();
}
