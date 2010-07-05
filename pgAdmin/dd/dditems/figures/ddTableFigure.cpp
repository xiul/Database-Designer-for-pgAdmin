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
#include "dd/dditems/figures/ddTableFigure.h"
#include "dd/dditems/figures/ddColumnFigure.h"
#include "dd/draw/main/ddDrawingView.h"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddTableFigure::ddTableFigure(int x, int y):
ddCompositeFigure()
{
	//Set table size, width and position
	rectangleFigure = new ddRectangleFigure();
	rectangleFigure->moveTo(x,y);
/*	rectangleFigure->getBasicDisplayBox().x=x;
	rectangleFigure->getBasicDisplayBox().y=y;
*/
	add(rectangleFigure);
	//DD-TODO: improve table name automatic creation
	tableTitle = new ddSimpleTextFigure(wxT("TableX"));
	tableTitle->setEditable(true);
	tableTitle->moveTo(x,y);
	add(tableTitle);
	internalPadding = 3;
	externalPadding = 6;
	tableTitle->moveTo(rectangleFigure->getBasicDisplayBox().x+externalPadding,rectangleFigure->getBasicDisplayBox().y+externalPadding);

}

ddTableFigure::~ddTableFigure()
{
}

//Columns SHOULD BE ADDED only using this function to avoid rare behaviors
void ddTableFigure::addColumn(ddColumnFigure *column)
{
	column->setOwnerTable(this);
	resetPosition(column);
	add(column);
	updateTableSize();
}

void ddTableFigure::removeColumn(ddColumnFigure *column)
{
	column->setOwnerTable(NULL);
	remove(column);
	updateTableSize();
}

void ddTableFigure::updateTableSize()
{
	ddRect r;
	ddIFigure *f;
	ddIteratorBase *iterator=figuresEnumerator();

	f = (ddIFigure *) iterator->Next(); //First Figure is Main Rect
	r.SetSize(wxSize(0,0));
	r.SetPosition( f->displayBox().GetPosition());

	while(iterator->HasNext()){
		f = (ddIFigure *) iterator->Next();
		r.add( f->displayBox() );
	}
	delete iterator;


//Adjust size of table with padding
wxSize s = r.GetSize();
s.IncBy(externalPadding*2,externalPadding*2);
rectangleFigure->setSize(s);
}


void ddTableFigure::draw(wxBufferedDC& context, ddDrawingView *view)
{
	ddCompositeFigure::draw(context,view);
/*	ddIteratorBase *iterator=figuresEnumerator();
	iterator->Next(); //First Figure is always Rect, just ignore
	ddIFigure *f = (ddIFigure *) iterator->Next(); //Second Figure is table title
	*/
}

//Put a new column their new position below older columns
void ddTableFigure::resetPosition(ddColumnFigure *column)
{
	ddRect r;
	int verticalPos = 0, horizontalPos = 0;

	ddIteratorBase *iterator=figuresEnumerator();
	
	iterator->Next(); //First Figure is always Rect, just ignore
	ddIFigure *f = (ddIFigure *) iterator->Next(); //Second Figure is table title
	verticalPos = f->displayBox().GetBottom(); //f->displayBox().y + f->displayBox().width;
	horizontalPos = f->displayBox().x;

	while(iterator->HasNext()){
		f = (ddIFigure *) iterator->Next();
		verticalPos += f->displayBox().height; 
	}
	delete iterator;
	column->displayBox().y = internalPadding + verticalPos;
	column->displayBox().x = horizontalPos;
}
