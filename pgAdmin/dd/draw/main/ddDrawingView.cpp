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
#include "dd/draw/utilities/ddGeometry.h"
#include "dd/draw/utilities/ddMouseEvent.h"

//Images
#include "images/check.xpm"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


BEGIN_EVENT_TABLE(ddDrawingView, wxScrolledWindow)
EVT_PAINT(ddDrawingView::onPaint)
EVT_MOTION(ddDrawingView::onMotion)
EVT_RIGHT_DOWN(ddDrawingView::onMouseDown)
EVT_LEFT_DOWN(ddDrawingView::onMouseDown)
EVT_LEFT_DCLICK(ddDrawingView::onMouseDown)
EVT_LEFT_UP(ddDrawingView::onMouseUp)
EVT_ERASE_BACKGROUND(ddDrawingView::onEraseBackGround)  //This erase flicker
EVT_TEXT(1979,ddDrawingView::simpleTextToolChangeHandler)
EVT_BUTTON(1980,ddDrawingView::OnOkTxtButton)
EVT_BUTTON(1981,ddDrawingView::OnCancelTxtButton)
END_EVENT_TABLE()

//DD-TODO replace numeric constants in events id for alphanumeric constants id

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
: wxScrolledWindow(ddParent, wxID_ANY, wxPoint(0,0), size,
wxHSCROLL | wxVSCROLL | wxBORDER | wxRETAINED)
{
	drawing=initialDrawing;
	drawingEditor=editor;
	canvasSize=size;
	SetVirtualSizeHints(canvasSize);
	selection =  new ddCollection(new ddArrayCollection());
	//Hack to avoid selection rectangle drawing bug
	drawSelRect = false;
	//Hack to avoid event problem with simpleTextTool wxTextCrtl at EVT_TEXT event
	simpleTextToolEdit = new wxTextCtrl(this,1979,wxT(""),wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
	simpleTextToolEdit->Hide();
	simpleTextFigure = NULL;
	menuFigure = NULL;
	okTxtButton = new wxBitmapButton(this,1980,wxBitmap(check_xpm),wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
	okTxtButton->Hide();
	cancelTxtButton = new wxBitmapButton(this,1981,wxBitmap(check_xpm),wxDefaultPosition,wxDefaultSize,wxBORDER_NONE);
	cancelTxtButton->Hide();
	//popTextUpItems=NULL;
}

ddDrawingView::~ddDrawingView()
{
	if(selection)
	{
		selection->removeAll();
		delete selection;
	}
	if(simpleTextToolEdit)
		delete simpleTextToolEdit;
	if(okTxtButton)
		delete okTxtButton;
	if(cancelTxtButton)
		delete cancelTxtButton;

/*	if(popTextUpItems)
		delete popTextUpItems;
		*/
}

void ddDrawingView::onPaint(wxPaintEvent& event)
{
	wxPaintDC dcc(this);                          // Prepare Context for Buffered Draw
    wxBufferedDC dc(&dcc, canvasSize);
	dc.Clear();
	ddIFigure *toDraw=NULL;
	ddIteratorBase *iterator=drawing->figuresEnumerator();
	while(iterator->HasNext()){
		 toDraw =(ddIFigure *)iterator->Next();
		 //wxPoint ptOrigin = wxPoint(toDraw->displayBox().GetPosition());
		 //this->CalcScrolledPosition(ptOrigin.x,ptOrigin.y,&ptOrigin.x,&ptOrigin.y);
		 if(toDraw->isSelected())
			toDraw->drawSelected(dc,this);	
		 else
			toDraw->draw(dc,this);			
	}

	delete iterator;

	//DD-TODO: Delete all iterators after use it

	ddIHandle *tmpHandle=NULL;
	ddIteratorBase *selectionIterator=selection->createIterator();
	while(selectionIterator->HasNext()){
		 toDraw=(ddIFigure *)selectionIterator->Next();
		 ddIteratorBase *handlesIterator = toDraw->handlesEnumerator()->createIterator();
		 while(handlesIterator->HasNext()){
			 tmpHandle = (ddIHandle *)handlesIterator->Next();
			 tmpHandle->draw(dc,this);
		 }
		 delete handlesIterator;
	}

	delete selectionIterator;

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
	delete iterator;
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
		 while(handlesIterator->HasNext())
		 {
			 tmpHandle = (ddIHandle *)handlesIterator->Next();
			 if(tmpHandle->containsPoint(x,y))
			 {
				 out=tmpHandle;
				 break;
			 }
		 }
		 delete handlesIterator;
	}
	delete selectionIterator;
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
	ddMouseEvent ddEvent = ddMouseEvent(event,this);	
	if(event.Dragging())
	{
		drawingEditor->tool()->mouseDrag(ddEvent);
		//DD-TODO: need this ScrollToMakeVisible (point)??? 
	}
	else
	{
			drawingEditor->tool()->mouseMove(ddEvent);
	}
	this->Refresh();
}

void ddDrawingView::onMouseDown(wxMouseEvent& event)
{
	ddMouseEvent ddEvent = ddMouseEvent(event,this);
	drawingEditor->tool()->mouseDown(ddEvent);
	this->Refresh();
}

void ddDrawingView::onMouseUp(wxMouseEvent& event){
	ddMouseEvent ddEvent = ddMouseEvent(event,this);
	drawingEditor->tool()->mouseUp(ddEvent);
	this->Refresh();
}


//Hack to avoid event problem with simpleTextTool wxTextCrtl at EVT_TEXT event
void ddDrawingView::setSimpleTextToolFigure(ddSimpleTextFigure *figure)
{
	simpleTextFigure=figure;
	menuFigure=NULL;
	if(simpleTextFigure)
	{
		oldText=simpleTextFigure->getText();
		simpleTextToolEdit->SetValue(simpleTextFigure->getText());
		simpleTextToolEdit->SelectAll();
	}
}

//Hack to allow use (events) of wxmenu inside a tool Generic Way
void ddDrawingView::setMenuToolFigure(ddAbstractMenuFigure *figure)
{
	menuFigure=figure;
	simpleTextFigure=NULL;
}

//Hack to avoid event problem with simpleTextTool wxTextCrtl at EVT_TEXT event
void ddDrawingView::OnOkTxtButton(wxCommandEvent& event)
{
	drawingEditor->tool()->deactivate();
	simpleTextToolEdit->Hide();  
	okTxtButton->Hide();
	cancelTxtButton->Hide();
	setSimpleTextToolFigure(NULL);
}

//Hack to avoid event problem with simpleTextTool wxTextCrtl at EVT_TEXT event
void ddDrawingView::OnCancelTxtButton(wxCommandEvent& event)
{
	simpleTextToolEdit->SetValue(oldText);
	drawingEditor->tool()->deactivate();
	simpleTextToolEdit->Hide();  
	okTxtButton->Hide();
	cancelTxtButton->Hide();
	setSimpleTextToolFigure(NULL);
}

//Hack to avoid event problem with simpleTextTool wxTextCrtl at EVT_TEXT event
void ddDrawingView::simpleTextToolChangeHandler(wxCommandEvent& event)
{
	if(simpleTextFigure)
	{
		simpleTextFigure->setText(simpleTextToolEdit->GetValue());
		//getFontMetrics
		int width, height;
		wxWindowDC dc(this);
		dc.SetFont(GetFont());
		if(simpleTextFigure->getText(true).length()>5)
			dc.GetTextExtent(simpleTextFigure->getText(true),&width,&height);
		else
			dc.GetTextExtent(wxT("EMPTY"),&width,&height);
		//recalculateDisplayBox
		ddGeometry g;
		simpleTextFigure->displayBox().width = g.max(width,10)+simpleTextFigure->getPadding();
		simpleTextFigure->displayBox().height= g.max(height,10)+simpleTextFigure->getPadding();
		//calculateSizeEntry
		ddPoint p=simpleTextFigure->displayBox().GetPosition();
		CalcScrolledPosition(p.x,p.y,&p.x,&p.y);
		simpleTextToolEdit->SetPosition(p);
		simpleTextToolEdit->SetSize(simpleTextFigure->displayBox().GetSize());
		okTxtButton->SetPosition(wxPoint(p.x+simpleTextToolEdit->GetSize().GetWidth()+4,p.y));
		cancelTxtButton->SetPosition(wxPoint(okTxtButton->GetPosition().x+okTxtButton->GetSize().GetWidth()+4,p.y));
	}
	else
	{
		wxMessageDialog *error = new wxMessageDialog(NULL, wxT("Error locating ddSimpleTextTool figure"), wxT("Error!"), wxOK | wxICON_ERROR);
		error->ShowModal();
		delete error;
	}
	event.Skip();
}

//Hack to avoid event problem with simpleTextTool wxTextCrtl at EVT_TEXT event
wxTextCtrl* ddDrawingView::getSimpleTextToolEdit()
{
	return simpleTextToolEdit;
}

//Hack to avoid event problem with simpleTextTool wxTextCrtl at EVT_TEXT event
wxBitmapButton* ddDrawingView::getOkTxt()
{
	return okTxtButton;
}

//Hack to avoid event problem with simpleTextTool wxTextCrtl at EVT_TEXT event
wxBitmapButton* ddDrawingView::getCancelTxt()
{
	return cancelTxtButton;
}

//Hack to allow use (events) of wxmenu inside a tool like simpletexttool
void ddDrawingView::OnTextPopupClick(wxCommandEvent& event)
{
	if(simpleTextFigure)
		simpleTextFigure->OnTextPopupClick(event);
	else if(menuFigure)
		menuFigure->OnTextPopupClick(event);
	event.Skip();
}

//Hack to allow use (events) of wxmenu inside a tool like simpletexttool
void ddDrawingView::setTextPopUpList(wxArrayString &strings, wxMenu &mnu)
{
	//DD-TODO: choose a better id for event
	mnu.Disconnect(wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)(wxEventFunction) (wxCommandEventFunction) &ddDrawingView::OnTextPopupClick,NULL,this);
	int sz = strings.size();  //to avoid warning
	wxMenuItem *item = NULL;
	wxMenu *submenu = NULL;
	for(int i=0 ; i < sz ; i++){
			//String "--submenu--menu item--sub menu title" and "--subitem--" create and add items to last created submenu
			if(strings[i].Contains(wxT("--submenu--"))) //DD-TODO: add other parameters to string
			{
				submenu = new wxMenu(strings[i].SubString(strings[i].find(wxT("--"),11)+2,strings[i].length())); 
				mnu.AppendSubMenu(submenu,strings[i].SubString(11,strings[i].find(wxT("--"),11)-1));
			}
			else if(strings[i].Contains(wxT("--subitem--")))
			{
				if(submenu)
					submenu->Append(i,strings[i].SubString(11,strings[i].length()));
			}
			else
			{
				 item = mnu.Append(i, strings[i]);
			}
		}
// Faltan Eventos
	mnu.Connect(wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)(wxEventFunction) (wxCommandEventFunction) &ddDrawingView::OnTextPopupClick,NULL,this);
}

ddDrawingEditor* ddDrawingView::editor()
{
	return drawingEditor;
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