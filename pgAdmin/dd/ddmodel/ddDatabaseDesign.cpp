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

// App headers
#include "dd/ddmodel/ddDatabaseDesign.h"
#include "dd/draw/tools/ddSelectionTool.h"



//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks

ddDatabaseDesign::ddDatabaseDesign(wxWindow *parent)
{
	draw = new ddDrawingEditor(parent);
	tool = new ddSelectionTool(draw);
	draw->setTool(tool);
}

ddDatabaseDesign::~ddDatabaseDesign()
{
//DD-TODO: need to delete this tool? exception raised sometimes
/*	if(tool)
		delete tool;
		*/
	if(draw)
		delete draw;
}

ddDrawingEditor* ddDatabaseDesign::getEditor()
{
	return draw;
}

ddDrawingView* ddDatabaseDesign::getView()
{
	return draw->view();
}

void ddDatabaseDesign::addTable(ddIFigure *figure)
{
	draw->view()->add(figure);
}

void ddDatabaseDesign::setTool(ddITool* tool)
{
	draw->setTool(tool);
}


//DD-TODO: change parameter type by a table type


/*
ddDrawing::ddDrawing()
{
	figures = new ddCollection(new ddArrayCollection());
}

ddDrawing::~ddDrawing()
{
	ddIFigure *tmp;
	while(figures->count()>0)
	{
		tmp = (ddIFigure*) figures->getItemAt(0);
		figures->removeItemAt(0);
		delete tmp;
	}
	if(figures)
		delete figures;
}



void ddDrawing::add(ddIFigure *figure){
	if(figures)
		figures->addItem(figure);	
	//DD-TODO: remove handle
	//RecalculateDisplayBox???

}

void ddDrawing::remove(ddIFigure *figure){
    if(figures)
		figures->removeItem(figure);

	//DD-TODO: remove handle
	//RecalculateDisplayBox???
}


bool ddDrawing::includes(ddIFigure *figure){
	if(figures)
		return figures->existsObject(figure);
	return false;
}

ddIFigure* ddDrawing::findFigure(int x, int y){
	ddIFigure *tmp=NULL, *out=NULL;
	ddIteratorBase *iterator=figures->createIterator();
	while(iterator->HasNext()){
		 tmp=(ddIFigure *)iterator->Next();
		 if(tmp->containsPoint(x,y)){
			out=tmp;
			break;
		 }
	}

	delete iterator;;

	return out;
}

void ddDrawing::recalculateDisplayBox(){
	//DD-TODO: do it
	
	//displayBox = new ddRect();
	bool first=true;
	ddIFigure *figure=NULL;

	ddIteratorBase *iterator = figures->createIterator();
	while(iterator->HasNext())
	{
		figure=(ddIFigure *)iterator->Next();
		if(first)
		{
			displayBox=figure->displayBox();
			first=false;
		}
		else
		{
			displayBox.add(figure->displayBox());
		}
	}

	delete iterator;	
}

void ddDrawing::bringToFront(ddIFigure *figure){
	//DD-TODO: do it
}

void ddDrawing::sendToBack(ddIFigure *figure){
	//DD-TODO: do it
}


ddRect& ddDrawing::DisplayBox(){
	return displayBox;
}

ddIteratorBase* ddDrawing::figuresEnumerator(){
	return figures->createIterator();
}


ddIteratorBase* ddDrawing::figuresInverseEnumerator(){
	return figures->createDownIterator();
}

//DD-TODO: need to do this delete to handles too?
void ddDrawing::deleteFigures(){
	figures->deleteAll();
}

*/