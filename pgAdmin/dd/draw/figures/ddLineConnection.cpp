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
	changeConnStartHandle = NULL;
	changeConnEndHandle = NULL; 
	//connectionHandles = new ddCollection(new ddArrayCollection());
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
		setStartPoint(startConnector->findStart(this));  
	}
	if(endConnector)
	{
		setEndPoint(endConnector->findEnd(this));
	}
}

ddIHandle* ddLineConnection::getStartHandle()
{
	if(!changeConnStartHandle)
	{
		changeConnStartHandle =  new ddChangeConnectionStartHandle(this);
	}
	return changeConnStartHandle;
}

ddIHandle* ddLineConnection::getEndHandle()
{
	if(!changeConnEndHandle)
	{
		changeConnEndHandle =  new ddChangeConnectionEndHandle(this);
	}
	return changeConnEndHandle;
}

void ddLineConnection::basicMoveBy(int x, int y){
	/*ddPoint *newPoint;
	for(int i=1 ; i<points->count()-1 ; i++){
		newPoint = (ddPoint *) points->getItemAt(i);  //DD-TODO: replace and test with pointAt
		newPoint->x += x;
		newPoint->y += y;
		points->replaceAtIndex((ddObject *) newPoint,i); //DD-TODO: this is neede because I'm working with pointers??
	}*/
	ddPolyLineFigure::basicMoveBy(x,y);
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
	
	// //ARREGLAR ESTO PQ SI HAGO ESTO DARA PROBLEMAS CUANDO ELIMINE O AGREGUE COSAS
	//connectionHandles->removeAll(); //

	if( points->count()< 2 )
		return handles;  //return empty handle
	
	return handles;
}


void ddLineConnection::connectFigure (ddIConnector *connector)
{
	if(connector)
	{
		//connector->getOwner()->figureChangedEvent ADD handler (observer pattern)
		//DD-TODO: HIGH-PRIORITY-FINISH-THIS observer pattern
		//connector->getOwner()->onFigureChanged((ddIFigure*)this);
		connector->getOwner()->addObserver(this);
		connector->getOwner()->addDependentFigure((ddIFigure*)this);
	}
}

void ddLineConnection::disconnectFigure (ddIConnector *connector)
{
	if(connector)
	{
		//DD-TODO: HIGH-PRIORITY-FINISH-THIS observer pattern
		//connector->getOwner()->onFigureChanged(this);
		connector->getOwner()->removeObserver(this);
		connector->getOwner()->removeDependentFigure(this);
	}
}

//DD-TODO: HIGH-PRIORITY-FINISH-THIS observer pattern
void ddLineConnection::onFigureChanged(ddIFigure *figure)
{
//		ddIConnectionFigure::onFigureChanged(figure);
		//BUGSISIMO  ver si debe ir aqui pq da un super error 
	updateConnection();
}

void ddLineConnection::addPoint (int x, int y){
	willChange();
	points->addItem((ddObject *) new ddPoint(x,y) );
	//Update handles
	if(points->count()==1)
	{
		//first point add start handle
		handles->addItem(getStartHandle());
	}
	else if(points->count()==2)
	{
		//second point add end handle
		handles->addItem(getEndHandle());
	}
	else if(points->count()>2)
	{
		//third and above point, add a polylinehandle before end handle
		handles->insertAtIndex(new ddPolyLineHandle(this, new ddPolyLineLocator(0), 0),handles->count()-1);
	}
	updateHandlesIndexes();	
	changed();
}

void ddLineConnection::insertPointAt (int index, int x, int y)
{
	willChange();
	points->insertAtIndex((ddObject*) new ddPoint(x,y), index);
	//Update handles
	if(index==0)
	{
		//add a new handle "normal" for a point in next position 0,1 in 1... in 0 startHandle is not moved
		handles->insertAtIndex(new ddPolyLineHandle(this, new ddPolyLineLocator(index), index),1);
	}
	else if(index==(points->count()-1)) //last point
	{
		//add a new handle "normal" for a point in before last item position
		handles->insertAtIndex(new ddPolyLineHandle(this, new ddPolyLineLocator(index), index),(points->count()-1));
	}
	else
	{
		//add handle at index
		handles->insertAtIndex(new ddPolyLineHandle(this, new ddPolyLineLocator(index), index),index);
	}
	updateHandlesIndexes();
	changed();
}

//DD-TODO: this functions is deprecated and should be delete in the future
void ddLineConnection::updateHandlesIndexes()
{
	//DD-TODO: simplify this in the future, probably implementing locator in other way
	//start and end don't have index
	//update point between start and end
	ddPolyLineHandle *h = NULL;
	for(int i=1;i<handles->count()-1;i++)
	{
		h = (ddPolyLineHandle*) handles->getItemAt(i);
		h->setIndex(i);
	}

/*	for(int i=0;i<points->count()-1;i++)  //not include start and end handles
	{
		handles->removeItemAt(i);
	}
	handles->removeAll();  //don't delete because it cause start & end handle to be loss
	
	handles->addItem(getStartHandle());
	for(int i=1;i<points->count()-1;i++){
		handles->addItem(new ddLineConnectionHandle(this, new ddPolyLineLocator(i), i));
	}
	handles->addItem(getEndHandle());	
*/
}
