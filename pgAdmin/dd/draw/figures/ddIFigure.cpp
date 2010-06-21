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
	connector=NULL;
	//DD-TODO: this should be initialize here
}

ddIFigure::~ddIFigure(){
	if(connector)
		delete connector;
	if(figures)
		delete figures;
	if(handles)
		delete handles;
	if(dependentFigures)
	{
		dependentFigures->removeAll();
		delete dependentFigures;
	}
	if(observers){
		observers->removeAll();
		delete observers;
	}
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
	if(!connector)
		connector = new ddChopBoxConnector(this);
	return connector;
}

bool ddIFigure::includes(ddIFigure *figure)
{
	return (this == figure);
}



void ddIFigure::onFigureChanged(ddIFigure *figure)
{

	ddIteratorBase *iterator=observers->createIterator();
	while(iterator->HasNext()){
		ddIFigure *o = (ddIFigure*) iterator->Next();
		o->onFigureChanged(this);
	}
	delete iterator;
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
		//DD-TODO: this delete the figure???? wxwidgets api is very bad documented
	}
}
