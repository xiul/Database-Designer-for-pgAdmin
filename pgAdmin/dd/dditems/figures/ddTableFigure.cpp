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
#include "dd/draw/utilities/ddGeometry.h"

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


	//DD-TODO: adjust this values
/*	minWidth=tableTitle->getTextWidth()+35;
	minHeight=tableTitle->getTextHeight()*2+internalPadding*2;
*/

//calcMaxTableSizes();
	calcRectsAreas();
}

ddTableFigure::~ddTableFigure()
{
}


//Columns SHOULD BE ADDED only using this function to avoid rare behaviors
void ddTableFigure::addColumn(ddColumnFigure *column)
{
	column->setOwnerTable(this);
	add(column);
	//calcMaxTableSizes();
	//Update Indexes
	if(maxColIndex == minIdxIndex) //maxColIndex == minIdxIndex means not indexes at this table, then update too
	{	
		minIdxIndex++;
		maxIdxIndex++;
	}
	maxColIndex++;
	colsWindow++;  //by default add a columna increase window
	calcRectsAreas();
	recalculateColsPos();
	
	
	
	if(maxColIndex >= 6)
	{
		beginDrawCols=4;
		colsWindow=2;
		calcRectsAreas();
		recalculateColsPos();
	}

}

void ddTableFigure::removeColumn(ddColumnFigure *column)
{
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
	if(maxColIndex==colsWindow)  //only decrease if size of window and columns is the same
		colsWindow--;
	calcRectsAreas();
	recalculateColsPos();
//DD-TODO: if remove column and it's foreign key, should update observers 
}

/*
void ddTableFigure::calcMaxTableSizes()
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

//Calc rect size (width,height) for table max sizes
/*666 maxSize = r.GetSize();
maxSize.IncBy(externalPadding*2,externalPadding*2);
*/



/* don't need this if work with indexes
if(maxSize.GetHeight()<minHeight)
	maxSize.SetHeight(minHeight);
if(maxSize.GetWidth()<minWidth)
	maxSize.SetWidth(minWidth);
if(setRects){
	rectangleFigure->setSize(maxSize);	
}

}
*/

/*
TODO NOW:
resetColPosition  debe cambiar es las columnas de posicion de acuerdo a su indice, de todas formas aquellas
que no esten en la ventana de dibujo, deben ser no dibujadas, para eso se les colocara la posicion x,y = -1 o un negativo muy grande -650000
y al detectar dicha posicion o con una variable especial la funcion de dibujo no las tomara en cuenta.
*/

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
//			int realPos = i-beginDrawCols;
			verticalPos = colsRect.y + (defaultHeight * (i-beginDrawCols) + ((i-beginDrawCols) * internalPadding));
			f->moveTo(horizontalPos,verticalPos);
		}
		else
			f->moveTo(-65000,-65000);
	}
}


//Put a new column their new position below older columns or if column is NULL fix positions of columns because a delete
/*
void ddTableFigure::resetColPosition(ddColumnFigure *column)
{
	ddRect r;
	int verticalPos = 0, horizontalPos = 0;

	ddIteratorBase *iterator=figuresEnumerator();
	
	//iterator->Next(); 
	ddIFigure *f = (ddIFigure *) iterator->Next(); //First Figure is always Rect
	horizontalPos = f->displayBox().x+2;
	f = (ddIFigure *) iterator->Next(); //Second Figure is table title
	//Get Font Metrics
	wxFont font = settings->GetSystemFont();
	font.SetPointSize(7);
	int height=getHeightFontMetric(wxT("Columns"),font);
	verticalPos = f->displayBox().GetBottom() + height+1; //f->displayBox().y + f->displayBox().width + X from second line(font metric) + 1 padding;
	

	while(iterator->HasNext()){
		f = (ddIFigure *) iterator->Next();
		if(!column) //if not column to add then recalculate old columns position
		{
			f->moveTo(horizontalPos,verticalPos + internalPadding);
		}
		verticalPos += f->displayBox().height; 
		

	}
	delete iterator;
	
	if(column)
	{
		column->moveTo(horizontalPos,internalPadding + verticalPos);
	}
}
*/

/*
crear 3 cuadros:
uno arriba para titulo y demas
el dos para columnas
el tres  para indices

el dos y el tres deben tener tamaño max y min, y un cambio en ellos debe cambiar la imagen de tamaño
esto es preparacion para el vertical scrollbar
*/

/*
void ddTableFigure::calculateHorizBars(ddDrawingView *view)
{
	//Calculate Top Line of Columns Bar
	ddIFigure *f;
	f = (ddIFigure*)figureFigures->getItemAt(0);
	int x1=f->displayBox().GetTopLeft().x;
	int x2=f->displayBox().GetTopRight().x;
	int y=f->displayBox().GetPosition().y;
	f = (ddIFigure*)figureFigures->getItemAt(1);
	y+=f->displayBox().height;

	view->CalcScrolledPosition(x1,y+(internalPadding),&colsTopLeft.x,&colsTopLeft.y);
	view->CalcScrolledPosition(x2,y+(internalPadding),&colsTopRight.x,&colsTopRight.y);
	
	//Calculate Bottom Line of Columns Bar
	colsBottomLeft = colsTopLeft;
	colsBottomRight = colsTopRight;
	
	//Get Font Metrics
	wxFont font = settings->GetSystemFont();
	font.SetPointSize(7);
	int height=getHeightFontMetric(wxT("Columns"),font);
	colsBottomLeft.y+=height;  
	colsBottomRight.y+=height;
	
	//Calculate Space for columns and draw indxs line

	//DD-TODO: Implement indexes and fix this
	f = (ddIFigure*)figureFigures->getItemAt(figureFigures->count()-1);
	x1=colsBottomLeft.x;
	x2=colsBottomLeft.x;
	y=f->displayBox().GetPosition().y;
	y+=f->displayBox().height;

	view->CalcScrolledPosition(x1,y+(internalPadding),&idxsTopLeft.x,&idxsTopLeft.y);
	view->CalcScrolledPosition(x2,y+(internalPadding),&idxsTopRight.x,&idxsTopRight.y);
	//Calculate Bottom Line of Columns Bar
	idxsBottomLeft = idxsTopLeft;
	idxsBottomRight = idxsTopRight;
	idxsBottomLeft.y+=9;
	idxsBottomRight.y+=9;
}
*/

void ddTableFigure::draw(wxBufferedDC& context, ddDrawingView *view)
{
	calcRectsAreas();
	context.SetPen(*wxBLACK_PEN);
	context.SetBrush(wxBrush (wxColour(255, 255, 224),wxSOLID));

//	context.DrawRectangle(fullSizeRect);

	ddIFigure *f = (ddIFigure *) figureFigures->getItemAt(0); //table rectangle
	f->draw(context,view);
	f = (ddIFigure *) figureFigures->getItemAt(1); //table title
	f->draw(context,view);


/*	context.DrawRectangle(titleRect);
	context.DrawRectangle(titleColsRect);
	context.DrawRectangle(colsRect);
	context.DrawRectangle(indxsTitleRect);
	context.DrawRectangle(indxsRect);
*/
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
	context.DrawText(wxT("Columns"),titleColsRect.x+3,titleColsRect.y);
	context.DrawText(wxT("Indexes"),indxsTitleRect.x+3,indxsTitleRect.y);

	//Hack to disable delete column mode when the figure pass from selected to no selected.
	if(fromSelToNOSel)
	{
		toggleColumnDeleteMode(true);
		fromSelToNOSel=false;
	}


	//Draw Columns Title Line 1
	//calculateHorizBars(view);
/*	context.DrawLine(colsTopLeft,colsTopRight);
	
	//Draw Columns middle line title
	wxFont font = settings->GetSystemFont();
	font.SetPointSize(7);
	context.SetFont(font);
	context.DrawText(wxT("Columns"),colsTopLeft.x+3,colsTopLeft.y-1);

	//Draw Columns Title Line 2
	context.DrawLine(colsBottomLeft,colsBottomRight);

	//DrawVertical Lines
	context.DrawLine(colsBottomLeft.x+11,colsBottomLeft.y,colsBottomLeft.x+11,idxsTopLeft.y);
	context.DrawLine(colsBottomLeft.x+22,colsBottomLeft.y,idxsTopLeft.x+22,idxsTopLeft.y);

	//Draw Indexes Title Line 1
	context.DrawLine(idxsTopLeft,idxsTopRight);
/*	
	//Draw Indexes middle line title
	font.SetPointSize(7);
	context.SetFont(font);
	context.DrawText(wxT("Indexes"),idxsTopLeft.x+3,idxsTopLeft.y-1);

	//Draw Indexes Title Line 2
	context.DrawLine(idxsBottomLeft,idxsBottomRight);
*/	

	

}

void ddTableFigure::drawSelected(wxBufferedDC& context, ddDrawingView *view)
{
	//Hack to unselect any table
	if(!fromSelToNOSel)
		fromSelToNOSel=true;

	//Hack to disable delete column mode when the figure pass from selected to no selected.
	if(fromSelToNOSel)
	{
		toggleColumnDeleteMode(true);
		fromSelToNOSel=false;
	}



	context.SetPen(wxPen(wxColour(70, 130, 180),2,wxSOLID));
	context.SetBrush(wxBrush (wxColour(224, 248, 255),wxSOLID));

	calcRectsAreas();
//	context.DrawRectangle(fullSizeRect);

	ddIFigure *f = (ddIFigure *) figureFigures->getItemAt(0); //table rectangle
	f->drawSelected(context,view);
	f = (ddIFigure *) figureFigures->getItemAt(1); //table title
	f->drawSelected(context,view);

/*	context.DrawRectangle(titleRect);
	context.DrawRectangle(titleColsRect);
	context.DrawRectangle(colsRect);
	context.DrawRectangle(indxsTitleRect);
	context.DrawRectangle(indxsRect);
*/
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
	context.DrawText(wxT("Columns"),titleColsRect.x+3,titleColsRect.y);
	context.DrawText(wxT("Indexes"),indxsTitleRect.x+3,indxsTitleRect.y);


	
/*	context.DrawRectangle(fullSizeRect);
	context.DrawRectangle(titleRect);
	context.DrawRectangle(titleColsRect);
	context.DrawRectangle(colsRect);
	context.DrawRectangle(indxsTitleRect);
	context.DrawRectangle(indxsRect);


	wxFont font = settings->GetSystemFont();
	font.SetPointSize(7);
	context.SetFont(font);
	context.DrawText(wxT("Columns"),titleColsRect.x+3,titleColsRect.y-1);
	context.DrawText(wxT("Indexes"),indxsTitleRect.x+3,indxsTitleRect.y-1); */

	//Hack to disable delete column mode when the figure pass from selected to no selected.
	if(fromSelToNOSel)
	{
		toggleColumnDeleteMode(true);
		fromSelToNOSel=false;
	}

//	ddCompositeFigure::draw(context,view);
	
	
	
	/*
	ddCompositeFigure::drawSelected(context,view);

	//Draw Columns Title Line 1
	//calculateHorizBars(view);
	context.DrawLine(colsTopLeft,colsTopRight);
	
	//Draw Columns middle line title
	wxFont font = settings->GetSystemFont();
	font.SetPointSize(7);
	context.SetFont(font);
	context.DrawText(wxT("Columns"),colsTopLeft.x+3,colsTopLeft.y-1);

	//Draw Columns Title Line 2
	context.DrawLine(colsBottomLeft,colsBottomRight);

	//DrawVertical Lines
	context.DrawLine(colsBottomLeft.x+11,colsBottomLeft.y,colsBottomLeft.x+11,idxsTopLeft.y);
	context.DrawLine(colsBottomLeft.x+22,colsBottomLeft.y,idxsTopLeft.x+22,idxsTopLeft.y);

	//Draw Indexes Title Line 1
	context.DrawLine(idxsTopLeft,idxsTopRight);
	*/
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
	return maxWidth;
}


void ddTableFigure::calcRectsAreas()
{
	int maxWidth = getFiguresMaxWidth() + externalPadding;
	wxFont font = settings->GetSystemFont();
	int defaultHeight = getColDefaultHeight(font);

	//*** titleRect
	font.SetPointSize(7);
	int colsTitleHeight=getHeightFontMetric(wxT("Columns"),font);
	titleRect.x = displayBox().x;
	titleRect.y = displayBox().y;
	titleRect.width=maxWidth;
	titleRect.height=defaultHeight; //666+colsTitleHeight;

	titleColsRect.x = displayBox().x;
	titleColsRect.y = titleRect.y+titleRect.height;
	titleColsRect.width=maxWidth;
	titleColsRect.height=colsTitleHeight;
	
	//*** colsRect
	colsRect.width=maxWidth;
	if(colsWindow>0)
		colsRect.height = defaultHeight * colsWindow + (colsWindow * internalPadding);
	else
		colsRect.height = defaultHeight;
	colsRect.x=displayBox().x;
	colsRect.y=titleRect.y+titleRect.height+titleColsRect.height;

	//*** idxTitleRect
	indxsTitleRect.width=maxWidth;
	indxsTitleRect.height=colsTitleHeight;
	indxsTitleRect.x=displayBox().x;
	indxsTitleRect.y=colsRect.y+colsRect.height;

	//*** indexesRect
	indxsRect.width=maxWidth;
	indxsRect.height = defaultHeight * idxsWindow + (idxsWindow * internalPadding);
	indxsRect.x=displayBox().x;
	indxsRect.y=indxsTitleRect.y+indxsTitleRect.height;

	//*** FullTable Size
	fullSizeRect.width = maxWidth;
	fullSizeRect.height = titleRect.height + titleColsRect.height + colsRect.height + indxsTitleRect.height + indxsRect.height;
	fullSizeRect.x=displayBox().x;  //666
	fullSizeRect.y=titleRect.y;

	//Update sizes
	rectangleFigure->setSize(fullSizeRect.GetSize());
}

void ddTableFigure::updateTableSize()
{
	//do something
	rectangleFigure->setSize(fullSizeRect.GetSize());
}

