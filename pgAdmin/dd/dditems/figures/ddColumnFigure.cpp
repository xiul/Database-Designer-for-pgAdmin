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
#include "dd/dditems/figures/ddColumnFigure.h"
#include "dd/dditems/figures/ddTextColumnFigure.h"
#include "dd/dditems/tools/ddColumnFigureTool.h"
#include "dd/dditems/figures/ddColumnKindIcon.h"
/*#include "dd/draw/utilities/ddArrayCollection.h"

*/
#include "dd/dditems/utilities/ddDataType.h"

//Images
#include "images/foreignkey.xpm"
#include "images/primarykey.xpm"
#include "images/unique.xpm"
#include "images/parser.xpm"  //test for fk pk


//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


ddColumnFigure::ddColumnFigure(wxString& columnName){
	columnText = new ddTextColumnFigure(columnName,dt_null);
	leftImage = new ddColumnKindIcon();

	//init displaybox && images position
	basicDisplayBox.SetPosition(wxPoint(0,0));
	basicDisplayBox.SetSize( columnText->displayBox().GetSize());
	if(leftImage)
	{
		basicDisplayBox.width+=leftImage->displayBox().GetSize().GetWidth();
		columnText->displayBox().x+=leftImage->displayBox().GetSize().GetWidth();
	}
	else
	{
		basicDisplayBox.width+=16; //default value
		columnText->displayBox().x+=16;
	}


}

ddColumnFigure::~ddColumnFigure(){

	if(columnText)
		delete columnText;
	if(leftImage)
		delete leftImage;
}

void ddColumnFigure::basicMoveBy(int x, int y)
{
	ddAbstractFigure::basicMoveBy(x,y);
	if(leftImage)
	{
			leftImage->moveBy(x,y);
			columnText->moveBy(x,y);
	}
	else
	{
			columnText->moveBy(x,y);
	}
}

void ddColumnFigure::moveTo(int x, int y)
{
	ddAbstractFigure::moveTo(x,y);
	if(leftImage)
	{
			leftImage->moveTo(x,y);
			columnText->moveTo(x+leftImage->displayBox().GetSize().GetWidth(),y);
	}
	else
	{
			columnText->moveTo(x+16,y);
	}
}


bool ddColumnFigure::containsPoint(int x, int y)
{
	bool out = false;
	if(columnText->containsPoint(x,y))
		{
			out=true;  
		}
		
	if(leftImage->containsPoint(x,y))
		{
			out=true;  
		}
	return out;
}

ddRect& ddColumnFigure::getBasicDisplayBox()
{
/*	if(leftImage)
	{
		basicDisplayBox.x=columnText->displayBox().x-leftImage->getWidth();
	}
	else
	{
		basicDisplayBox.x=columnText->displayBox().x-16;
	}
	basicDisplayBox.y=columnText->displayBox().y;
*/
	return basicDisplayBox;
}

void ddColumnFigure::draw(wxBufferedDC& context, ddDrawingView *view)
{
	columnText->draw(context,view);
		if(leftImage)
			leftImage->draw(context,view);
}

void ddColumnFigure::drawSelected(wxBufferedDC& context, ddDrawingView *view)
{
	columnText->drawSelected(context,view);
		if(leftImage)
			leftImage->drawSelected(context,view);
}

ddIFigure* ddColumnFigure::findFigure(int x, int y)
{
	ddIFigure *out=NULL;

	if(columnText->containsPoint(x,y))
			out=columnText;

	if(leftImage && leftImage->containsPoint(x,y))
			out=leftImage;

	return out;
}

ddITool* ddColumnFigure::CreateFigureTool(ddDrawingEditor *editor, ddITool *defaultTool)
{
	return new ddColumnFigureTool(editor, this, defaultTool);
}

void ddColumnFigure::sendToBack(ddIFigure *figure)
{
	//DD-TODO: Implement this function
}

void ddColumnFigure::sendToFront(ddIFigure *figure)
{
	//DD-TODO: Implement this function
}


ddIFigure* ddColumnFigure::getFigureAt(int pos)
{
	if(pos==0)
	{
		return (ddIFigure*) leftImage;
	}
	
	if(pos==1)
	{
		return (ddIFigure*) columnText;
	}
	
	return NULL;
}

ddTableFigure* ddColumnFigure::getOwnerTable()
{
	return columnText->getOwnerTable();
}

void ddColumnFigure::setOwnerTable(ddTableFigure *table)
{
	columnText->setOwnerTable(table);
}