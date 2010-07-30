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
#include "dd/draw/figures/ddCompositeFigure.h"
#include "dd/draw/figures/ddIFigure.h"
#include "dd/draw/utilities/ddArrayCollection.h"
#include "dd/draw/tools/ddCompositeFigureTool.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddCompositeFigure::ddCompositeFigure(){
	figureFigures = new ddCollection(new ddArrayCollection());
	figureHandles = new ddCollection(new ddArrayCollection());
}

ddCompositeFigure::~ddCompositeFigure(){

	ddIHandle *tmpH;
	//figureHandles->removeAll();  //Handles should be delete by their owner (figure)
	while(figureHandles->count()>0)
	{
		tmpH = (ddIHandle*) figureHandles->getItemAt(0);
		figureHandles->removeItemAt(0);
		delete tmpH;
	}
	if(figureHandles)
		delete figureHandles;  


	ddIFigure *tmp;
	while(figureFigures->count()>0)
	{
		tmp = (ddIFigure*) figureFigures->getItemAt(0);
		figureFigures->removeItemAt(0);
		delete tmp;
	}
	if(figureFigures)
		delete figureFigures;
}

void ddCompositeFigure::basicMoveBy(int x, int y)
{
	ddIteratorBase *iterator=figuresEnumerator();
	while(iterator->HasNext()){
		ddIFigure *f = (ddIFigure *) iterator->Next();
		f->moveBy(x,y);
	}
	delete iterator;
}

bool ddCompositeFigure::containsPoint(int x, int y)
{
	bool out = false;
	ddIteratorBase *iterator=figuresEnumerator();
	while(iterator->HasNext()){
		ddIFigure *f = (ddIFigure *) iterator->Next();
		if(f->containsPoint(x,y))
		{
			out=true;  //avoid memory leak
		}
	}
	delete iterator;
	return out;
}

ddIteratorBase* ddCompositeFigure::figuresEnumerator()
{
	return figureFigures->createIterator();
}

ddIteratorBase* ddCompositeFigure::figuresInverseEnumerator()
{
	return figureFigures->createDownIterator();
}

ddRect& ddCompositeFigure::getBasicDisplayBox()
{
	basicDisplayBox.SetPosition(wxPoint(0,0));
	basicDisplayBox.SetSize(wxSize(0,0));
	bool firstFigure = true;

	ddIteratorBase *iterator=figuresEnumerator();
	while(iterator->HasNext()){
		ddIFigure *f = (ddIFigure *) iterator->Next();
		if(firstFigure)
		{
			basicDisplayBox.SetPosition( f->displayBox().GetPosition());
			basicDisplayBox.SetSize( f->displayBox().GetSize());
			firstFigure = false;
		}
		else
		{
			basicDisplayBox.add( f->displayBox() );
		}
	}
	delete iterator;
	return basicDisplayBox;

}

ddCollection* ddCompositeFigure::handlesEnumerator()
{
	return figureHandles;
}

void ddCompositeFigure::add(ddIFigure *figure)
{
	if(includes(figure))
		return;
	
	//Add figure
	figureFigures->addItem(figure);
	//Add figure handles
	ddIteratorBase *handlesIterator = figure->handlesEnumerator()->createIterator();
	while(handlesIterator->HasNext())
	{
		ddIHandle *h = (ddIHandle *) handlesIterator->Next();
		figureHandles->addItem(h);
	}
	delete handlesIterator;
}

void ddCompositeFigure::remove(ddIFigure *figure)
{
	if(!includes(figure))
		return;
	
	//Remove figure handles
	ddIteratorBase *handlesIterator = figure->handlesEnumerator()->createIterator();
	while(handlesIterator->HasNext())
	{
		ddIHandle *h = (ddIHandle *) handlesIterator->Next();
		figureHandles->removeItem(h);
		//DD-TODO: should I delete this handle?
	}
	delete handlesIterator;
	//Remove figure
	figureFigures->removeItem(figure);
	//DD-TODO: should I delete this figure?
}

bool ddCompositeFigure::includes(ddIFigure *figure)
{
	if(ddAbstractFigure::includes(figure))
		return true;
	
	bool out = false;

	ddIteratorBase *iterator=figuresEnumerator();
	while(iterator->HasNext()){
		ddIFigure *f = (ddIFigure *) iterator->Next();
		if(f->includes(figure))
			out = true;
	}
	
	delete iterator;
	return out;
}

void ddCompositeFigure::draw(wxBufferedDC& context, ddDrawingView *view)
{
	ddIteratorBase *iterator = figuresEnumerator();
	ddIFigure *f=NULL;
	while(iterator->HasNext()){
		f = (ddIFigure *) iterator->Next();
		f->draw(context,view);
	}
	delete iterator;
}

void ddCompositeFigure::drawSelected(wxBufferedDC& context, ddDrawingView *view)
{
	ddIteratorBase *iterator = figuresEnumerator();
	ddIFigure *f = NULL;
	while(iterator->HasNext()){
		 f = (ddIFigure *) iterator->Next();
		f->drawSelected(context,view);
	}
	delete iterator;
}

ddIFigure* ddCompositeFigure::findFigure(int x, int y)
{
	ddIFigure *tmp=NULL, *out=NULL;
	ddIteratorBase *iterator=figuresInverseEnumerator();
	while(iterator->HasNext()){
		 tmp=(ddIFigure *)iterator->Next();
		 if(tmp->containsPoint(x,y)){
			out=tmp;
			break;
		 }
	}

	delete iterator;

	return out;
}

ddITool* ddCompositeFigure::CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool)
{
	return new ddCompositeFigureTool(editor, this, defaultTool);
}

void ddCompositeFigure::sendToBack(ddIFigure *figure)
{
	//DD-TODO: Implement this function
}

void ddCompositeFigure::sendToFront(ddIFigure *figure)
{
	//DD-TODO: Implement this function
}


ddIFigure* ddCompositeFigure::getFigureAt(int pos)
{
	return (ddIFigure*) figureFigures->getItemAt(pos);
}
