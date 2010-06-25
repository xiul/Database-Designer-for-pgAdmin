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
#include "dd/draw/figures/ddSimpleTextFigure.h"
#include "dd/draw/tools/ddSimpleTextTool.h"
#include "dd/draw/utilities/ddGeometry.h"
/*
#include "dd/draw/handles/ddIHandle.h"
#include "dd/draw/utilities/ddArrayCollection.h"
#include "dd/draw/tools/ddITool.h"
#include "dd/draw/connectors/ddIConnector.h"
#include "dd/draw/connectors/ddChopBoxConnector.h"
*/


ddSimpleTextFigure::ddSimpleTextFigure(wxString textString)
{
	text = textString;
	textEditable = false;
	font = settings->GetSystemFont();
	textForeground = *wxBLACK;
	textBackground = wxBrush (wxColour(245, 245, 245),wxSOLID);
	refreshDisplayBox = true;
	padding = 2;
}

ddSimpleTextFigure::~ddSimpleTextFigure()
{
}

void ddSimpleTextFigure::setText(wxString textString)
{
	text = textString;
	refreshDisplayBox = true;
	//DD-TODO: update displaybox size
}
wxString& ddSimpleTextFigure::getText()
{
	return text;
}

void ddSimpleTextFigure::setFont(wxFont textFont)
{
	font = textFont;
	refreshDisplayBox = true;
}

void ddSimpleTextFigure::setForeground(wxColour colour)
{
	textForeground = colour;
	refreshDisplayBox = true;
}

void ddSimpleTextFigure::setBackground(wxBrush background)
{
	textBackground = background;
	refreshDisplayBox = true;
}

void ddSimpleTextFigure::getFontMetrics(int &width, int &height, wxBufferedDC& context)
{
	context.SetFont(font);
	context.GetTextExtent(wxT("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxtz"),&width,&height);
}



void ddSimpleTextFigure::recalculateDisplayBox(wxBufferedDC& context)
{
	int w,h;
	
	getFontMetrics(w,h,context);

	wxRect r = displayBox();
	
	ddGeometry g;
	r.width = g.max(w,10);
	r.height= g.max(h,10);
}

/*
ddRect& ddSimpleTextFigure::getBasicDisplayBox()
{
	return ddAbstractFigure::getBasicDisplayBox();
}
*/

void ddSimpleTextFigure::basicDraw(wxBufferedDC& context)
{
	if(refreshDisplayBox)
		recalculateDisplayBox(context);
	
	setupLayout(context);
	context.DrawText(text,getBasicDisplayBox().GetPosition());
}

void ddSimpleTextFigure::setupLayout(wxBufferedDC& context)
{
	context.SetFont(font);
	context.SetTextForeground(textForeground);
	context.SetBrush(textBackground);
}

//DD-TODO: Add event onTextChanged

void ddSimpleTextFigure::basicMoveBy(int x, int y)
{
	displayBox().x += x;
	displayBox().y += y;
}

ddITool* ddSimpleTextFigure::CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool)
{
	return textEditable ? new ddSimpleTextTool(editor,this,defaultTool) : defaultTool;
}

void ddSimpleTextFigure::setEditable(bool value)
{
	textEditable = value;
}



/*
			w = Math.Max (w, 10);
			h = Math.Max (h, 10);
			RectangleD r = new RectangleD (DisplayBox.X + Padding, DisplayBox.Y + Padding, 
									(double) w, (double) h);
			r.Inflate (Padding, Padding);
			_displayBox = r; 

/*
    // Get Value for row Height
    if(!rowHeight)
    {
        bdc.SetFont(TableTitleFont);
        bdc.GetTextExtent(wxT("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxtz"),&w,&h);
        rowHeight=h;
    }

    // Get Title Metrics
    bdc.SetFont(TableTitleFont);
    height+= rowHeight + rowTopMargin;

    // Calculate font metrics for table title with/without alias
    if(queryTable->getAlias().length()>0)
        bdc.GetTextExtent(queryTable->getName()+wxT(" (")+queryTable->getAlias()+wxT(")"),&w,&h);
    else
        bdc.GetTextExtent(queryTable->getName(),&w,&h);
    width= rowLeftMargin + w + rowRightMargin;




/*

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
*/


