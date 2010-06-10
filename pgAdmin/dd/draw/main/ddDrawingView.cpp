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
#include "dd/draw/main/ddDrawingView.h"
#include "dd/draw/utilities/ddArrayCollection.h"
#include "dd/draw/main/ddDrawingEditor.h"

BEGIN_EVENT_TABLE(ddDrawingView, wxScrolledWindow)
EVT_PAINT(ddDrawingView::onPaint)
EVT_MOTION(ddDrawingView::onMotion)
EVT_LEFT_DOWN(ddDrawingView::onMouseDown)
EVT_LEFT_DCLICK(ddDrawingView::onMouseDown)
EVT_LEFT_UP(ddDrawingView::onMouseUp)
EVT_ERASE_BACKGROUND(gqbView::onEraseBackGround)  //This erase flicker
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
	drawSelRect = false;
}

ddDrawingView::~ddDrawingView()
{
}

//DD-TODO: set/get an Editor

void ddDrawingView::onPaint(wxPaintEvent& event)
{
	wxPaintDC dcc(this);                          // Prepare Context for Buffered Draw
    wxBufferedDC dc(&dcc, canvasSize);
	dc.Clear();
	ddIFigure *toDraw;
	ddIteratorBase *iterator=drawing->figuresEnumerator();
	while(iterator->HasNext()){
		 toDraw=(ddIFigure *)iterator->Next();
		 if(toDraw->isSelected())
			toDraw->drawSelected(dc);	
		 else
			toDraw->draw(dc);			
		 
	}
	
	if( drawSelRect ){  //Hack to avoid selection rectangle drawing bug
		wxPen* pen = wxThePenList->FindOrCreatePen(*wxRED, 1, wxDOT);
		dc.SetPen(*pen);
		wxBrush* brush = wxTheBrushList->FindOrCreateBrush(*wxRED,wxTRANSPARENT);
		dc.SetBackground(*brush);
		dc.SetBackgroundMode(wxTRANSPARENT);	
		dc.DrawLines(5, selPoints, 0, 0);
		drawSelRect = false;
	}
}


//Hack to avoid selection rectangle drawing bug
void ddDrawingView::disableSelRectDraw(){
	drawSelRect = false;
}

//Hack to avoid selection rectangle drawing bug
void ddDrawingView::setSelRect(ddRect& selectionRect){
	//Create rectangle lines to avoid non transparent brush for filling bug in wxwidgets
	selPoints[0].x=selectionRect.x;
	selPoints[0].y=selectionRect.y;
	selPoints[1].x=selectionRect.x+selectionRect.width;
	selPoints[1].y=selectionRect.y;
	selPoints[2].x=selectionRect.x+selectionRect.width;
	selPoints[2].y=selectionRect.y+selectionRect.height;
	selPoints[3].x=selectionRect.x;
	selPoints[3].y=selectionRect.y+selectionRect.height;
	selPoints[4].x=selectionRect.x;
	selPoints[4].y=selectionRect.y;
	drawSelRect = true;
}

// Overwrite and disable onEraseBackground Event to avoid Flicker
void ddDrawingView::onEraseBackGround(wxEraseEvent& event)
{
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
	if(figure){
		figure->setSelected(true);
		selection->addItem(figure);	
	}
}

void ddDrawingView::addToSelection(ddCollection *figures){
}

void ddDrawingView::removeFromSelection(ddIFigure *figure){
	figure->setSelected(false);
	if(selection){
		selection->removeItem(figure);		
	}
}


void ddDrawingView::toggleSelection(ddIFigure *figure){
	if(figure->isSelected() &&	selection->existsObject(figure)){
		selection->removeItem(figure);
	}
	else if(!figure->isSelected() && drawing->includes(figure))
	{
		selection->addItem(figure);
	}
	
	figure->setSelected(!figure->isSelected());
}

void ddDrawingView::clearSelection(){
	ddIFigure *tmp=NULL;
	ddIteratorBase *iterator=selection->createIterator();
	while(iterator->HasNext()){
		 tmp=(ddIFigure *)iterator->Next();
		 tmp->setSelected(false);
		 }
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
	this->Refresh();
}

void ddDrawingView::onMouseDown(wxMouseEvent& event){
	drawingEditor->tool()->mouseDown(event);
	this->Refresh();
}

void ddDrawingView::onMouseUp(wxMouseEvent& event){
	drawingEditor->tool()->mouseUp(event);
	this->Refresh();
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