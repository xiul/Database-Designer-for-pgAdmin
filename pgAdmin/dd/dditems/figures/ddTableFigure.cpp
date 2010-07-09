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
#include "dd/dditems/utilities/ddDataType.h"
#include "dd/dditems/handles/ddAddColButtonHandle.h"
#include "dd/dditems/locators/ddAddColLocator.h"
#include "dd/dditems/handles/ddRemoveColButtonHandle.h"
#include "dd/dditems/locators/ddRemoveColLocator.h"
#include "dd/dditems/handles/ddAddFkButtonHandle.h"
#include "dd/dditems/locators/ddAddFkLocator.h"
//Images
#include "images/ddAddColumn.xpm"
#include "images/ddRemoveColumn.xpm"
#include "images/ddAddForeignKey.xpm"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddTableFigure::ddTableFigure(int x, int y):
ddCompositeFigure()
{
	internalPadding = 3;
	externalPadding = 6;
	deleteColumnMode=false;

	//Set table size, width and position
	rectangleFigure = new ddRectangleFigure();
	rectangleFigure->moveTo(x,y);
	add(rectangleFigure);
	
	//DD-TODO: improve table name automatic creation
	tableTitle = new ddColumnFigure(wxString(wxT("NewTable")),dt_varchar_n);
	tableTitle->setEditable(true);
	tableTitle->moveTo(x,y);
	tableTitle->disablePopUp();
	tableTitle->setShowDataType(false);
	//If owner == NULL then don't delete that column because it don't belong to table
	tableTitle->setOwnerTable(NULL); 
	add(tableTitle);
	tableTitle->moveTo(rectangleFigure->getBasicDisplayBox().x+externalPadding,rectangleFigure->getBasicDisplayBox().y+externalPadding);

	//Intialize handles
	figureHandles->addItem(new ddAddColButtonHandle(this,new ddAddColLocator(), wxBitmap(ddAddColumn_xpm),wxSize(8,8)));
	figureHandles->addItem(new ddRemoveColButtonHandle(this,new ddRemoveColLocator(), wxBitmap(ddRemoveColumn_xpm),wxSize(8,8)));
	figureHandles->addItem(new ddAddFkButtonHandle(this,new ddAddFkLocator(), wxBitmap(ddAddForeignKey_xpm),wxSize(8,8)));

	fromSelToNOSel=false;
	
	minWidth=tableTitle->getTextWidth()+35;
	minHeight=tableTitle->getTextHeight()*2+internalPadding*2;

updateTableSize();
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
	if(column)
		delete column;
	updateTableSize();

//DD-TODO: if remove column and it's foreign key, should update observers 


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


//Adjust size of table	 with padding
wxSize s = r.GetSize();
s.IncBy(externalPadding*2,externalPadding*2);
if(s.GetHeight()<minHeight)
	s.SetHeight(minHeight);
if(s.GetWidth()<minWidth)
	s.SetWidth(minWidth);
rectangleFigure->setSize(s);
}


void ddTableFigure::draw(wxBufferedDC& context, ddDrawingView *view)
{
	//Hack to disable delete column mode when the figure pass from selected to no selected.
	if(fromSelToNOSel)
	{
		toggleColumnDeleteMode(true);
		fromSelToNOSel=false;
	}

	context.SetPen(*wxBLACK_PEN);
	context.SetBrush(wxBrush (wxColour(255, 255, 224),wxSOLID));

	ddCompositeFigure::draw(context,view);

	//Draw Title Line
	ddIFigure *f;
	f = (ddIFigure*)figureFigures->getItemAt(0);
	int x1=f->displayBox().GetTopLeft().x;
	int x2=f->displayBox().GetTopRight().x;
	int y=f->displayBox().GetPosition().y;
	f = (ddIFigure*)figureFigures->getItemAt(1);
	y+=f->displayBox().height;
	
	ddPoint copy1,copy2;
	view->CalcScrolledPosition(x1,y+(internalPadding),&copy1.x,&copy1.y);
	view->CalcScrolledPosition(x2,y+(internalPadding),&copy2.x,&copy2.y);

	context.DrawLine(copy1,copy2);
}

void ddTableFigure::drawSelected(wxBufferedDC& context, ddDrawingView *view)
{
	if(!fromSelToNOSel)
		fromSelToNOSel=true;
/*	context.SetPen(wxPen(wxColour(70, 130, 180),2,wxSOLID));
	context.SetBrush(wxBrush (wxColour(224, 248, 255),wxSOLID));
	*/

	context.SetPen(wxPen(wxColour(70, 130, 180),2,wxSOLID));
	context.SetBrush(wxBrush (wxColour(224, 248, 255),wxSOLID));

	ddCompositeFigure::drawSelected(context,view);

	//Draw Title Line
	ddIFigure *f;
	f = (ddIFigure*)figureFigures->getItemAt(0);
	int x1=f->displayBox().GetTopLeft().x;
	int x2=f->displayBox().GetTopRight().x;
	int y=f->displayBox().GetPosition().y;
	f = (ddIFigure*)figureFigures->getItemAt(1);
	y+=f->displayBox().height;

	ddPoint copy1,copy2;
	view->CalcScrolledPosition(x1,y+(internalPadding),&copy1.x,&copy1.y);
	view->CalcScrolledPosition(x2,y+(internalPadding),&copy2.x,&copy2.y);

	context.DrawLine(copy1,copy2);
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

bool ddTableFigure::deleteColumnActivated()
{
	return deleteColumnMode;
}

void ddTableFigure::toggleColumnDeleteMode(bool disable)
{
	if(disable)
		deleteColumnMode = false;
	else
		deleteColumnMode = !deleteColumnMode;
}