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
#include "dd/dditems/figures/ddTextColumnFigure.h"
#include "dd/dditems/figures/ddColumnFigure.h"
#include "dd/draw/main/ddDrawingView.h"
#include "dd/dditems/utilities/ddDataType.h"
#include "dd/dditems/handles/ddAddColButtonHandle.h"
#include "dd/dditems/locators/ddAddColLocator.h"
#include "dd/dditems/handles/ddRemoveColButtonHandle.h"
#include "dd/dditems/locators/ddRemoveColLocator.h"
#include "dd/dditems/handles/ddAddFkButtonHandle.h"
#include "dd/dditems/locators/ddAddFkLocator.h"
#include "dd/dditems/handles/ddRemoveTableButtonHandle.h"
#include "dd/dditems/locators/ddRemoveTableLocator.h"
#include "dd/dditems/handles/ddMinMaxTableButtonHandle.h"
#include "dd/dditems/locators/ddMinMaxTableLocator.h"
#include "dd/dditems/handles/ddScrollBarHandle.h"
#include "dd/dditems/locators/ddScrollBarTableLocator.h"
#include "dd/dditems/handles/ddSouthTableSizeHandle.h"
#include "dd/dditems/locators/ddTableBottomLocator.h"
#include "dd/draw/utilities/ddGeometry.h"
#include "dd/dditems/figures/ddRelationshipFigure.h"

//Images
#include "images/ddAddColumn.xpm"
#include "images/ddRemoveColumn.xpm"
#include "images/ddAddForeignKey.xpm"
#include "images/ddMaximizeTable.xpm"
#include "images/ddMinimizeTable.xpm"
#include "images/ddRemoveTable.xpm"

//*******************   Start of special debug header to find memory leaks
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//*******************   End of special debug header to find memory leaks


/*
All figures title, cols, indxs are store at same array to improve performance

[0] = table border rect
[1] = table title
[2] = first column index
[maxColIndex] = last column index
[minIdxIndex] = first index index
[maxIdxIndex] = last index index
*/

ddTableFigure::ddTableFigure(int x, int y):
ddCompositeFigure()
{
	internalPadding = 2;
	externalPadding = 4;
	deleteColumnMode=false;

	//Set table size, width and position
	rectangleFigure = new ddRectangleFigure();
	rectangleFigure->moveTo(x,y);
	add(rectangleFigure);
	
	//DD-TODO: improve table name automatic creation
	tableTitle = new ddTextColumnFigure(wxString(wxT("NewTable")),dt_null,NULL);
	tableTitle->setEditable(true);
	tableTitle->moveTo(x,y);
	tableTitle->disablePopUp();
	tableTitle->setShowDataType(false);
	//If owner == NULL then don't delete that column because it don't belong to table
	//tableTitle->setOwnerTable(NULL); 
	add(tableTitle);
	tableTitle->moveTo(rectangleFigure->getBasicDisplayBox().x+internalPadding*2,rectangleFigure->getBasicDisplayBox().y+internalPadding/2);

	//Intialize handles
	figureHandles->addItem(new ddAddColButtonHandle(this,new ddAddColLocator(), wxBitmap(ddAddColumn_xpm),wxSize(8,8)));
	figureHandles->addItem(new ddRemoveColButtonHandle(this,new ddRemoveColLocator(), wxBitmap(ddRemoveColumn_xpm),wxSize(8,8)));
	figureHandles->addItem(new ddAddFkButtonHandle(this,new ddAddFkLocator(), wxBitmap(ddAddForeignKey_xpm),wxSize(8,8)));
	figureHandles->addItem(new ddRemoveTableButtonHandle(this,new ddRemoveTableLocator(), wxBitmap(ddRemoveTable_xpm),wxSize(8,8)));
	figureHandles->addItem(new ddMinMaxTableButtonHandle(this,new ddMinMaxTableLocator(), wxBitmap(ddMinimizeTable_xpm),wxBitmap(ddMaximizeTable_xpm),wxSize(8,8)));
// Don't use it to UI consistency, eliminate it	figureHandles->addItem(new ddNorthTableSizeHandle(this,new ddTableTopLocator()));
	figureHandles->addItem(new ddSouthTableSizeHandle(this, new ddTableBottomLocator()));

	//Intialize special handle
	scrollbar=new ddScrollBarHandle(this,new ddScrollBarTableLocator(),wxSize(10,colsRect.GetSize().GetHeight()));

	fromSelToNOSel=false;
	
	//Intialize columns window (Min is always 1 in both, with or without cols & indxs)
	colsRowsSize = 0;
	colsWindow = 0;
	idxsRowsSize = 0;
	idxsWindow = 0;
	
	//Initialize indexes (pointers to array segments)
	maxColIndex=2;
	minIdxIndex=2;  
	maxIdxIndex=2;

	//Initialize position where start to draw cols & indxs
	//This is value to allow scrollbars
	beginDrawCols=2;
	beginDrawIdxs=2;

	//Initialize
	pkName=wxT("NewTable_pk");
	ukNames.clear();

/*	getUkConstraintsNames().Add(wxString(wxT("uk_1")));
	getUkConstraintsNames().Add(wxString(wxT("uk_2")));
	getUkConstraintsNames().Add(wxString(wxT("uk_3")));
	getUkConstraintsNames().Add(wxString(wxT("uk_4")));
/*
	//Start foreign keys management variables
	fkMaxIndex=0;
	fkNames.Clear();
*/

	calcRectsAreas();
}

ddTableFigure::~ddTableFigure()
{
	if(scrollbar)
	{
		if(figureHandles->existsObject(scrollbar))
			figureHandles->removeItem(scrollbar);
		delete scrollbar;
	}
}


//Columns SHOULD BE ADDED only using this function to avoid rare behaviors
void ddTableFigure::addColumn(ddColumnFigure *column)
{
	column->setOwnerTable(this);
	add(column);
	//Update Indexes
	if(maxColIndex == minIdxIndex) //maxColIndex == minIdxIndex means not indexes at this table, then update too
	{	
		minIdxIndex++;
		maxIdxIndex++;
	}
	maxColIndex++;
	colsWindow++;  //by default add a columna increase window
	colsRowsSize++;
	calcRectsAreas();
	recalculateColsPos();

	/*SCROLLBAR TEST*/
		if(maxColIndex == 10)
	{
		setColumnsWindow(4);
		setColumnsWindow(3);
		setColumnsWindow(2);
		setColumnsWindow(1);
		setColumnsWindow(2);
		setColumnsWindow(3);
		setColumnsWindow(2);
		setColumnsWindow(4);
		columnsWindowDown();
		columnsWindowUp();
		columnsWindowUp();
		columnsWindowUp();
		columnsWindowUp();
		columnsWindowUp();
		columnsWindowDown();
		columnsWindowDown();
		columnsWindowDown();
		columnsWindowDown();
		columnsWindowDown();

/*		beginDrawCols=4;
		colsWindow=2;
		calcRectsAreas();
		recalculateColsPos();
		*/
	}
}

void ddTableFigure::removeColumn(ddColumnFigure *column)
{
	//hack to allow to remove Fk before delete it.
	if(column->isPrimaryKey())
	{
		column->setColumnKind(none);
		updateFkObservers();
	}
	column->setOwnerTable(NULL);
	remove(column);
	if(column)
		delete column;
	//calcMaxTableSizes();
	//Update Indexes
	if(maxColIndex == minIdxIndex) //maxColIndex == minIdxIndex means not indexes at this table, then update too
	{	
		minIdxIndex--;
		maxIdxIndex--;
	}
	maxColIndex--;
	if(colsRowsSize==colsWindow)  //only decrease if size of window and columns is the same
		colsWindow--;
	colsRowsSize--;
	if(beginDrawCols > 2)
		beginDrawCols--;
	calcRectsAreas();
	recalculateColsPos();
	if(colsWindow==colsRowsSize)   //if handle need to be removed, remove it
	{
		if(figureHandles->existsObject(scrollbar))
			figureHandles->removeItem(scrollbar);
	}
	//hack to update relationship position when table size change
	moveBy(-1,0);
	moveBy(1,0);
}

//al borrar una columna de una tabla con el window = al size falla


void ddTableFigure::recalculateColsPos()
{
	wxFont font = settings->GetSystemFont();
	int defaultHeight = getColDefaultHeight(font);

	ddIFigure *f = (ddIFigure *) figureFigures->getItemAt(0); //First Figure is always Rect
	int horizontalPos = f->displayBox().x+2;
	int verticalPos = 0;

	for(int i = 2; i < maxColIndex ; i++)
	{
		f = (ddIFigure *) figureFigures->getItemAt(i); //table title
		if( (i >= beginDrawCols) && (i <= (colsWindow+beginDrawCols)) )  //visible to draw
		{
			verticalPos = colsRect.y + (defaultHeight * (i-beginDrawCols) + ((i-beginDrawCols) * internalPadding));
			f->moveTo(horizontalPos,verticalPos);
		}
		else
			f->moveTo(-65000,-65000);  //any figure outside canvas (x<0 || y<0) is not draw & not used to calculate displaybox
	}
}



void ddTableFigure::draw(wxBufferedDC& context, ddDrawingView *view)
{

	context.SetPen(defaultPen);
	context.SetBrush(defaultBrush);

	//Hack to disable delete column mode when the figure pass from selected to no selected.
	if(fromSelToNOSel)
	{
		toggleColumnDeleteMode(true);
		fromSelToNOSel=false;
	}
	
	calcRectsAreas();
	context.SetPen(*wxBLACK_PEN);
	context.SetBrush(wxBrush (wxColour(255, 255, 224),wxSOLID));

	if(calcScrolled) //Hack to avoid pass view as parameter to calcRectsAreas() because is sometimes called outside a paint event
	{
		view->CalcScrolledPosition(fullSizeRect.x,fullSizeRect.y,&fullSizeRect.x,&fullSizeRect.y);
		view->CalcScrolledPosition(titleRect.x,titleRect.y,&titleRect.x,&titleRect.y);
		view->CalcScrolledPosition(titleColsRect.x,titleColsRect.y,&titleColsRect.x,&titleColsRect.y);
		view->CalcScrolledPosition(colsRect.x,colsRect.y,&colsRect.x,&colsRect.y);
		view->CalcScrolledPosition(titleIndxsRect.x,titleIndxsRect.y,&titleIndxsRect.x,&titleIndxsRect.y);
		view->CalcScrolledPosition(indxsRect.x,indxsRect.y,&indxsRect.x,&indxsRect.y);
		calcScrolled=false;
	}

	ddIFigure *f = (ddIFigure *) figureFigures->getItemAt(0); //table rectangle
	f->draw(context,view);
	f = (ddIFigure *) figureFigures->getItemAt(1); //table title
	f->draw(context,view);

	for(int i=beginDrawCols; i < (colsWindow+beginDrawCols); i++)
	{
		f = (ddIFigure *) figureFigures->getItemAt(i); //table title
		if(f->displayBox().GetPosition().x > 0 && f->displayBox().GetPosition().y > 0)
		{
			f->draw(context,view);
		}
	}

	wxFont font = settings->GetSystemFont();
	font.SetPointSize(7);
	context.SetFont(font);

	//Draw Columns Title Line 1
	context.DrawLine(titleColsRect.GetTopLeft(),titleColsRect.GetTopRight());
	//Draw Columns Title
	context.DrawText(wxT("Columns"),titleColsRect.x+3,titleColsRect.y);
	//Draw Columns Title Line 2
	context.DrawLine(titleColsRect.GetBottomLeft(),titleColsRect.GetBottomRight());
	//DrawVertical Lines
	context.DrawLine(titleColsRect.GetBottomLeft().x+11,titleColsRect.GetBottomLeft().y,titleColsRect.GetBottomLeft().x+11,titleIndxsRect.GetTopLeft().y);
	context.DrawLine(titleColsRect.GetBottomLeft().x+22,titleColsRect.GetBottomLeft().y,titleColsRect.GetBottomLeft().x+22,titleIndxsRect.GetTopLeft().y);
	//Draw Indexes Title Line 1
	context.DrawLine(titleIndxsRect.GetTopLeft(),titleIndxsRect.GetTopRight());
	//Draw Indexes Title	
	context.DrawText(wxT("Indexes"),titleIndxsRect.x+3,titleIndxsRect.y);
	//Draw Indexes Title Line 2
	context.DrawLine(titleIndxsRect.GetBottomLeft(),titleIndxsRect.GetBottomRight());

	//Draw scrollbar is needed
	if(scrollbar && figureHandles->existsObject(scrollbar))
		scrollbar->draw(context,view);
}

void ddTableFigure::drawSelected(wxBufferedDC& context, ddDrawingView *view)
{
	context.SetPen(defaultSelectedPen);
	context.SetBrush(defaultSelectedBrush);

	//Hack to unselect any table
	if(!fromSelToNOSel)
		fromSelToNOSel=true;

	calcRectsAreas();
	context.SetPen(wxPen(wxColour(70, 130, 180),2,wxSOLID));
	context.SetBrush(wxBrush (wxColour(224, 248, 255),wxSOLID));

	if(calcScrolled) //Hack to avoid pass view as parameter to calcRectsAreas() because is sometimes called outside a paint event
	{
		view->CalcScrolledPosition(fullSizeRect.x,fullSizeRect.y,&fullSizeRect.x,&fullSizeRect.y);
		view->CalcScrolledPosition(titleRect.x,titleRect.y,&titleRect.x,&titleRect.y);
		view->CalcScrolledPosition(titleColsRect.x,titleColsRect.y,&titleColsRect.x,&titleColsRect.y);
		view->CalcScrolledPosition(colsRect.x,colsRect.y,&colsRect.x,&colsRect.y);
		view->CalcScrolledPosition(titleIndxsRect.x,titleIndxsRect.y,&titleIndxsRect.x,&titleIndxsRect.y);
		view->CalcScrolledPosition(indxsRect.x,indxsRect.y,&indxsRect.x,&indxsRect.y);
		calcScrolled=false;
	}

	ddIFigure *f = (ddIFigure *) figureFigures->getItemAt(0); //table rectangle
	f->drawSelected(context,view);
	f = (ddIFigure *) figureFigures->getItemAt(1); //table title
	f->drawSelected(context,view);

	for(int i=beginDrawCols; i < (colsWindow+beginDrawCols); i++)
	{
		f = (ddIFigure *) figureFigures->getItemAt(i); //table title
		if(f->displayBox().GetPosition().x > 0 && f->displayBox().GetPosition().y > 0)
		{
			f->drawSelected(context,view);
		}
	}

	wxFont font = settings->GetSystemFont();
	font.SetPointSize(7);
	context.SetFont(font);

	//Draw Columns Title Line 1
	context.DrawLine(titleColsRect.GetTopLeft(),titleColsRect.GetTopRight());
	//Draw Columns Title
	context.DrawText(wxT("Columns"),titleColsRect.x+3,titleColsRect.y);
	//Draw Columns Title Line 2
	context.DrawLine(titleColsRect.GetBottomLeft(),titleColsRect.GetBottomRight());
	//DrawVertical Lines
	context.DrawLine(titleColsRect.GetBottomLeft().x+11,titleColsRect.GetBottomLeft().y,titleColsRect.GetBottomLeft().x+11,titleIndxsRect.GetTopLeft().y);
	context.DrawLine(titleColsRect.GetBottomLeft().x+22,titleColsRect.GetBottomLeft().y,titleColsRect.GetBottomLeft().x+22,titleIndxsRect.GetTopLeft().y);
	//Draw Indexes Title Line 1
	context.DrawLine(titleIndxsRect.GetTopLeft(),titleIndxsRect.GetTopRight());
	//Draw Indexes Title	
	context.DrawText(wxT("Indexes"),titleIndxsRect.x+3,titleIndxsRect.y);
	//Draw Indexes Title Line 2
	context.DrawLine(titleIndxsRect.GetBottomLeft(),titleIndxsRect.GetBottomRight());

	if(deleteColumnMode)
	{
		context.SetTextForeground(*wxRED);
		wxBrush old=context.GetBrush();
		context.SetBrush(*wxGREEN_BRUSH);

		int w,h,x,y;
		context.GetTextExtent(wxString(wxT("Select Column to delete")),&w,&h);
		x=fullSizeRect.GetTopLeft().x+(((fullSizeRect.GetTopRight().x-fullSizeRect.GetTopLeft().x)-w)/2);
		y=fullSizeRect.GetTopLeft().y-h-2;
		context.DrawRectangle(wxRect(x,y,w,h));
		context.DrawText(wxString(wxT("Select Column to delete")),x,y);
		
		context.SetBrush(old);
		context.SetTextForeground(*wxBLACK);
		context.SetBackground(*wxWHITE);
		
	}
}

void ddTableFigure::setColsRowsWindow(int num)
{
	if(num > 0)
	{
		colsWindow = num;
		wxFont font = settings->GetSystemFont();
		colsRect.height = getColDefaultHeight(font) * colsWindow;
		colsRect.width = getFiguresMaxWidth();
	}
}

int ddTableFigure::getHeightFontMetric(wxString text, wxFont font)
{
	int width, height;
	wxMemoryDC temp_dc;
	temp_dc.SetFont(font);
	temp_dc.GetTextExtent(text,&width,&height);
	return height;
}

int ddTableFigure::getColDefaultHeight(wxFont font)
{
	if(figureFigures->count()<=0)
	{
		int width, height;
		wxMemoryDC temp_dc;
		temp_dc.SetFont(font);
		temp_dc.GetTextExtent(wxT("NewColumn"),&width,&height);
		return height;
	}
	else
	{
		ddIFigure *f = (ddIFigure *) figureFigures->getItemAt(1); //table title
		return f->displayBox().height; 
	}
}

//Delete Column Hack
bool ddTableFigure::deleteColumnActivated()
{
	return deleteColumnMode;
}

//Delete Column Hack
void ddTableFigure::toggleColumnDeleteMode(bool disable)
{
	if(disable)
		deleteColumnMode = false;
	else
		deleteColumnMode = !deleteColumnMode;
}

int ddTableFigure::getFiguresMaxWidth()
{
	ddIFigure *f;
	ddGeometry g;

	ddIteratorBase *iterator=figuresEnumerator();
	iterator->Next(); //First Figure is Main Rect
	int maxWidth=0;
	while(iterator->HasNext()){
		f = (ddIFigure *) iterator->Next();
		maxWidth = g.max(maxWidth,f->displayBox().width);
	}
	delete iterator;
	if(figureHandles->existsObject(scrollbar))
		return maxWidth + 11;  //as defined at locator
	else
		return maxWidth;
}


void ddTableFigure::calcRectsAreas()
{
	calcScrolled=true;

	int maxWidth = getFiguresMaxWidth() + externalPadding;
	if(maxWidth < 100)
		maxWidth = 100;
	wxFont font = settings->GetSystemFont();
	int defaultHeight = getColDefaultHeight(font);

	//cache displayBox()
	ddRect db = displayBox();

	//*** titleRect
	font.SetPointSize(7);
	int colsTitleHeight=getHeightFontMetric(wxT("Columns"),font);
	titleRect.x = db.x;
	titleRect.y = db.y;
	titleRect.width=maxWidth;
	titleRect.height=defaultHeight;

	titleColsRect.x = db.x;
	titleColsRect.y = titleRect.y+titleRect.height;
	titleColsRect.width=maxWidth;
	titleColsRect.height=colsTitleHeight;
	unScrolledTitleRect=titleColsRect;
	
	//*** colsRect
	colsRect.width=maxWidth;
	if(colsWindow>0)
		colsRect.height = defaultHeight * colsWindow + (colsWindow * internalPadding);
	else
		colsRect.height = defaultHeight;
	colsRect.x=db.x;
	colsRect.y=titleRect.y+titleRect.height+titleColsRect.height;
	unScrolledColsRect=colsRect;

	//*** idxTitleRect
	titleIndxsRect.width=maxWidth;
	titleIndxsRect.height=colsTitleHeight;
	titleIndxsRect.x=db.x;
	titleIndxsRect.y=colsRect.y+colsRect.height;

	//*** indexesRect
	indxsRect.width=maxWidth;
	indxsRect.height = defaultHeight * idxsWindow + (idxsWindow * internalPadding);
	indxsRect.x=db.x;
	indxsRect.y=titleIndxsRect.y+titleIndxsRect.height;

	//*** FullTable Size
	fullSizeRect.width = maxWidth;
	fullSizeRect.height = titleRect.height + titleColsRect.height + colsRect.height + titleIndxsRect.height + indxsRect.height;
	fullSizeRect.x=db.x;
	fullSizeRect.y=titleRect.y;
	unScrolledFullSizeRect=fullSizeRect;

	//Update sizes
	rectangleFigure->setSize(fullSizeRect.GetSize());
}

void ddTableFigure::updateTableSize()
{
	rectangleFigure->setSize(fullSizeRect.GetSize());
	//hack to update relationship position when table size change
	moveBy(-1,0);
	moveBy(1,0);
}

ddRect& ddTableFigure::getColsSpace()
{
	return unScrolledColsRect;
}

ddRect& ddTableFigure::getFullSpace()
{
	return unScrolledFullSizeRect;
}

ddRect& ddTableFigure::getTitleRect()
{
	return unScrolledTitleRect;
}


int ddTableFigure::getTotalColumns()
{
	return colsRowsSize;
}

int ddTableFigure::getColumnsWindow()
{
	return colsWindow;
}

void ddTableFigure::setColumnsWindow(int value, bool maximize)
{

	if(!maximize)
	{

		//if value >0 && <= max size table && table+offset < maxColIndex with window
		if( (value > 0) && (value <= colsRowsSize) && (maxColIndex >= ( beginDrawCols + value ) ) )   
		{
			colsWindow = value;
			calcRectsAreas();
			recalculateColsPos();
		}

		//if special case of needing to modify beginDrawCols then do it
		if( (value > 0) && (value <= colsRowsSize) && (maxColIndex < ( beginDrawCols + value ) ) ) 
		{
			if( (beginDrawCols + colsWindow)==maxColIndex)  //if index is at max
			{
				int diff = value-colsWindow;  //value should be always higher tan colsWindows
				if(diff > 0 && (beginDrawCols-diff)>=0 )
				{
					beginDrawCols-=diff;
					colsWindow = value;
					calcRectsAreas();
					recalculateColsPos();

				}
			}
		}
	}
	else
	{
		beginDrawCols = 2;
		colsWindow = value;
		calcRectsAreas();
		recalculateColsPos();
	}


	//Hide Scrollbar if needed
	if(colsWindow==colsRowsSize) 
	{
		if(figureHandles->existsObject(scrollbar))
			figureHandles->removeItem(scrollbar);
	}
	else 
	{
		if (!figureHandles->existsObject(scrollbar))
			figureHandles->addItem(scrollbar);
	}

}

void ddTableFigure::columnsWindowUp()  //move window from number to zero
{
	if( beginDrawCols > 2 )
	{
		beginDrawCols--;
		calcRectsAreas();
		recalculateColsPos();
	}
}

void ddTableFigure::columnsWindowDown()  //move window from number to maxcolumns
{
	if( (beginDrawCols+colsWindow) < maxColIndex)
	{
		beginDrawCols++;
		calcRectsAreas();
		recalculateColsPos();
	}
}

int ddTableFigure::getTopColWindowIndex()
{
	return (beginDrawCols-2);
}

void ddTableFigure::setPkConstraintName(wxString name)
{
	pkName = name;
}

wxString ddTableFigure::getPkConstraintName()
{
	return pkName;	
}

wxArrayString& ddTableFigure::getUkConstraintsNames()
{
	return ukNames;
}

wxString ddTableFigure::getTableName()
{
	ddTextColumnFigure *c = (ddTextColumnFigure*) figureFigures->getItemAt(1);
	return c->getText(false);
}

void ddTableFigure::updateFkObservers()
{
	ddIteratorBase *iterator = observersEnumerator();
	while(iterator->HasNext()){
	ddRelationshipFigure *r = (ddRelationshipFigure*) iterator->Next();
		r->updateForeignKey();
	}
	delete iterator;
}

void ddTableFigure::basicMoveBy(int x, int y)
{
	ddIFigure *f = (ddIFigure *) figureFigures->getItemAt(0);
	if((f->displayBox().x+x) > 0  && (f->displayBox().y+y) > 0)
		ddCompositeFigure::basicMoveBy(x,y);
}
