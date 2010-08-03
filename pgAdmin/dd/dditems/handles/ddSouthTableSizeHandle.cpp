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
#include "dd/dditems/handles/ddSouthTableSizeHandle.h"
#include "dd/dditems/figures/ddTableFigure.h"



//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddSouthTableSizeHandle::ddSouthTableSizeHandle(ddTableFigure *owner, ddILocator *locator):
ddLocatorHandle(owner,locator)
{
	//drawTempRect=false;
}

ddRect& ddSouthTableSizeHandle::getDisplayBox(){
	ddPoint p = locate();
	ddTableFigure *table = (ddTableFigure*) getOwner();
	displayBox.width=table->getFullSpace().width * 0.5;  //as defined at locator
	displayBox.height=3;
	displayBox.SetPosition(p);
	return displayBox;
}


wxCursor ddSouthTableSizeHandle::createCursor()
{
	return wxCursor(wxCURSOR_SIZENS);
}

void ddSouthTableSizeHandle::draw(wxBufferedDC& context, ddDrawingView *view)
{
/*	wxPen p = context.GetPen();
	wxBrush b = context.GetBrush();
	context.SetPen(*wxRED_PEN);
	context.SetBrush(*wxRED_BRUSH);
	ddRect sizer = getDisplayBox();
	int x=sizer.x;
	int y=sizer.y;
	int x2 = sizer.GetRightTop().x;
	sizer.width-=20;
	sizer.x+=10;
	context.DrawRectangle(sizer);
	
    
	wxPoint triangle_down[4];
    triangle_down[0] = wxPoint(x,y);
    triangle_down[1] = wxPoint(x+5,y);
    triangle_down[2] = wxPoint(x+3,y+5);
	triangle_down[3] = wxPoint(x,y);
	context.DrawPolygon(4,triangle_down);

	wxPoint triangle_up[4];
    triangle_up[0] = wxPoint(x2,y+5);
    triangle_up[1] = wxPoint(x2-5,y+5);
    triangle_up[2] = wxPoint(x2-3,y);
	triangle_up[3] = wxPoint(x2,y+5);
	context.DrawPolygon(4,triangle_up);

	context.SetPen(p);
	context.SetBrush(b);

	
	/*if(drawTempRect){
		if(startPoint.y < endPoint.y)
		{
			wxRect tmpRect(startPoint,endPoint);
			context.DrawRectangle(tmpRect);
		}
		else
		{
			wxRect tmpRect(endPoint,startPoint);
			context.DrawRectangle(tmpRect);
		}
	}
	*/
}

ddSouthTableSizeHandle::~ddSouthTableSizeHandle(){
}

void ddSouthTableSizeHandle::invokeStart(int x, int y, ddDrawingView *view)
{
	anchorY=y;
	
/*	ddTableFigure *table = (ddTableFigure*) getOwner();

	startPoint.x=table->getFullSpace().x;
	startPoint.y=y-10;
	endPoint.x=table->getFullSpace().x+table->getFullSpace().width;
	endPoint.y=y;
	drawTempRect=true;*/
}

void ddSouthTableSizeHandle::invokeStep(int x, int y, ddDrawingView *view)
{
	ddTableFigure *table = (ddTableFigure*) getOwner();
	wxFont font = settings->GetSystemFont();
	int colOffset = table->getColDefaultHeight(font);

	int divBy = (table->getTotalColumns() - table->getColumnsWindow());
	if(divBy<=0)
		divBy = table->getColumnsWindow();
	
	if ( abs(anchorY-y) > colOffset)
	{
		if((anchorY-y)>0)
		{
			table->setColumnsWindow(table->getColumnsWindow()-1);   //validated at table that dont't bypass max & min indexes
			//startPoint.y=y-10;
		}
		else
		{
			table->setColumnsWindow(table->getColumnsWindow()+1);   //validated at table that dont't bypass max & min indexes
		}
		anchorY=y;
	}

/*	endPoint.x=table->getFullSpace().x+table->getFullSpace().width;
	endPoint.y=y;
	*/
}

void ddSouthTableSizeHandle::invokeEnd(int x, int y, ddDrawingView *view)
{
	//drawTempRect=false;
}
