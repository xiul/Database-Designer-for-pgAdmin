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
#include "dd/draw/ddDrawingView.h"
#include "dd/draw/ddArrayCollection.h"

BEGIN_EVENT_TABLE(ddDrawingView, wxScrolledWindow)
EVT_PAINT(ddDrawingView::onPaint)
END_EVENT_TABLE()


ddDrawingView::ddDrawingView(wxWindow *ddParent, wxSize size, ddDrawing *initialDrawing)// gqbController *controller, gqbModel *model)
: wxScrolledWindow(ddParent, wxID_ANY, wxPoint(201,0), size,
wxHSCROLL | wxVSCROLL | wxBORDER | wxRETAINED)
{
	drawing=initialDrawing;
	canvasSize=size;
	SetVirtualSizeHints(size);
}

ddDrawingView::~ddDrawingView()
{
}

//DD-TODO: set/get an Editor

void ddDrawingView::onPaint(wxPaintEvent& event)
{
    wxPaintDC dcc(this);                          // Prepare Context for Buffered Draw
    wxBufferedDC dc(&dcc, canvasSize);
	//dc.DrawRectangle(wxRect(wxPoint(5,5), wxSize(100,100)));
	ddIFigure *toDraw;
	ddIteratorBase *iterator=drawing->figuresEnumerator();
	while(iterator->HasNext()){
		 toDraw=(ddIFigure *)iterator->Next();
		 toDraw->draw(dc);
	}

}

void ddDrawingView::add(ddIFigure *figure){
	drawing->add(figure);
}


void ddDrawingView::remove(ddIFigure *figure){
	drawing->remove(figure);
}

/* ddCollection* ddDrawingView::insertFigures(ddCollection figures, double dx, double dy, bool check){

}
*/

void ddDrawingView::addToSelection(ddIFigure *figure){
	if(!selection){
		selection = new ddCollection(new ddArrayCollection());
	}
	selection->addItem(figure);	
}

void ddDrawingView::addToSelection(ddCollection *figures){
}

void ddDrawingView::removeFromSelection(ddIFigure *figure){
	if(selection){
		selection->removeItem(figure);		
	}
}

void ddDrawingView::toggleSelection(ddIFigure *figure){
}

void ddDrawingView::clearSelection(){
	selection->removeAll();
}

void ddDrawingView::ScrollToMakeVisible(wxPoint p){
}

void ddDrawingView::ScrollToMakeVisible (ddRect r){
}

ddIHandle* ddDrawingView::findHandle(double x, double y){
	ddIFigure *tmpFigure=NULL;
	ddIHandle *tmpHandle=NULL, *out=NULL;

	//DD-TODO: for each figure in SelectionEnumerator

	ddIteratorBase *selectionIterator=selection->createIterator();
	while(selectionIterator->HasNext()){
		 tmpFigure=(ddIFigure *)selectionIterator->Next();
		 ddIteratorBase *handlesIterator = tmpFigure->handlesEnumerator()->createIterator();
		 while(handlesIterator->HasNext()){
			 tmpHandle= (ddIHandle *)handlesIterator->Next();
			 if(tmpHandle->containsPoint(x,y)){
				 out=tmpHandle;
				 break;
			 }
		 }
	}
	return out;
}

bool ddDrawingView::isFigureSelected(ddIFigure *figure){
	return selection->existsObject(figure);
}

ddIteratorBase* ddDrawingView::selectionFigures(){
	return selection->createIterator();
}


/*


wxPoint ddDrawingView::drawingToView(double x, double y){
}

wxPoint ddDrawingView::viewToDrawing(double x, double y){
}

ddIDrawing* ddDrawingView::drawing(){
}

ddIDrawing* ddDrawingView::editor(){   //DD-TODO: debe retornar un editor
}



int ddDrawingView::selectionCount(){
}
ddRect ddDrawingView::visibleArea(){
}
*/