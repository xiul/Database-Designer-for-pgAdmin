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
#include "dd/draw/ddDrawingEditor.h"

BEGIN_EVENT_TABLE(ddDrawingView, wxScrolledWindow)
EVT_PAINT(ddDrawingView::onPaint)
EVT_MOTION(ddDrawingView::onMotion)
EVT_LEFT_DOWN(ddDrawingView::onMouseDown)
EVT_LEFT_UP(ddDrawingView::onMouseUp)
END_EVENT_TABLE()

/*
EVT_RIGHT_DOWN(ddDrawingView::onRightClick)
EVT_LEFT_DCLICK(ddDrawingView::onDoubleClick)
EVT_KEY_DOWN(ddDrawingView::OnKeyDown)

/*
    * EVT_LEFT_DOWN(func):
      Process a wxEVT_LEFT_DOWN event. The handler of this event should normally call event.Skip() to allow the default processing to take place as otherwise the window under mouse wouldn't get the focus.
    * EVT_LEFT_UP(func):
      Process a wxEVT_LEFT_UP event.
    * EVT_LEFT_DCLICK(func):
      Process a wxEVT_LEFT_DCLICK event.
    * EVT_MIDDLE_DOWN(func):
      Process a wxEVT_MIDDLE_DOWN event.
    * EVT_MIDDLE_UP(func):
      Process a wxEVT_MIDDLE_UP event.
    * EVT_MIDDLE_DCLICK(func):
      Process a wxEVT_MIDDLE_DCLICK event.
    * EVT_RIGHT_DOWN(func):
      Process a wxEVT_RIGHT_DOWN event.
    * EVT_RIGHT_UP(func):
      Process a wxEVT_RIGHT_UP event.
    * EVT_RIGHT_DCLICK(func):
      Process a wxEVT_RIGHT_DCLICK event.
    * EVT_MOUSE_AUX1_DOWN(func):
      Process a wxEVT_AUX1_DOWN event.
    * EVT_MOUSE_AUX1_UP(func):
      Process a wxEVT_AUX1_UP event.
    * EVT_MOUSE_AUX1_DCLICK(func):
      Process a wxEVT_AUX1_DCLICK event.
    * EVT_MOUSE_AUX2_DOWN(func):
      Process a wxEVT_AUX2_DOWN event.
    * EVT_MOUSE_AUX2_UP(func):
      Process a wxEVT_AUX2_UP event.
    * EVT_MOUSE_AUX2_DCLICK(func):
      Process a wxEVT_AUX2_DCLICK event.
    * EVT_MOTION(func):
      Process a wxEVT_MOTION event.
    * EVT_ENTER_WINDOW(func):
      Process a wxEVT_ENTER_WINDOW event.
    * EVT_LEAVE_WINDOW(func):
      Process a wxEVT_LEAVE_WINDOW event.
    * EVT_MOUSEWHEEL(func):
      Process a wxEVT_MOUSEWHEEL event.
    * EVT_MOUSE_EVENTS(func):
      Process all mouse events.
*/

ddDrawingView::ddDrawingView(wxWindow *ddParent, ddDrawingEditor *editor, wxSize size, ddDrawing *initialDrawing)// gqbController *controller, gqbModel *model)
: wxScrolledWindow(ddParent, wxID_ANY, wxPoint(201,0), size,
wxHSCROLL | wxVSCROLL | wxBORDER | wxRETAINED)
{
	drawing=initialDrawing;
	drawingEditor=editor;
	canvasSize=size;
	SetVirtualSizeHints(size);
	selection =  new ddCollection(new ddArrayCollection());
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

ddDrawing* ddDrawingView::getDrawing(){
	return drawing;
}

void ddDrawingView::onMotion(wxMouseEvent& event)
{
	if(event.Dragging())
	{
		drawingEditor->tool()->mouseDrag(event);
		//DD-TODO: need this ScrollToMakeVisible (point); 
	}
	else
	{
		drawingEditor->tool()->mouseMove(event);
	}
}

void ddDrawingView::onMouseDown(wxMouseEvent& event){
	drawingEditor->tool()->mouseDown(event);
}

void ddDrawingView::onMouseUp(wxMouseEvent& event){
	drawingEditor->tool()->mouseUp(event);
}


/*void ddDrawingView::OnKeyDown(wxKeyEvent& event)
{
/*    if(event.GetKeyCode() == WXK_DELETE)
    {
        if(collectionSelected)
        {
            this->joinsGridTable->removeJoins(collectionSelected);
            controller->removeTableFromModel(collectionSelected,gridTable,orderByLGridTable,orderByRGridTable);
            collectionSelected=NULL;
            this->Refresh();
        }

        if(joinSelected)
        {
            this->joinsGridTable->removeJoin(joinSelected);
            controller->removeJoin(joinSelected);
            joinSelected=NULL;
            this->Refresh();
        }
    }
}/*







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