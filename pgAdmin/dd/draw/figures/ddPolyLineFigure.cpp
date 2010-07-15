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
#include <wx/pen.h>

// App headers
#include "dd/draw/figures/ddPolyLineFigure.h"
#include "dd/draw/utilities/ddArrayCollection.h"
#include "dd/draw/locators/ddILocator.h"
#include "dd/draw/handles/ddPolyLineHandle.h"
#include "dd/draw/figures/ddLineTerminal.h"
#include "dd/draw/locators/ddPolyLineLocator.h"
#include "dd/draw/utilities/ddGeometry.h"
#include "dd/draw/tools/ddPolyLineFigureTool.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddPolyLineFigure::ddPolyLineFigure(){
	points = new ddArrayCollection();
	startTerminal = NULL;
	endTerminal = NULL;
	handlesChanged = false;
	startPoint=ddPoint(0,0);
	endPoint=ddPoint(0,0);
	pointAtPos=ddPoint(0,0);
	//primero=true;
}

ddPolyLineFigure::~ddPolyLineFigure(){
	ddPoint *tmp; //Hack: If just delete points collection an error is raised.
	while(points->count()>0)
	{
		tmp = (ddPoint*) points->getItemAt(0);
		points->removeItemAt(0);
		delete tmp;
	}
	if(points)
		delete points;
	if(startTerminal)
		delete startTerminal;
	if(endTerminal)
		delete endTerminal;
}

ddRect& ddPolyLineFigure::getBasicDisplayBox() {
	
	//basicDisplayBox.
	basicDisplayBox.height=0;
	basicDisplayBox.width=0;
	if(points->count() < 2)
	{
		
		return basicDisplayBox;
	}
	if(points->count()>=1)
	{
		basicDisplayBox.SetPosition(pointAt(0));
	}
	else
	{
		basicDisplayBox.SetPosition(wxPoint(0,0));
	}

	ddIteratorBase *iterator=points->createIterator();
	while(iterator->HasNext()){
		ddPoint *p = (ddPoint *) iterator->Next();
		basicDisplayBox.add(ddRect(p->x,p->y,0,0));
	}
	
	delete iterator;

	return basicDisplayBox;
}

int ddPolyLineFigure::pointCount(){
 return points->count();
}

ddPoint& ddPolyLineFigure::getStartPoint(){
	//DD-TODO: fix [] operator not working here, bad casting info was shown
	startPoint.x = ((ddPoint*)points->getItemAt(0))->x;
	startPoint.y = ((ddPoint*)points->getItemAt(0))->y;
	return startPoint;
}

void ddPolyLineFigure::setStartPoint(ddPoint point){
	willChange();
	if(points->count()==0)
		addPoint(point.x,point.y);
	else
	{
		//points->replaceAtIndex((ddObject *)point,0);
		ddPoint *p = (ddPoint *) points->getItemAt(0);
		p->x = point.x;
		p->y = point.y;
	}
		
	changed();
	//DD-TODO: need to delete start point if overwrite it
}

ddPoint& ddPolyLineFigure::getEndPoint(){
	//DD-TODO: fix [] operator not working here, bad casting info was shown
	endPoint.x = ((ddPoint*)points->getItemAt(points->count()-1))->x;
	endPoint.y = ((ddPoint*)points->getItemAt(points->count()-1))->y;
	return endPoint;
}

void ddPolyLineFigure::setEndPoint(ddPoint point){
	willChange();
	if(points->count() < 2)
		addPoint(point.x,point.y);
	else{
		//points->insertAtIndex((ddObject *)point, points->count()-1); CREO que deberia ser replaceAtIndex de paso
		ddPoint *p = (ddPoint *) points->getItemAt(points->count()-1);
		p->x = point.x;
		p->y = point.y;
	}
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
/*	if(handlesChanged)
	{
		handles->deleteAll();
		for(int i=0;i<points->count();i++){
			handles->addItem(new ddPolyLineHandle(this, new ddPolyLineLocator(i), i));
		}
		handlesChanged = false;
		//primero=false;
	}
*/
	return handles;
}

void ddPolyLineFigure::addPoint (int x, int y){
	willChange();
	points->addItem((ddObject *) new ddPoint(x,y) );
	//Update handles
	handles->addItem(new ddPolyLineHandle(this, new ddPolyLineLocator(0), 0));
	updateHandlesIndexes(); //DD-TODO: move this method to changed()???
	changed();
}

void ddPolyLineFigure::changed()
{
	//if(primero)
	handlesChanged = true;
}

//DD-TODO: HIGH-PRIORITY-FINISH-THIS difference between this and below one
/*
void ddPolyLineFigure::removePoint (int index)
{
	willChange();
	points->removeItemAt(index);
	changed();
}
*/

void ddPolyLineFigure::removePointAt (int index)
{
	willChange();
	ddPoint *p = (ddPoint*) points->getItemAt(index);
	points->removeItemAt(index);
	delete p;
	//Update handles
	ddIHandle *h = (ddIHandle*) handles->getItemAt(index);
	handles->removeItemAt(index);
//DD-TODO: avoid this memory leak without a memory fail---->	delete h;
	//DD-TODO: delete all item after a getItemAt... research if this is need cause wxwidgets docs is not clear about this
	updateHandlesIndexes();
	changed();
}

void ddPolyLineFigure::basicDrawSelected(wxBufferedDC& context, ddDrawingView *view){
	basicDraw(context,view); //DD-TODO: HIGH-PRIORITY-FINISH-THIS: what to do when selected?
}

void ddPolyLineFigure::basicDraw(wxBufferedDC& context, ddDrawingView *view){
	if(points->count() < 2)
	{
		return;
	}
	//DD-TODO: HIGH-PRIORITY-FINISH-THIS set context attributes: width, round join, color, dashes

	ddPoint start, end;

	if(startTerminal)
	{
		start = startTerminal->draw(context, getStartPoint(), pointAt(1),view);
	}
	else
	{
		start = getStartPoint();
	}

	if(endTerminal)
	{
		end = endTerminal->draw(context, getEndPoint(), pointAt(pointCount() - 2),view);
	}
	else
	{
		end = getEndPoint();
	}

	//DD-TODO: Are There any way of use DrawLines instead of DrawLine?
	//DD-TODO: Draw when selected???
	context.SetPen(wxPen(wxColour(100, 100, 100),1,wxSOLID));
	/*
	ddRect rect = ddRect(this->displayBox());
	//rect.Inflate(4,4);
	context.DrawRectangle(rect);
	just for testing
*/
	for(int i=0;i<points->count()-1;i++){
		ddPoint *p1 = (ddPoint *) points->getItemAt(i);
		ddPoint *p2 = (ddPoint *) points->getItemAt(i+1);

		ddPoint copyP1 = ddPoint (*p1);
		view->CalcScrolledPosition(copyP1.x,copyP1.y,&copyP1.x,&copyP1.y);
		ddPoint copyP2 = ddPoint (*p2);
		view->CalcScrolledPosition(copyP2.x,copyP2.y,&copyP2.x,&copyP2.y);

		context.DrawLine(copyP1,copyP2);
	}
	//DD-TODO: this is really needed or I can change way end/startTerminal->draw works?
/*	delete start;
	delete end;
	*/
}

void ddPolyLineFigure::basicMoveBy(int x, int y){
	ddPoint *movPoint;
	for(int i=0 ; i<points->count() ; i++){
		movPoint = (ddPoint *) points->getItemAt(i);  //DD-TODO: replace and test with pointAt
		movPoint->x += x;
		movPoint->y += y;
		//points->replaceAtIndex((ddObject *) newPoint,i); //DD-TODO: this is neede because I'm working with pointers??
	}
}

ddITool* ddPolyLineFigure::CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool)
{
	return new ddPolyLineFigureTool(editor,this,defaultTool);
}

int ddPolyLineFigure::findSegment (int x, int y){
	for(int i=0 ; i<points->count()-1 ; i++){
		ddPoint p1 = pointAt(i);
		ddPoint p2 = pointAt(i+1);
		ddGeometry g;
		if(g.lineContainsPoint(p1.x, p1.y, p2.x, p2.y, x, y)){
			return i+1;
		}
	}
	return -1;
}

ddPoint& ddPolyLineFigure::pointAt(int index)
{
	//hack to avoid error with bad indexes calls
	if(index<0)
	{
		pointAtPos.x = 0;
		pointAtPos.y = 0;
	}
	else
	{
		pointAtPos.x = ((ddPoint*)points->getItemAt(index))->x;
		pointAtPos.y = ((ddPoint*)points->getItemAt(index))->y;
	}
	return pointAtPos;
}

bool ddPolyLineFigure::containsPoint (int x, int y){
	//DD-TODO: HIGH-PRIORITY-FINISH-THIS  Search in all inflate references value pass using value not reference to not modify value
	ddRect rect = ddRect(this->displayBox()); //DD-TODO: verify some displaybox returned here with incorrect values sometimes
	rect.Inflate(4,4);
	if(!rect.Contains(x,y)){
		return false;
	}

	for(int i=0 ; i<points->count()-1 ; i++){
		ddPoint p1 = pointAt(i);
		ddPoint p2 = pointAt(i+1);
		ddGeometry g;
		if(g.lineContainsPoint(p1.x, p1.y, p2.x, p2.y, x, y)){
			return true;
		}
	}
	return false;
}

void ddPolyLineFigure::clearPoints()
{
	points->deleteAll();
}

void ddPolyLineFigure::insertPointAt (int index, int x, int y)
{
	willChange();
	points->insertAtIndex((ddObject*) new ddPoint(x,y), index);
	//Update handles
	handles->insertAtIndex(new ddPolyLineHandle(this, new ddPolyLineLocator(index), index),index);
	updateHandlesIndexes();
	changed();
}

//DD-TODO: HIGH-PRIORITY-FINISH-THIS: possible source of bug between set and insert search for everyone at this project and solved it
void ddPolyLineFigure::setPointAt (int index, int x, int y)
{
	willChange();
	//points->replaceAtIndex((ddObject*) new ddPoint(x,y),index); 
	ddPoint *p = (ddPoint *) points->getItemAt(index);
	p->x = x;
	p->y = y;
	changed();
}

void ddPolyLineFigure::splitSegment(int x, int y) 
{
	int index = findSegment(x,y);

	if(index!=-1)
	{
		insertPointAt(index,x,y);
	}
}


//DD-TODO: this functions is deprecated and should be delete in the future
void ddPolyLineFigure::updateHandlesIndexes()
{
ddPolyLineHandle *h = NULL;
for(int i=0;i<points->count();i++){
	h = (ddPolyLineHandle*) handles->getItemAt(i);
	h->setIndex(i);
	}
/*handles->deleteAll();
for(int i=0;i<points->count();i++){
	handles->addItem(new ddPolyLineHandle(this, new ddPolyLineLocator(i), i));
	}
*/
}
