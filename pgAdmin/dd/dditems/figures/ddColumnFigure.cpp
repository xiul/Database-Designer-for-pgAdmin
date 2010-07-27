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
#include "dd/dditems/figures/ddColumnOptionIcon.h"
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


ddColumnFigure::ddColumnFigure(wxString& columnName, ddTableFigure *owner){
	columnText = new ddTextColumnFigure(columnName,dt_null,this);
	leftImage = new ddColumnKindIcon();
	centerImage = new ddColumnOptionIcon();
	
	setOwnerTable(owner);

	//init displaybox && images position
	basicDisplayBox.SetPosition(wxPoint(0,0));
	basicDisplayBox.SetSize( columnText->displayBox().GetSize());
	if(leftImage && centerImage)
	{
		basicDisplayBox.width+=leftImage->displayBox().GetSize().GetWidth()+3;
		basicDisplayBox.width+=centerImage->displayBox().GetSize().GetWidth()+3;
		columnText->displayBox().x+=leftImage->displayBox().GetSize().GetWidth()+2;
		columnText->displayBox().x+=centerImage->displayBox().GetSize().GetWidth()+3;
	}
	else
	{
		basicDisplayBox.width+=22; //default value =1 + 8 + 3 + 8 +2 
		columnText->displayBox().x+=22;
	}
}

ddColumnFigure::~ddColumnFigure(){

	if(columnText)
		delete columnText;
	if(leftImage)
		delete leftImage;
	if(centerImage)
		delete centerImage;
}

void ddColumnFigure::basicMoveBy(int x, int y)
{
	ddAbstractFigure::basicMoveBy(x,y);
	if(leftImage)
	{
			leftImage->moveBy(x,y);
	}
	if(centerImage)
	{
			centerImage->moveBy(x,y);
	}
	columnText->moveBy(x,y);
}

void ddColumnFigure::moveTo(int x, int y)
{
	ddAbstractFigure::moveTo(x,y);
	int distance=0;
	if(leftImage)
	{
		leftImage->moveTo(x,y);
		distance+=leftImage->displayBox().GetSize().GetWidth()+3;
	}
	else
	{
		distance+=11; //8+3
	}
	if(centerImage)
	{
		centerImage->moveTo(x+distance,y);
		distance+=centerImage->displayBox().GetSize().GetWidth()+3;
	}
	else
	{
		distance+=11; //8+3
	}

	columnText->moveTo(x+distance,y);
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
	
	if(centerImage->containsPoint(x,y))
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
		if(centerImage)
			centerImage->draw(context,view);
}

void ddColumnFigure::drawSelected(wxBufferedDC& context, ddDrawingView *view)
{
	columnText->drawSelected(context,view);
		if(leftImage)
			leftImage->drawSelected(context,view);
		if(centerImage)
			centerImage->drawSelected(context,view);
}

ddIFigure* ddColumnFigure::findFigure(int x, int y)
{
	ddIFigure *out=NULL;

	if(columnText->containsPoint(x,y))
			out=columnText;

	if(leftImage && leftImage->containsPoint(x,y))
			out=leftImage;

	if(centerImage && centerImage->containsPoint(x,y))
			out=centerImage;

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
		return (ddIFigure*) centerImage;
	}

	if(pos==2)
	{
		return (ddIFigure*) columnText;
	}
	
	return NULL;
}

ddTableFigure* ddColumnFigure::getOwnerTable()
{
	return ownerTable;
}

void ddColumnFigure::setOwnerTable(ddTableFigure *table)
{
	ownerTable = table;
}

void ddColumnFigure::displayBoxUpdate()
{
	if(leftImage && centerImage)
	{
		basicDisplayBox.width=columnText->displayBox().GetSize().GetWidth();
		basicDisplayBox.width+=leftImage->displayBox().GetSize().GetWidth()+3;
		basicDisplayBox.width+=centerImage->displayBox().GetSize().GetWidth()+3;
	}
	else
	{
		basicDisplayBox.width+=22; //default value =1 + 8 + 3 + 8 +2 
	}
}

bool ddColumnFigure::isNull()
{
	return centerImage->getOption()==null;
}

bool ddColumnFigure::isNotNull()
{
	return centerImage->getOption()==notnull;
}

bool ddColumnFigure::isPrimaryKey()
{
	return leftImage->getKind()==pk;
}

bool ddColumnFigure::isUniqueKey()
{
	return leftImage->getKind()==uk;
}

bool ddColumnFigure::isPlain()
{
	return leftImage->getKind()==none;
}

void ddColumnFigure::setColumnKind(ddColumnType type)
{
	leftImage->changeIcon(type);
}

void ddColumnFigure::setColumnOption(ddColumnOptionType type)
{
	centerImage->changeIcon(type);
}