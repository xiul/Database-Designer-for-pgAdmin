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
	
	//delete hack
	bool deleteColumnActivated();
	void toggleColumnDeleteMode(bool disable=false);
	
	//columns scrolls
	void updateTableSize();
	void recalculateColsPos();
	void setColsRowsWindow(int num);
	ddRect& getColsSpace();
	ddRect& getFullSpace();
	int getTotalColumns();
	int getColumnsWindow();
	int getTopColWindowIndex();
	void setColumnsWindow(int value);
	void columnsWindowUp();
	void columnsWindowDown();
	int getColDefaultHeight(wxFont font);
	
	//metadata
	wxString getTableName();

	//uk pk constraints
	void setPkConstraintName(wxString name);
	wxString getPkConstraintName();
	wxArrayString& getUkConstraintsNames();

/*	int addFk(wxString parentTableName);
	void removeFk(int fk);
*/
	void updateFkObservers();

protected:

private:
	//Main Rectangle Sizes
	ddRect fullSizeRect, titleRect, titleColsRect, colsRect, titleIndxsRect, indxsRect;
	ddRect unScrolledColsRect, unScrolledFullSizeRect;
	
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


/*	//foreign keys (created a this table)
	wxArrayString fkNames;
	int fkMaxIndex;
	wxArr
	*/
};
#endif
