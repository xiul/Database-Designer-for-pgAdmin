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
#include "dd/draw/locators/ddILocator.h"
#include "dd/draw/handles/ddPolyLineHandle.h"
#include "dd/draw/figures/ddLineTerminal.h"
#include "dd/draw/locators/ddPolyLineLocator.h"
#include "dd/draw/utilities/ddGeometry.h"
#include "dd/draw/tools/ddPolyLineFigureTool.h"

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
	//DD-TODO: need to delete start point if overwrite it??
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

ddCollection* ddPolyLineFigure::handlesEnumerator(){
	//DD-TODO: HIGH-PRIORITY-FINISH-THIS optimize this, not create a new instance everytime invoke function
	handles->deleteAll();
	for(int i=0;i<points->count();i++){
		handles->addItem(new ddPolyLineHandle(this, new ddPolyLineLocator(i), i));
	}

	return handles;
}

void ddPolyLineFigure::addPoint (int x, int y){
	willChange();
	points->addItem((ddObject *) new ddPoint(x,y) );
	changed();
}

void ddPolyLineFigure::removePoint (int i){
	willChange();
	points->removeItemAt(i);
	changed();
}

void ddPolyLineFigure::basicDraw(wxBufferedDC& context){
	if(points->count() < 2)
	{
		return;
	}
	//DD-TODO: HIGH-PRIORITY-FINISH-THIS set context attributes: width, round join, color, dashes

	ddPoint *start, *end;

	if(startTerminal)
	{
		start = startTerminal->draw(context, getStartPoint(), pointAt(1));
	}
	else
	{
		start = getStartPoint();
	}

	if(endTerminal)
	{
		end = endTerminal->draw(context, getEndPoint(), pointAt(pointCount() - 2));
	}
	else
	{
		end = getEndPoint();
	}

	//DD-TODO: Are There any way of use DrawLines instead of DrawLine?
	for(int i=0;i<points->count()-1;i++){
		ddPoint *p1 = (ddPoint *) points->getItemAt(i);
		ddPoint *p2 = (ddPoint *) points->getItemAt(i+1);

		context.DrawLine(*p1,*p2);
	}
}

void ddPolyLineFigure::basicMoveBy(int x, int y){
	ddPoint *newPoint;
	for(int i=0 ; i<points->count() ; i++){
		newPoint = (ddPoint *) points->getItemAt(i);  //DD-TODO: replace and test with pointAt
		newPoint->x += x;
		newPoint->y += y;
		points->insertAtIndex((ddObject *) newPoint,i); //DD-TODO: this is neede because I'm working with pointers??
	}
}

ddITool* ddPolyLineFigure::CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool)
{
	return new ddPolyLineFigureTool(editor,this,defaultTool);
	//DD-TODO: check what is done with all new objects return from function because they should be destroyed/delete
}

int ddPolyLineFigure::findSegment (int x, int y){
	for(int i=0 ; i<points->count()-1 ; i++){
		ddPoint *p1 = pointAt(i);
		ddPoint *p2 = pointAt(i+1);
		ddGeometry g;
		if(g.lineContainsPoint(p1->x, p1->y, p2->x, p2->y, x, y)){
			return i+1;
		}
	}
	return -1;
}

ddPoint* ddPolyLineFigure::pointAt(int index)
{
	return (ddPoint *)points->getItemAt(index);
}

bool ddPolyLineFigure::containsPoint (int x, int y){
	//DD-TODO: HIGH-PRIORITY-FINISH-THIS  Search in all inflate references value pass using value not reference to not modify value
	ddRect rect = ddRect(this->displayBox());
	rect.Inflate(4,4);
	if(!rect.Contains(x,y)){
		return false;
	}

	for(int i=0 ; i<points->count()-1 ; i++){
		ddPoint *p1 = pointAt(i);
		ddPoint *p2 = pointAt(i+1);
		ddGeometry g;
		if(g.lineContainsPoint(p1->x, p1->y, p2->x, p2->y, x, y)){
			return true;
		}
	}
	return false;
}

void ddPolyLineFigure::clearPoints()
{
	points->deleteAll();
}


void ddPolyLineFigure::splitSegment(int x, int y) 
{
	int index = findSegment(x,y);

	if(index!=-1)
	{
		insertPointAt( hacer esto
	}
}



/*




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
