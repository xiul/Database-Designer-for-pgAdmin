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
#include "dd/draw/figures/ddIFigure.h"
#include "dd/draw/handles/ddIHandle.h"
#include "dd/draw/utilities/ddArrayCollection.h"
#include "dd/draw/tools/ddITool.h"
#include "dd/draw/connectors/ddIConnector.h"
#include "dd/draw/connectors/ddChopBoxConnector.h"



ddIFigure::ddIFigure(){
	figures=new ddCollection(new ddArrayCollection());
	handles=new ddCollection(new ddArrayCollection());
	dependentFigures=new ddCollection(new ddArrayCollection());
	observers=new ddCollection(new ddArrayCollection());
	selected=false;
	//DD-TODO: this should be initialize here
}

ddIFigure::~ddIFigure(){

}


ddRect& ddIFigure::displayBox() {
	return getBasicDisplayBox();
}

ddRect& ddIFigure::getBasicDisplayBox()
{
	return basicDisplayBox;
}

bool ddIFigure::containsPoint (int x, int y){
	return false;
}

void ddIFigure::draw (wxBufferedDC& context){
}

void ddIFigure::drawSelected (wxBufferedDC& context){
}

ddCollection* ddIFigure::handlesEnumerator(){
	return handles;
}


void ddIFigure::addDependentFigure (ddIFigure *figure){
	if(!dependentFigures){
		dependentFigures = new ddCollection(new ddArrayCollection());
	}
	dependentFigures->addItem(figure);	
}


void ddIFigure::removeDependentFigure (ddIFigure *figure){
	if(dependentFigures){
		dependentFigures->removeItem(figure);		
	}
}

void ddIFigure::addHandle (ddIHandle *handle){
	if(!handles){
		handles  = new ddCollection(new ddArrayCollection());
	}
	handles->addItem(handle);	
}

void ddIFigure::removeHandle (ddIHandle *handle){
	if(handles){
		handles->removeItem(handle);		
	}
}

void ddIFigure::moveBy (int x, int y){
}

void ddIFigure::moveTo(int x, int y){
}

ddITool* ddIFigure::CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool){
	return defaultTool;
}

bool ddIFigure::isSelected(){
	return selected;
}

void ddIFigure::setSelected(bool value){
	selected=value;
}


ddIConnector* ddIFigure::connectorAt (int x, int y)
{
	return new ddChopBoxConnector(this);
	//DD-TODO: HIGH-PRIORITY-FINISH-THIS avoid this memory leak
}

bool ddIFigure::includes(ddIFigure *figure)
{
	return (this == figure);
}



void ddIFigure::onFigureChanged(ddIFigure *figure)
{
//666  999 
/*
	ddIteratorBase *iterator=observers->createIterator();
	while(iterator->HasNext()){
		ddIFigure *o = (ddIFigure*) iterator->Next();
		o->onFigureChanged(figure);
	}
*/
}




void ddIFigure::addObserver(ddIFigure *observer)
{
	if(!observers){
		observers  = new ddCollection(new ddArrayCollection());
	}
	observers->addItem(observer);	
}

void ddIFigure::removeObserver(ddIFigure *observer)
{
	if(observers){
		observers->removeItem(observer);		
	}
}


/*

		RectangleD DisplayBox { get; set; }
		IEnumerable <IFigure> FiguresEnumerator { get; }
		IEnumerable <IHandle> HandlesEnumerator { get; }
		IEnumerable <IFigure> DependentFiguresEnumerator { get;	}
		bool CanConnect { get; }




//http://juanobligado.wordpress.com/2007/11/05/interfaces-con-c/
/*ddAbstractFigure::ddAbstractFigure()
{
}

ddAbstractFigure::~ddAbstractFigure()
{
}
*/
