//////////////////////////////////////////////////////////////////////////
//
// pgAdmin III - PostgreSQL Tools
// RCS-ID:      $Id: gqbObject.h 8189 2010-02-25 22:10:21Z dpage $
// Copyright (C) 2002 - 2010, The pgAdmin Development Team
// This software is released under the PostgreSQL Licence
//
// gqbObject.h - 
//
//////////////////////////////////////////////////////////////////////////

#ifndef DDTABLEFIGURE_H
#define DDTABLEFIGURE_H
#include "dd/draw/figures/ddCompositeFigure.h"
#include "dd/draw/figures/ddRectangleFigure.h"
#include "dd/draw/figures/ddSimpleTextFigure.h"
#include "dd/dditems/figures/ddTextColumnFigure.h"
#include "dd/dditems/figures/ddColumnFigure.h"

class ddScrollBarHandle;
class ddRelationshipFigure;

// Create Array Objects used as base for gqbCollections
class ddTableFigure : public ddCompositeFigure
{
public:  //DD-TODO: put private unneeded public methods
	ddTableFigure(int x, int y);
    ~ddTableFigure();
	
	//add remove items
	void addColumn(ddColumnFigure *column);
	void removeColumn(ddColumnFigure *column);
	
	//drawing
	virtual void draw(wxBufferedDC& context, ddDrawingView *view);
	virtual void drawSelected(wxBufferedDC& context, ddDrawingView *view);
	virtual void basicMoveBy(int x, int y);
	
	//delete hack columns
	bool deleteColumnActivated();
	void toggleColumnDeleteMode(bool disable=false);

	//delete hack tables
	void processDeleteAlert(ddDrawingView *view);
	
	//columns scrolls
	void updateTableSize();
	void recalculateColsPos();
	void setColsRowsWindow(int num);
	ddRect& getColsSpace();
	ddRect& getFullSpace();
	ddRect& getTitleRect();
	int getTotalColumns();
	int getColumnsWindow();
	int getTopColWindowIndex();
	void setColumnsWindow(int value, bool maximize=false);
	void columnsWindowUp();
	void columnsWindowDown();
	int getColDefaultHeight(wxFont font);
	
	//metadata
	wxString getTableName();
	wxString generateSQL();

	//uk pk constraints
	void setPkConstraintName(wxString name);
	wxString getPkConstraintName();
	wxArrayString& getUkConstraintsNames();
	
	//fk related
	void updateFkObservers();

protected:

private:
	//Main Rectangle Sizes
	ddRect fullSizeRect, titleRect, titleColsRect, colsRect, titleIndxsRect, indxsRect;
	ddRect unScrolledColsRect, unScrolledFullSizeRect, unScrolledTitleRect;
	
	//Rectangle item counters
	int colsRowsSize, colsWindow, idxsRowsSize, idxsWindow;
	
	//vector indexes
	int maxColIndex,minIdxIndex,maxIdxIndex;
	
	//position
	int beginDrawCols, beginDrawIdxs;
	
	//Default Figures
	ddRectangleFigure *rectangleFigure;
	ddTextColumnFigure *tableTitle;

	//helper variables
	bool fromSelToNOSel;
	bool deleteColumnMode;
	int internalPadding, externalPadding;
	bool calcScrolled;
	
	//specials handles
	ddScrollBarHandle *scrollbar;

	//methods
	int getHeightFontMetric(wxString text, wxFont font);
	int getFiguresMaxWidth();
	void calcRectsAreas();

	//pk uk(s)
	wxString pkName;
	wxArrayString ukNames;

};
#endif
