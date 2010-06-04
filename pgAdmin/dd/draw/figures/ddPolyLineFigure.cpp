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
#include "dd/draw/figures/ddPolyLineFigure.h"
#include "dd/draw/utilities/ddArrayCollection.h"


ddPolyLineFigure::ddPolyLineFigure(){
	points = new ddArrayCollection();
}

ddPolyLineFigure::~ddPolyLineFigure(){
	//DD-TODO: delete points
}

ddRect& ddPolyLineFigure::basicDisplayBox() {
	if(points->count() < 2)
	{
		basicDisplayBoxRect.SetPosition(wxPoint(0,0));
		basicDisplayBoxRect.height=0;
		basicDisplayBoxRect.width=0;
		return basicDisplayBoxRect;
	}

	ddIteratorBase *iterator=points->createIterator();
	while(iterator->HasNext()){
		ddPoint *p = (ddPoint *) iterator->Next();
		basicDisplayBoxRect.add(ddRect(p->x,p->y,0,0));
	}

	return basicDisplayBoxRect;
}

int ddPolyLineFigure::pointCount(){
 return points->count();
}

ddPoint* ddPolyLineFigure::getStartPoint(){
	//DD-TODO: fix [] operator not working here, bad casting info was shown
	return (ddPoint *) points->getItemAt(0);
}

void ddPolyLineFigure::setStartPoint(ddPoint *point){
	willChange();
	if(points->count()==0)
		addPoint(point->x,point->y);
	else
		points->insertAtIndex((ddObject *)point,0);
	changed();
	//DD-TODO: need to delete start point if overwrite it
}

ddPoint* ddPolyLineFigure::getEndPoint(){
	//DD-TODO: fix [] operator not working here, bad casting info was shown
	return (ddPoint *) points->getItemAt(points->count()-1);
}

void ddPolyLineFigure::setEndPoint(ddPoint *point){
	willChange();
	if(points->count() < 2)
		addPoint(point->x,point->y);
	else
		points->insertAtIndex((ddObject *)point, points->count()-1);
	changed();
	//DD-TODO: need to delete start point if overwrite it
}

void ddPolyLineFigure::setStartTerminal(ddLineTerminal *terminal){
	startTerminal=terminal;
}

ddLineTerminal* ddPolyLineFigure::getStartTerminal(){
	return startTerminal;
}

void ddPolyLineFigure::setEndTerminal(ddLineTerminal *terminal){
	endTerminal=terminal;
}

ddLineTerminal* ddPolyLineFigure::getEndTerminal(){
	return endTerminal;
}


void ddPolyLineFigure::basicDraw(wxBufferedDC& context){
	if(points->count() < 2)
	{
		return;
	}
	//DD-TODO: set context attributes: width, round join, color, dashes

	ddPoint start;
	ddPoint end;
}



void ddPolyLineFigure::addPoint (int x, int y){

}



/*
bool ddIFigure::containsPoint (int x, int y){
	return false;
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
