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
#include "dd/dditems/handles/ddScrollBarHandle.h"
#include "dd/draw/utilities/ddPoint.h"
#include "dd/draw/main/ddDrawingView.h"

//Images
#include "images/ddUp.xpm"
#include "images/ddDown.xpm"



//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


//DD-TODO: can change base class to locatorhandle without any problems?
ddScrollBarHandle::ddScrollBarHandle(ddTableFigure *owner, ddILocator *scrollBarLocator , wxSize &size):
ddIHandle(owner)
{
	table=owner;
	scrollLocator = scrollBarLocator;
	displayBox.SetSize(size);
	upBitmap=wxBitmap(ddUp_xpm);
	downBitmap=wxBitmap(ddDown_xpm);
}

ddScrollBarHandle::~ddScrollBarHandle()
{
	if(scrollLocator)
		delete scrollLocator;
}


wxCursor ddScrollBarHandle::createCursor()
{
	return wxCursor(wxCURSOR_HAND);
}

//avoid to use inflate on this handle
ddRect& ddScrollBarHandle::getDisplayBox(){
	ddPoint p = locate();
	displayBox.width=11;  //as defined at locator
	displayBox.height=table->getColsSpace().height;
	displayBox.SetPosition(p);
	return displayBox;
}

void ddScrollBarHandle::draw(wxBufferedDC& context, ddDrawingView *view)
{
	wxPoint copy = getDisplayBox().GetPosition();
	view->CalcScrolledPosition(copy.x,copy.y,&copy.x,&copy.y);
	context.DrawRectangle(copy.x,copy.y,getDisplayBox().width,getDisplayBox().height);
	context.DrawBitmap(upBitmap,copy.x+1,copy.y+2,true);
	context.DrawBitmap(downBitmap,copy.x+1,copy.y+getDisplayBox().height-2-downBitmap.GetHeight(),true);
	
	barSize.SetHeight((getDisplayBox().height-12)*0.45); 
	barSize.SetWidth(getDisplayBox().width-4);

	int divBy = (table->getTotalColumns() - table->getColumnsWindow());
	if(divBy<=0)
		divBy = table->getColumnsWindow();
	int colOffset = barSize.GetHeight() / divBy;
	int verticalPosBar=3+copy.y+downBitmap.GetHeight()+ colOffset*table->getTopColWindowIndex();
	if(table->getColumnsWindow()>1)
		context.DrawRectangle(wxPoint(copy.x+2,verticalPosBar),barSize);

}

void ddScrollBarHandle::invokeStart(int x, int y, ddDrawingView *view)
{
	anchorY=y;
	if( (y > (getDisplayBox().GetPosition().y + 2)) && (y <  (getDisplayBox().GetPosition().y + 2 + 6)) )  //6 image height
		table->columnsWindowUp();

	if( (y > (getDisplayBox().GetPosition().y+getDisplayBox().height-2-downBitmap.GetHeight()) ) && (y < (getDisplayBox().GetPosition().y+getDisplayBox().height-2) ) )
		table->columnsWindowDown();
}

void ddScrollBarHandle::invokeStep(int x, int y, ddDrawingView *view)
{
	int divBy = (table->getTotalColumns() - table->getColumnsWindow());
	if(divBy<=0)
		divBy = table->getColumnsWindow();
	int colOffset = barSize.GetHeight() / divBy;
	
	if ( abs(anchorY-y) > colOffset)
	{
		if((anchorY-y)>0)
		{
			table->columnsWindowUp();
		}
		else
		{
			table->columnsWindowDown();
		}
		anchorY=y;
	}
}

void ddScrollBarHandle::invokeEnd(int x, int y, ddDrawingView *view)
{
}

ddPoint& ddScrollBarHandle::locate()
{
	if(scrollLocator)
		return scrollLocator->locate(getOwner());
	else
		return ddPoint(0,0);
}